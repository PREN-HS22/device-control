#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Conveyor : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        Status status;

    public:
        Conveyor(Controller *c);
        ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
