#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    // TODO: Define start state for all components
    Controller::Controller()
        : em(this, null),
          arm(this, null),
          vacuum(this, null),
          conveyor(this, null),
          cont_a(this, null, Components::ContainerType::PlasticCap),
          cont_b(this, null, Components::ContainerType::CrownCap),
          cont_c(this, null, Components::ContainerType::CigaretteStump),
          cont_d(this, null, Components::ContainerType::Valuables)
    {
    }

    Controller::~Controller()
    {
    }

    void Controller::Extend()
    {
    }

    void Controller::Retract()
    {
    }

    void Controller::StartCollecting()
    {
    }

    void Controller::StopCollecting()
    {
    }

    bool Controller::IsExtended()
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
        this->report["Extended"] = this->IsExtended();
        this->report["Collecting"] = this->IsCollecting();
        this->report["CurrentPowerConsumption"] = this->CurrentPowerConsumption();
        this->report["TotalPowerConsumption"] = this->TotalPowerConsumption();

        return this->report;
    }
}
