#pragma once
#include "BaseComponent.hpp"

namespace CleaningDevice::Components
{
    class ElectroMotor : public BaseComponent<ElectroMotor>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        float angularVel, torque;

    public:
        ElectroMotor(Controller *c, State<ElectroMotor> *start);
        ~ElectroMotor();

        void Rotate(float angularVel, float torque);
        void Rotate(float angularVel, float torque, float duration);
        void Stop();
        void RaiseEmergency();
        Report &GetReport();
    };
}
