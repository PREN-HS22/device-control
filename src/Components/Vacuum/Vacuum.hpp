#pragma once
#include "../AbstractComponent.hpp"
#include <Servo.h>

namespace CleaningDevice::Components
{
    class Vacuum : public AbstractComponent
    {
    private:
        float speedFraction;
        Servo motor;

    public:
        Vacuum(Controller &c);
        ~Vacuum();

        void Enable();
        void Disable();
        void SetTargetSpeed(float fraction);
        float GetTargetSpeed();
        void CutOff();
        void Idle();
        void OperationalSpeed();
        bool IsReady();
        void RaiseEmergency();
        Report &GetReport();
    };
}
