#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN::Component
{
    class Conveyor : public Emergency, public Reportable
    {
    public:
        Conveyor(/* args */);
        virtual ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report* GetStatusReport();
    };
}
