#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"
#include "../../Misc/PowerConsumption.hpp"

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
        void SetSpeed(float fraction);
        float GetSpeed();
        float GetPower();
        void RaiseEmergency();
        Report &GetReport();
    };
}
