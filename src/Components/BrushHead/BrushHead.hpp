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
        PowerConsumption pc;

    public:
        BrushHead(Controller &c);
        ~BrushHead();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        float GetPower();
        void RaiseEmergency();
        Report &GetReport();
    };
}
