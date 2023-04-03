#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Arm : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Extending,
            Retractring,
            Moving = 4,
            MovingExtending,
            MovingRetracting,
            Rotating = 8,
            MovingRotating = 12
        };

    private:
        Status status;

    public:
        Arm(Controller *c);
        ~Arm();

        void Extend();
        void Retract();
        void Move(float distance, float speed);
        void Rotate(float angle, float speed);
        bool IsRetracted();
        float GetDistance();
        float GetAngle();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
