#include "Vacuum.hpp"

namespace PREN::Components
{
    Vacuum::Vacuum(Controller *c) : BaseComponent(c)
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
    }

    void Vacuum::RaiseEmergency()
    {
    }

    Report &Vacuum::GetStatusReport()
    {
        return this->report;
    }
}
