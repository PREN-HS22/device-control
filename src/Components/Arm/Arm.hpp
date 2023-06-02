#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"
#include "../Stepper/Stepper.hpp"

namespace CleaningDevice::Components
{
    class Arm : public AbstractComponent<Arm>
    {
    private:
        Stepper verticalStepper, horizontalStepper;
        DcMotor motorA, motorB;

    public:
        Arm(Controller &c, State<Arm> *start);
        ~Arm();

        void Lower();
        void Raise();
        void Move(float distance, float speed);
        void Rotate(float angle, float speed);
        bool IsRaised();
        bool IsLowered();
        float GetDistance();
        float GetAngle();
        void RaiseEmergency();
        Report &GetReport();
    };
}
