#pragma once
#include "../AbstractComponent.hpp"

namespace CleaningDevice::Components
{
    class Vacuum : public AbstractComponent<Vacuum>
    {
    private:
        float speedPctg;

    public:
        Vacuum(Controller &c, State<Vacuum> *start);
        ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float percentage);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
