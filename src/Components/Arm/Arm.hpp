#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class Arm : public AbstractComponent<Arm>
    {
    public:
        Arm(Controller &c, State<Arm> &start);
        ~Arm();

        void Lower();
        void Raise();
        void Move(float distance, float speed);
        void Rotate(float angle, float speed);
        bool IsRaised();
        bool IsLowered();
        float GetDistance();
        float GetAngle();
        void RaiseEmergency();
        Report &GetReport();
    };
}
