#pragma once
#include "../AbstractComponent.hpp"
#include <Servo.h>
#include <freertos/task.h>

namespace CleaningDevice::Components
{
    class Vacuum : public AbstractComponent
    {
    private:
        float speedFraction;
        Servo motor;
        TaskHandle_t task;
        portMUX_TYPE spinLock = portMUX_INITIALIZER_UNLOCKED;

    private:
        static void Run(void *pvParams);

    public:
        Vacuum(Controller &c);
        ~Vacuum();

        void Start();
        void Stop();
        void SetSpeed(float fraction);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
