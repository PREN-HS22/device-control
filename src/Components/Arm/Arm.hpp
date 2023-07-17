#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"
#include "../Stepper/Stepper.hpp"

namespace CleaningDevice::Components
{
    class Arm : public AbstractComponent
    {
    private:
        Stepper verticalStepper, horizontalStepper;
        DcMotor motorA, motorB;
        bool raised, lowered;

    public:
        Arm(Controller &c);
        ~Arm();

        void Lower();
        void Raise();
        void StopVerticalMovement();
        void StopHorizontalMovement();
        void StopAllMovements();
        void Move(uint64_t duration, float speed = .5f);
        void Rotate(long steps, float rpm = 60.f);
        bool IsRaised();
        bool IsLowered();
        float GetDistance();
        float GetAngle();
        void RaiseEmergency();
        Report &GetReport();
    };
}
