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
        Status status;

    public:
        Vacuum(Controller *c);
        virtual ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
