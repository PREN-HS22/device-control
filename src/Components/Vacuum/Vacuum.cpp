#include "Vacuum.hpp"

namespace CleaningDevice::Components
{
    Vacuum::Vacuum(Controller &c, State<Vacuum> *start)
        : AbstractComponent<Vacuum>(c, start)
    {
    }

    Vacuum::~Vacuum()
    {
    }

    void Vacuum::Start()
    {
    }

    void Vacuum::Stop()
    {
        this->speedPctg = 0.f;
    }

    void Vacuum::SetSpeed(float percentage)
    {
        if (!(0.f <= percentage && percentage <= 100.f))
        {
            return;
        }

        this->speedPctg = percentage;
    }

    float Vacuum::GetSpeed()
    {
        return this->speedPctg;
    }

    void Vacuum::RaiseEmergency()
    {
        this->SetSpeed(0.f);
        // Stop device
    }

    Report &Vacuum::GetReport()
    {
        this->report["Status"] = this->GetState()->GetName();
        this->report["Speed [%]"] = this->GetSpeed();
        this->report["RPM"] = 0.f; // Calculate RPM of the motor

        return this->report;
    }
}
