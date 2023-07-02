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
        float rpm;

    public:
        Conveyor(Controller &c);
        ~Conveyor();

        void Start();
        void Stop();
        void SetRpm(float rpm);
        float GetRpm();
        bool IsRunning();
        void RaiseEmergency();
        Report &GetReport();
    };
}
