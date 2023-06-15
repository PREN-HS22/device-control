#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class ElectroMagnet : public AbstractComponent
    {
    private:
        void Rotate(float angle, float speed);

    public:
        ElectroMagnet(Controller &c);
        ~ElectroMagnet();

        void Enable();
        void Disable();
        bool IsEnabled();
        void Cycle(int dir);
        void RaiseEmergency();
        Report &GetReport();
    };
}
