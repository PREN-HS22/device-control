#include "Arm.hpp"

namespace CleaningDevice::Components
{
    Arm::Arm(Controller &c)
        : AbstractComponent(c),
          verticalStepper(c, 200, 22, 23),   // Arm lowering and raising, positive numbers lower, negative raise the arm
          horizontalStepper(c, 200, 19, 21), // Arm rotation
          motorA(c, DcMotorCfg(32, 25, 33)), // Compartment A (Motor closer to base)
          motorB(c, DcMotorCfg(14, 26, 27)), // Compartment B (Motor closer to brush)
          raised(true),
          lowered(false)
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
        if (this->lowered)
        {
            return;
        }

        this->verticalStepper.Move(7400, 200.f);
        vTaskDelay(pdMS_TO_TICKS(15000));
        this->raised = false;
        this->lowered = true;
    }

    void Arm::Raise()
    {
        if (this->raised)
        {
            return;
        }

        this->verticalStepper.Move(-7400, 200.f);
        vTaskDelay(pdMS_TO_TICKS(15000));
        this->lowered = false;
        this->raised = true;
    }

    void Arm::StopVerticalMovement()
    {
        this->verticalStepper.Stop();
    }

    void Arm::StopHorizontalMovement()
    {
        this->horizontalStepper.Stop();
    }

    void Arm::StopAllMovements()
    {
        this->motorA.Stop();
        this->motorB.Stop();
    }

    void Arm::Move(uint64_t duration, float speed)
    {
        // FORWARD: Retract
        // BACKWARD: Extend
        speed = std::clamp(speed, -1.f, 1.f);
        auto dir = speed > 0.f ? L298N::BACKWARD : L298N::FORWARD;

        motorA.Rotate(dir, std::abs(speed), duration);
        motorB.Rotate(dir, std::abs(speed), duration);
    }

    void Arm::Rotate(long steps, float rpm)
    {
        this->horizontalStepper.Move(steps, rpm);
    }

    bool Arm::IsRaised()
    {
        return this->raised;
    }

    bool Arm::IsLowered()
    {
        return this->lowered;
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
