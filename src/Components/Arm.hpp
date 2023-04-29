#pragma once
#include "BaseComponent.hpp"

namespace CleaningDevice::Components
{
    class Arm : public BaseComponent<Arm>
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

    public:
        Arm(Controller &c, State<Arm> &start);
        ~Arm();

        void Extend();
        void Retract();
        void Move(float distance, float speed);
        void Rotate(float angle, float speed);
        bool IsRetracted();
        float GetDistance();
        float GetAngle();
        void RaiseEmergency();
        Report &GetReport();
    };
}
