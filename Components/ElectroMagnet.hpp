#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class ElectroMagnet : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Enabled,
            Disabled,
            Cycling = 4,
            CyclingEnabled,
            CyclingDisabled
        };

    private:
        Status status;
        void Rotate(float angle, float speed);

    public:
        ElectroMagnet(Controller *c);
        ~ElectroMagnet();

        void Enable();
        void Disable();
        bool IsEnabled();
        void Cycle(int dir);
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
