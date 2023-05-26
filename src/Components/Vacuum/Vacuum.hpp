#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"
namespace CleaningDevice::Components
{
    class Vacuum : public AbstractComponent<Vacuum>
    {
    private:
        float speedFraction;
        DcMotor motor;

    public:
        Vacuum(Controller &c, State<Vacuum> *start);
        ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float fraction);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
