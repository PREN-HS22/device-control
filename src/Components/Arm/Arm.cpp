#include "Arm.hpp"

namespace CleaningDevice::Components
{
    Arm::Arm(Controller &c, State<Arm> &start)
        : AbstractComponent<Arm>(c, start)
    {
    }

    Arm::~Arm()
    {
    }

    void Arm::Lower()
    {
    }

    void Arm::Raise()
    {
    }

    void Arm::Move(float distance, float speed)
    {
    }

    void Arm::Rotate(float angle, float speed)
    {
    }

    bool Arm::IsRaised()
    {
    }

    bool Arm::IsLowered()
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
        this->report["Raised"] = this->IsRaised();

        return this->report;
    }
}
