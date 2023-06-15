#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"

namespace CleaningDevice::Components
{
    class BrushHead : public AbstractComponent
    {
    private:
        DcMotor motor;

    public:
        BrushHead(Controller &c);
        ~BrushHead();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
