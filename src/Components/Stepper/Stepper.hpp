#pragma once
#include "../AbstractComponent.hpp"
#include <A4988.h>
#include <freertos/task.h>

namespace CleaningDevice::Components
{
    class Stepper : public AbstractComponent
    {
    private:
        A4988 driver;
        TaskHandle_t task;
        portMUX_TYPE spinLock = portMUX_INITIALIZER_UNLOCKED;
        bool indefiniteSteps;
        long stepsRemaining;

    private:
        static void Run(void *pvParams);

    public:
        Stepper(Controller &c, std::uint16_t, std::uint8_t dirPin, std::uint8_t stepPin);
        ~Stepper();

        void Move(long steps, float rpm = 60.f);
        void MoveIndefinite(float rpm = 60.f);
        bool Calibrate();
        void Suspend();
        void Resume();
        void Stop();
        bool IsRunning();

        void RaiseEmergency();
        Report &GetReport();
    };
}
