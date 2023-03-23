#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Conveyor : public BaseComponent
    {
    private:

    public:
        Conveyor(Controller *c);
        virtual ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
