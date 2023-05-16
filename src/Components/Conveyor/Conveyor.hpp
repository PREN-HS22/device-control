#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class Conveyor : public AbstractComponent<Conveyor>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    public:
        Conveyor(Controller &c, State<Conveyor> &start);
        ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
