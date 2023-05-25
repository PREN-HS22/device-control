#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    // TODO: Define start state for all components
    Controller::Controller(State<Controller> *start)
        : FiniteStateMachine(start),
          wifiClient(),
          mqttClient(wifiClient, "", 0U, "", ""),
          em(*this, nullptr),
          arm(*this, nullptr),
          vacuum(*this, nullptr),
          conveyor(*this, nullptr),
          cont_a(*this, nullptr, Components::ContainerType::PlasticCap),
          cont_b(*this, nullptr, Components::ContainerType::CrownCap),
          cont_c(*this, nullptr, Components::ContainerType::CigaretteStump),
          cont_d(*this, nullptr, Components::ContainerType::Valuables)
    {
        this->ConnectToWiFiAP();
        this->ConnectToMqttBroker();
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
        this->report["Status"] = this->GetState()->GetName();
        this->report["Extended"] = this->IsReady();
        this->report["Collecting"] = this->IsCollecting();
        this->report["CurrentPowerConsumption"] = this->CurrentPowerConsumption();
        this->report["TotalPowerConsumption"] = this->TotalPowerConsumption();

        return this->report;
    }

    void Controller::ConnectToWiFiAP()
    {
        WiFi.begin("" /* ssid */, "" /* password */);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

    void Controller::ConnectToMqttBroker()
    {
    }
}
