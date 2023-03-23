#include "Arm.hpp"

namespace PREN::Components
{
    Arm::Arm(Controller *c) : BaseComponent(c), status(Idle)
    {
    }

    Arm::~Arm()
    {
    }

    void Arm::Extend()
    {
    }

    void Arm::Retract()
    {
    }

    void Arm::Move(float distance, float speed)
    {
    }

    void Arm::Rotate(float angle, float speed)
    {
    }

    bool Arm::IsRetracted()
    {
    }

    float Arm::GetDistance()
    {
    }

    float Arm::GetAngle()
    {
    }

    Arm::Status Arm::GetStatus()
    {
        return this->status;
    }

    void Arm::RaiseEmergency()
    {
    }

    Report &Arm::GetReport()
    {
        return this->report;
    }
}
