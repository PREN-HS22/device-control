#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    Controller::Controller(WiFiClient &wc, MqttClient &mc)
        : consumption(50, 13, 4, INA219_CALC_ADDRESS(0, 0)),
          wifiClient(wc),
          mqttClient(mc),
          arm(*this),
          vacuum(*this),
          conveyor(*this),
          brush(*this),
          cont_a(*this, Components::ContainerType::PlasticCap),
          cont_b(*this, Components::ContainerType::CrownCap),
          cont_c(*this, Components::ContainerType::CigaretteStump),
          cont_d(*this, Components::ContainerType::Valuables),
          lcd(*this, 0, 16, 2),
          collecting(false)
    {
        this->ConnectToWiFiAP();
        this->mqttClient.Connect();
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
        this->vacuum.Stop();
        // Move arm to idle position
        this->arm.Raise();

        while (!this->arm.IsRaised())
        {
            delay(1000);
        }
    }

    void Controller::StartCollecting()
    {
        this->collecting = true;
    }

    void Controller::StopCollecting()
    {
        this->collecting = false;
    }

    bool Controller::IsReady()
    {
        return this->arm.IsLowered() &&
               this->vacuum.IsReady();
    }

    bool Controller::IsCollecting()
    {
        return this->collecting;
    }

    float Controller::CurrentPowerConsumption()
    {
        return this->consumption.GetLatestSample().Power;
    }

    float Controller::TotalPowerConsumption()
    {
        return this->consumption.GetTotalPower();
    }

    void Controller::RaiseEmergency()
    {
        this->arm.RaiseEmergency();
        this->vacuum.RaiseEmergency();
        this->conveyor.RaiseEmergency();
        this->cont_a.RaiseEmergency();
        this->cont_b.RaiseEmergency();
        this->cont_c.RaiseEmergency();
        this->cont_d.RaiseEmergency();
        this->lcd.RaiseEmergency();

        this->mqttClient.Publish("/status", JSON.stringify(this->GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->arm.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->vacuum.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->conveyor.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->cont_a.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->cont_b.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->cont_c.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->cont_d.GetReport()).c_str());
        this->mqttClient.Publish("/status", JSON.stringify(this->lcd.GetReport()).c_str());
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
