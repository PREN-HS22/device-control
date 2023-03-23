#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class ElectroMagnet : public BaseComponent
    {
    private:

    public:
        ElectroMagnet(Controller *c);
        virtual ~ElectroMagnet();

        void Enable();
        void Disable();
        bool IsEnabled();
        void Rotate(float angle, float speed);
        void Cycle(int dir);
        void RaiseEmergency();
        Report &GetStatusReport();
    };

}
