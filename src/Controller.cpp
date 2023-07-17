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
          brush(*this)
    {
        this->ConnectToWiFiAP();
        delay(500);
        this->mqttClient.Connect();
        delay(500);
        this->mqttClient.Publish("/status", "[Status] Controller started");
    }

    Controller::~Controller()
    {
        this->mqttClient.Publish("/status", "[Status] Controller stopped");
        WiFi.disconnect();
    }

    void Controller::StartDevice()
    {
        this->arm.Lower();
        while (!this->arm.IsLowered())
        {
            delay(1000);
        }
        this->conveyor.Start();
    }

    void Controller::StopDevice()
    {
        this->conveyor.Stop();
        this->vacuum.Disable();
        // Move arm to idle position
        this->arm.Raise();

        while (!this->arm.IsRaised())
        {
            delay(1000);
        }
    }

    void Controller::StartCollecting()
    {
    }

    void Controller::StopCollecting()
    {
    }

    bool Controller::IsReady()
    {
        return this->arm.IsLowered() &&
               this->vacuum.IsReady();
    }

    bool Controller::IsCollecting()
    {
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

        for (;;)
        {
        }
    }
}
