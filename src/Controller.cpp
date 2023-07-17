#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    Controller::Controller(WiFiClient &wc, MqttClient &mc)
        : wifiClient(wc),
          mqttClient(mc),
          arm(*this),
          vacuum(*this),
          conveyor(*this),
          brush(*this),
          state(State::IDLE)
    {
        this->ConnectToWiFiAP();
        delay(500);
        this->mqttClient.Connect();
        delay(500);
        this->mqttClient.Publish("/status", "[Status] Controller started");
        this->vacuum.Enable();
        xTaskCreatePinnedToCore(Controller::Run, "Controller::Run", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->mainTask), 0);
        xTaskCreatePinnedToCore(Controller::ButtonTask, "Controller::ButtonTask", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->buttonTask), 0);
        xTaskCreatePinnedToCore(Controller::CleaningTask, "Controller::CleaningTask", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->cleaningTask), 0);
        vTaskSuspend(this->cleaningTask);
    }

    Controller::~Controller()
    {
        this->mqttClient.Publish("/status", "[Status] Controller stopped");
        vTaskDelete(this->mainTask);
        vTaskDelete(this->buttonTask);
        this->vacuum.Disable();
        WiFi.disconnect();
    }

    void Controller::StartDevice()
    {
        xTaskCreatePinnedToCore(Controller::CleaningTask, "Controller::CleaningTask", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->cleaningTask), 0);
        vTaskSuspend(this->cleaningTask);
        this->arm.Lower();
    }

    void Controller::StopDevice()
    {
        this->conveyor.Stop();
        this->brush.Stop();
        this->vacuum.CutOff();
        // Move arm to idle position
        this->arm.Raise();
    }

    void Controller::StartCollecting()
    {
        this->arm.Rotate(34, 2.5f);
        vTaskDelay(pdMS_TO_TICKS(5500));

        for (int i = 0; i < 4; i++)
        {
            this->DoLinearMovementPattern();

            if (i < 3)
            {
                this->arm.Rotate(-17, 2.5f);
                vTaskDelay(pdMS_TO_TICKS(2900));
            }
        }

        this->arm.Rotate(34, 2.5f);
        vTaskDelay(pdMS_TO_TICKS(5500));
        this->state = State::IDLE;
    }

    void Controller::StopCollecting()
    {
        this->arm.StopAllMovements();
        this->conveyor.Stop();
        this->brush.Stop();
        this->vacuum.CutOff();
    }

    void Controller::DoLinearMovementPattern()
    {
        // 1. Extend
        this->vacuum.Idle();
        vTaskDelay(pdMS_TO_TICKS(100));
        this->conveyor.Start();
        this->vacuum.OperationalSpeed();
        this->brush.Start();
        this->arm.Move(4500, .6f); // 6800 for complete extension
        vTaskDelay(pdMS_TO_TICKS(4500));

        for (int i = 0; i < 5; i++)
        {
            // 2. Vacuum pause
            this->arm.StopAllMovements();
            this->vacuum.Idle();
            vTaskDelay(pdMS_TO_TICKS(200));
            this->vacuum.CutOff();
            vTaskDelay(pdMS_TO_TICKS(1500));

            // 3. Spin up vacuum
            this->vacuum.Idle();
            vTaskDelay(100);
            this->vacuum.OperationalSpeed();

            // 4. Step wise retraction
            for (int j = 0; j < 5; j++)
            {
                this->arm.Move(200, -.75f);
                vTaskDelay(pdMS_TO_TICKS(800));
            }
        }

        // 5. Finish linear movement
        this->vacuum.Idle();
        vTaskDelay(pdMS_TO_TICKS(200));
        this->vacuum.CutOff();
        vTaskDelay(pdMS_TO_TICKS(800));
    }

    bool Controller::IsReady()
    {
        return this->arm.IsLowered() &&
               this->vacuum.IsReady();
    }

    bool Controller::IsCollecting()
    {
        return this->state == State::COLLECTING;
    }

    float Controller::CurrentPowerConsumption()
    {
    }

    float Controller::TotalPowerConsumption()
    {
    }

    void Controller::RaiseEmergency()
    {
        this->arm.RaiseEmergency();
        this->vacuum.RaiseEmergency();
        this->conveyor.RaiseEmergency();

        this->mqttClient.Publish("/status", JSON.stringify(this->GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->arm.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->vacuum.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->conveyor.GetReport()).c_str());
    }

    Report &Controller::GetReport()
    {
        this->report["Ready"] = this->IsReady();
        this->report["Collecting"] = this->IsCollecting();
        this->report["CurrentPowerConsumption"] = this->CurrentPowerConsumption();
        this->report["TotalPowerConsumption"] = this->TotalPowerConsumption();

        return this->report;
    }

    void Controller::ConnectToWiFiAP()
    {
        WiFi.begin("" /* ssid */, "" /* password */);
        int tries = 0;

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(250);
            tries++;

            if (tries > 10)
            {
                // Display connection error on LCD
            }
        }
    }

    void Controller::Run(void *pvParams)
    {
        auto self = static_cast<Controller *>(pvParams);
        pinMode(34, INPUT); // Start
        pinMode(35, INPUT); // Stop

        for (;;)
        {
            switch (self->state)
            {
            case State::STARTING:
                self->state = State::COLLECTING;
                vTaskResume(self->cleaningTask);
                break;
            case State::COLLECTING:
                vTaskDelay(pdMS_TO_TICKS(500));
                break;
            case State::STOPPING:
                vTaskSuspend(self->cleaningTask);
                self->StopCollecting();
                break;
            case State::STOPPED:
                self->StopCollecting();
                self->StopDevice();
                vTaskDelete(self->cleaningTask);
                self->state = State::IDLE;
                break;
            }
        }
    }

    void Controller::ButtonTask(void *pvParams)
    {
        auto self = static_cast<Controller *>(pvParams);
        pinMode(34, INPUT); // Start
        pinMode(35, INPUT); // Stop

        for (;;)
        {
            if (!digitalRead(34))
            {
                Serial.println("34 pressed");

                if (self->state == State::IDLE)
                {
                    self->state = State::STARTING;
                }
            }

            if (!digitalRead(35))
            {
                Serial.println("35 pressed");

                if (self->state == State::COLLECTING)
                {
                    self->state = State::STOPPING;
                }
                else if (self->state == State::STOPPING)
                {
                    self->state = State::IDLE;
                }
            }

            vTaskDelay(pdMS_TO_TICKS(400));
        }
    }

    void Controller::CleaningTask(void *pvParams)
    {
        auto self = static_cast<Controller *>(pvParams);

        for (;;)
        {
            switch (self->state)
            {
            case State::STARTING:
                self->StartDevice();
                self->StartCollecting();
                break;
            }
        }
    }
}
