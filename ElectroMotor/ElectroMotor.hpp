#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"

namespace PREN::Component
{
    class ElectroMotor : public Emergency, public Reportable
    {
    private:
        Report status;

    public:
        ElectroMotor();
        virtual ~ElectroMotor();

        void Rotate(float angularVelocity, float torque, float duration);
        void Stop();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
