#pragma once
#include "../AbstractComponent.hpp"
#include "../Stepper/Stepper.hpp"
#include <freertos/task.h>

namespace CleaningDevice::Components
{
    class Conveyor : public AbstractComponent
    {
    private:
        Stepper stepper;
        const float maxStepperSpeed;
        float speedFraction;

    public:
        Conveyor(Controller &c);
        ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float fraction);
        float GetSpeed();
        bool IsRunning();
        void RaiseEmergency();
        Report &GetReport();
    };
}
