#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"

namespace CleaningDevice::Components
{
    class BrushHead : public AbstractComponent<BrushHead>
    {
    private:
        DcMotor motor;

    public:
        BrushHead(Controller &c, State<BrushHead> *start);
        ~BrushHead();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
