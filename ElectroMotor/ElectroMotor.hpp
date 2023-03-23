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
        Status status;

    public:
        ElectroMotor(Controller *c);
        virtual ~ElectroMotor();

        void Rotate(float angularVelocity, float torque, float duration);
        void Stop();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
