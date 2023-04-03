#include "Controller.hpp"

namespace PREN
{
    Controller::Controller()
        : em(this),
          arm(this),
          vacuum(this),
          conveyor(this),
          containers({
              Components::Container(this, Components::ContainerType::PlasticCap),
              Components::Container(this, Components::ContainerType::CrownCap),
              Components::Container(this, Components::ContainerType::CigaretteStump),
              Components::Container(this, Components::ContainerType::Valuables),
          })
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
