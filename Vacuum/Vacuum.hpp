#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"

namespace PREN::Components
{
    class Vacuum : public Emergency, public Reportable
    {
    private:
        Report status;

    public:
        Vacuum();
        virtual ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
