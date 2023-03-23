#include "Conveyor.hpp"

namespace PREN::Components
{
    Conveyor::Conveyor(Controller *c) : BaseComponent(c), status(Idle)
    {
    }

    Conveyor::~Conveyor()
    {
    }

    void Conveyor::Start()
    {
    }

    void Conveyor::Stop()
    {
    }

    void Conveyor::SetSpeed(float s)
    {
    }

    float Conveyor::GetSpeed()
    {
    }

    Conveyor::Status Conveyor::GetStatus()
    {
        return this->status;
    }

    void Conveyor::RaiseEmergency()
    {
    }

    Report &Conveyor::GetReport()
    {
        return this->report;
    }
}
