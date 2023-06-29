#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    Controller::Controller()
        : consumption(50, INA219_CALC_ADDRESS(0, 0)),
          wifiClient(),
          mqttClient(wifiClient, "", 0U, "", "", (std::string) "esp32/" + WiFi.macAddress().c_str()),
          arm(*this),
          vacuum(*this),
          conveyor(*this),
          cont_a(*this, Components::ContainerType::PlasticCap),
          cont_b(*this, Components::ContainerType::CrownCap),
          cont_c(*this, Components::ContainerType::CigaretteStump),
          cont_d(*this, Components::ContainerType::Valuables)
    {
        this->ConnectToWiFiAP();
        this->mqttClient.Connect();
        this->mqttClient.Publish("/status", "[Status] Controller started");
    }

    Controller::~Controller()
    {
        this->mqttClient.Publish("/status", "[Status] Controller stopped");
    }

    void Controller::StartDevice()
    {
    }

    void Controller::StopDevice()
    {
    }

    void Controller::StartCollecting()
    {
    }

    void Controller::StopCollecting()
    {
    }

    bool Controller::IsReady()
    {
    }

    bool Controller::IsCollecting()
    {
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
        auto self = new Controller();

        for (;;)
        {
        }
    }
}
