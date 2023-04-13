#include "Controller.hpp"
#include <array>

namespace CleaningDevice
{
    Controller::Controller()
        : em(this),
          arm(this),
          vacuum(this),
          conveyor(this),          
          cont_a(this, Components::ContainerType::PlasticCap),
          cont_b(this, Components::ContainerType::CrownCap),
          cont_c(this, Components::ContainerType::CigaretteStump),
          cont_d(this, Components::ContainerType::Valuables)
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
        return this->status;
    }
}
