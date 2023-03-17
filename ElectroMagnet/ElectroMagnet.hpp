#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN::Component
{
    class ElectroMagnet : public Emergency, public Reportable
    {
    private:
        Report status;

    public:
        ElectroMagnet();
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
