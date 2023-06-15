#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"
namespace CleaningDevice::Components
{
    class Vacuum : public AbstractComponent
    {
    private:
        float speedFraction;
        DcMotor motor;

    public:
        Vacuum(Controller &c);
        ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float fraction);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
