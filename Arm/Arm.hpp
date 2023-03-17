#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN::Component
{
    class Arm : public Emergency, public Reportable
    {
    private:
        Report status;

    public:
        Arm();
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
