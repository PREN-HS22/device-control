#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class ElectroMagnet : public AbstractComponent<ElectroMagnet>
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
        void Rotate(float angle, float speed);

    public:
        ElectroMagnet(Controller &c, State<ElectroMagnet> &start);
        ~ElectroMagnet();

        void Enable();
        void Disable();
        bool IsEnabled();
        void Cycle(int dir);
        void RaiseEmergency();
        Report &GetReport();
    };
}
