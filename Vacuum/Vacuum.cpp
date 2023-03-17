#include "Vacuum.hpp"

namespace PREN::Component
{
    Vacuum::Vacuum()
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
        return this->status;
    }
}
