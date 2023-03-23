#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Arm : public BaseComponent
    {
    private:

    public:
        Arm(Controller *c);
        virtual ~Arm();

        void Descend();
        void Ascend();
        void Move(float distance, float speed);
        void Rotate(float angle, float speed);
        float GetDistance();
        float GetAngle();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
