#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class Conveyor : public AbstractComponent<Conveyor>
    {
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
