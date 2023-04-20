#pragma once
#include "BaseComponent.hpp"

namespace CleaningDevice::Components
{
    class Conveyor : public BaseComponent<Conveyor>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    public:
        Conveyor(Controller *c, State<Conveyor> *start);
        ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
