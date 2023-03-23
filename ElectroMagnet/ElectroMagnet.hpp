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

    public:
        ElectroMagnet(Controller *c);
        virtual ~ElectroMagnet();

        void Enable();
        void Disable();
        bool IsEnabled();
        void Rotate(float angle, float speed);
        void Cycle(int dir);
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };

}
