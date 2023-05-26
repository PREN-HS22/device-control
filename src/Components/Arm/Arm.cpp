#include "Arm.hpp"

namespace CleaningDevice::Components
{
    Arm::Arm(Controller &c, State<Arm> *start)
        : AbstractComponent(c, start),
          verticalStepper(AccelStepper::DRIVER, 16, 17),    // Arm lowering and raising
          horizontalStepper(AccelStepper::DRIVER, 4, 13),   // Arm rotation
          motorA(c, nullptr, DcMotorCfg(32, 25, 33)), // Compartment A (Motor closer to base)
          motorB(c, nullptr, DcMotorCfg(14, 26, 27))  // Compartment B (Motor closer to brush)
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
        this->report["Status"] = this->GetState()->GetName();
        this->report["Distance"] = this->GetDistance();
        this->report["Angle"] = this->GetAngle();
        this->report["Raised"] = this->IsRaised();
        this->report["Motor"]["Segment A"] = this->motorA.GetReport();
        this->report["Motor"]["Segment B"] = this->motorB.GetReport();

        return this->report;
    }
}
