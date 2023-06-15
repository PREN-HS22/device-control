#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    Controller::Controller()
        : wifiClient(),
          mqttClient(wifiClient, "", 0U, "", "", (std::string)"esp32" + WiFi.macAddress().c_str()),
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
    }

    Controller::~Controller()
    {
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
    }

    float Controller::TotalPowerConsumption()
    {
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
            Serial.print(".");
            tries++;

            if (tries > 10)
            {
                // Display connection error on LCD
                Serial.println("AP connection failed");
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
