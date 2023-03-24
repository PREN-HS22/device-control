#include "Controller.hpp"

namespace PREN
{
    Controller::Controller() : em(this), arm(this), vacuum(this), conveyor(this), containers({})
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
