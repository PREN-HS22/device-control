#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class DcMotor : public AbstractComponent<DcMotor>
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
        DcMotor(Controller &c, State<DcMotor> &start);
        ~DcMotor();

        void Rotate(float angularVel, float torque);
        void Rotate(float angularVel, float torque, float duration);
        void Stop();
        void RaiseEmergency();
        Report &GetReport();
    };
}
