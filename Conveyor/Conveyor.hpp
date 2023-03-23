#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"

namespace PREN::Components
{
    class Conveyor : public Emergency, public Reportable
    {
    private:
        Report status;

    public:
        Conveyor();
        virtual ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float s);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
