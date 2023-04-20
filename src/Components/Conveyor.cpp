#include "Conveyor.hpp"

namespace CleaningDevice::Components
{
    Conveyor::Conveyor(Controller *c, State<Conveyor> *start)
        : BaseComponent<Conveyor>(c, start)
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
        // Stop device
    }

    Report &Conveyor::GetReport()
    {
        this->report["Status"] = this->GetState()->GetName();
        this->report["Speed"] = this->GetSpeed();

        return this->report;
    }
}
