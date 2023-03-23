#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class ElectroMotor : public BaseComponent
    {
    private:

    public:
        ElectroMotor(Controller *c);
        virtual ~ElectroMotor();

        void Rotate(float angularVelocity, float torque, float duration);
        void Stop();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
