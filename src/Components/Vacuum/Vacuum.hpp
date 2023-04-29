#pragma once
#include "../BaseComponent.hpp"

namespace CleaningDevice::Components
{
    class Vacuum : public BaseComponent<Vacuum>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        float speedPctg;

    public:
        Vacuum(Controller &c, State<Vacuum> &start);
        ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
