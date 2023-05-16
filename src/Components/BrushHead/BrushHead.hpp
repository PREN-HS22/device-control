#pragma once
#include "../BaseComponent.hpp"

namespace CleaningDevice::Components
{
    class BrushHead : public BaseComponent<BrushHead>
    {
    public:
        BrushHead(Controller &c, State<BrushHead> &start);
        ~BrushHead();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
