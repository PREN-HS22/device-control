#pragma once
#include "../AbstractComponent.hpp"
#include <AccelStepper.h>
#include <freertos/task.h>

namespace CleaningDevice::Components
{
    class Stepper : public AbstractComponent<Stepper>
    {
    private:
        AccelStepper stepper;
        TaskHandle_t task;
        portMUX_TYPE spinLock = portMUX_INITIALIZER_UNLOCKED;

    private:
        static void StepTask(void *pvParams);

    public:
        Stepper(Controller &c, State<Stepper> *start, AccelStepper::MotorInterfaceType ifType, std::uint8_t pin1, std::uint8_t pin2);
        ~Stepper();

        void MoveAbsolute(long position, float speed);
        void MoveRelative(long position, float speed);
        bool Calibrate();
        void Suspend();
        void Resume();
        void Stop();
        bool IsRunning();

        void RaiseEmergency();
        Report &GetReport();
    };
}
