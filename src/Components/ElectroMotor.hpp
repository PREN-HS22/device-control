#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class ElectroMotor : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        float angularVel, torque;
        Status status;

    public:
        ElectroMotor(Controller *c);
        ~ElectroMotor();

        void Rotate(float angularVel, float torque);
        void Rotate(float angularVel, float torque, float duration);
        void Stop();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
