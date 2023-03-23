#include "Vacuum.hpp"

namespace PREN::Components
{
    Vacuum::Vacuum(Controller *c) : BaseComponent(c), status(Idle)
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
        if (! (0.f <= percentage && percentage <= 100.f)) {
            return;
        }

        this->speedPctg = percentage;
    }

    float Vacuum::GetSpeed()
    {
        return this->speedPctg;
    }

    Vacuum::Status Vacuum::GetStatus()
    {
        return this->status;
    }

    void Vacuum::RaiseEmergency()
    {
    }

    Report &Vacuum::GetReport()
    {
        return this->report;
    }
}
