#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class BrushHead : public AbstractComponent<BrushHead>
    {
    public:
        BrushHead(Controller &c, State<BrushHead> *start);
        ~BrushHead();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
