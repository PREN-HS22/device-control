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
    }

    void Vacuum::SetSpeed(float percentage)
    {
    }

    float Vacuum::GetSpeed()
    {
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
