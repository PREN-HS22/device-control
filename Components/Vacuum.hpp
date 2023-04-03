#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Vacuum : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        float speedPctg;
        Status status;

    public:
        Vacuum(Controller *c);
        ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
