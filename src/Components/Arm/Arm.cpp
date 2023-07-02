#include "Arm.hpp"

namespace CleaningDevice::Components
{
    Arm::Arm(Controller &c)
        : AbstractComponent(c),
          verticalStepper(c, 200, 22, 23),   // Arm lowering and raising, positive numbers lower, negative raise the arm
          horizontalStepper(c, 200, 19, 21), // Arm rotation
          motorA(c, DcMotorCfg(32, 25, 33)),  // Compartment A (Motor closer to base)
          motorB(c, DcMotorCfg(14, 26, 27))   // Compartment B (Motor closer to brush)
    {
    }

    Arm::~Arm()
    {
        this->motorA.Stop();
        this->motorB.Stop();
        this->verticalStepper.Stop();
        this->horizontalStepper.Stop();
    }

    void Arm::Lower()
    {
    }

    void Arm::Raise()
    {
    }

    void Arm::Move(float distance, float speed)
    {
        // FORWARD: Retract
        // BACKWARD: Extend
        // TODO: Map distance and speed to the corresponding duration and PWM dutycycle
        speed = std::clamp(speed, 0.f, 1.f);
        auto dir = distance > 0.f ? L298N::BACKWARD : L298N::FORWARD;
        auto pwm = (std::uint16_t)(speed * 255);

        motorA.Rotate(dir, pwm);
        motorB.Rotate(dir, pwm);
        delay(1000);
        motorA.Stop();
        motorB.Stop();
    }

    void Arm::Rotate(float angle, float rpm)
    {
        // TODO: Calculate angle to steps
        long steps = (long)(angle * 100.f);
        this->horizontalStepper.Move(steps, rpm);
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
        this->motorA.Stop();
        this->motorB.Stop();
        this->verticalStepper.Stop();
        this->horizontalStepper.Stop();
    }

    Report &Arm::GetReport()
    {
        this->report["Distance"] = this->GetDistance();
        this->report["Angle"] = this->GetAngle();
        this->report["Raised"] = this->IsRaised();
        this->report["Stepper"]["Horizontal"] = this->horizontalStepper.GetReport();
        this->report["Stepper"]["Vertical"] = this->verticalStepper.GetReport();
        this->report["Motor"]["Segment A"] = this->motorA.GetReport();
        this->report["Motor"]["Segment B"] = this->motorB.GetReport();

        return this->report;
    }
}
