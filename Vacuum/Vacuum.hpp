#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Vacuum : public BaseComponent
    {
    private:

    public:
        Vacuum(Controller *c);
        virtual ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
