#include "Arm.hpp"

namespace PREN::Components
{
    Arm::Arm(Controller *c) : BaseComponent(c), status(Idle)
    {
    }

    Arm::~Arm()
    {
    }

    void Arm::Descend()
    {
    }

    void Arm::Ascend()
    {
    }

    void Arm::Move(float distance, float speed)
    {
    }

    void Arm::Rotate(float angle, float speed)
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

    Report &Arm::GetStatusReport()
    {
        return this->report;
    }
}
