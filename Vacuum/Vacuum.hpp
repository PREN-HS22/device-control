#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN::Component
{
    class Vacuum : public Emergency, public Reportable
    {
    public:
        Vacuum();
        virtual ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report* GetStatusReport();
    };
}
