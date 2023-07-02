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

        void Start();
        void Stop();
        void SetTargetSpeed(float fraction);
        float GetTargetSpeed();
        bool IsReady();
        void RaiseEmergency();
        Report &GetReport();
    };
}
