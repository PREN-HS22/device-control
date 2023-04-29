#include "Arm.hpp"

namespace CleaningDevice::Components
{
    Arm::Arm(Controller &c, State<Arm> &start)
        : BaseComponent<Arm>(c, start)
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

    void Arm::RaiseEmergency()
    {
        // Stop device
    }

    Report &Arm::GetReport()
    {
        this->report["Status"] = this->GetState().GetName();
        this->report["Distance"] = this->GetDistance();
        this->report["Angle"] = this->GetAngle();
        this->report["Retracted"] = this->IsRetracted();

        return this->report;
    }
}
