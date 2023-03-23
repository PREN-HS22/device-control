#include "Conveyor.hpp"

namespace PREN::Components
{
    Conveyor::Conveyor(Controller *c) : BaseComponent(c)
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

    void Conveyor::RaiseEmergency()
    {
    }

    Report &Conveyor::GetStatusReport()
    {
        return this->report;
    }
}
