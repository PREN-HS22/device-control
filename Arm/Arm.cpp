#include "Arm.hpp"

namespace PREN::Components
{
    Arm::Arm(Controller *c) : BaseComponent(c)
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

    void Arm::RaiseEmergency()
    {
    }

    Report &Arm::GetStatusReport()
    {
        return this->report;
    }
}
