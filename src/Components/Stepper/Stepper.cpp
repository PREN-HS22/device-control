#include "Stepper.hpp"

namespace CleaningDevice::Components
{
    Stepper::Stepper(Controller &c, AccelStepper::MotorInterfaceType ifType, std::uint8_t pin1, std::uint8_t pin2)
        : AbstractComponent(c),
          stepper(ifType, pin1, pin2),
          indefiniteSteps(false)
    {
        // After initialisation, set current position as the new 0-position
        this->stepper.setAcceleration(12000);
        this->stepper.setCurrentPosition(this->stepper.currentPosition());
        xTaskCreatePinnedToCore(Stepper::Run, "Stepper::Run", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->task), 1);
        vTaskSuspend(this->task);
    }

    Stepper::~Stepper()
    {
        vTaskDelete(this->task);
        this->Stop();
    }

    void Stepper::Move(long position, float speed)
    {
        this->Stop();
        this->stepper.setMaxSpeed(std::abs(speed));
        this->stepper.moveTo(position);
        vTaskResume(this->task);
    }

    void Stepper::MoveAbsolute(long position, float speed)
    {
        this->indefiniteSteps = false;
        this->Move(position, speed);
    }

    void Stepper::MoveRelative(long position, float speed)
    {
        this->indefiniteSteps = false;
        this->Move(this->stepper.currentPosition() + position, speed);
    }

    void Stepper::MoveIndefinite(float speed)
    {
        this->indefiniteSteps = true;
        this->stepper.setCurrentPosition(0);
        this->Move(speed > 0.f ? 100000 : -10000, speed);
    }

    bool Stepper::Calibrate()
    {
        auto canCalibrate = !this->stepper.isRunning();

        if (canCalibrate)
        {
            this->stepper.setCurrentPosition(this->stepper.currentPosition());
        }

        return canCalibrate;
    }

    void Stepper::Suspend()
    {
        if (this->stepper.isRunning())
        {
            vTaskSuspend(this->task);
            auto distanceLeft = this->stepper.distanceToGo();
            this->stepper.stop();
            this->stepper.move(distanceLeft);
        }
    }

    void Stepper::Resume()
    {
        if (this->stepper.isRunning())
        {
            vTaskResume(this->task);
        }
    }

    void Stepper::Stop()
    {
        if (this->stepper.isRunning())
        {
            vTaskSuspend(this->task);
            this->stepper.stop();
        }
    }

    bool Stepper::IsRunning()
    {
        return this->stepper.isRunning();
    }

    void Stepper::RaiseEmergency()
    {
    }

    Report &Stepper::GetReport()
    {
        this->report["Running"] = this->stepper.isRunning();
        this->report["Run indefinitely"] = this->indefiniteSteps;
        this->report["Position"]["Current"] = this->stepper.currentPosition();
        this->report["Position"]["Target"] = this->stepper.targetPosition();
        this->report["Speed"]["Current"] = this->stepper.speed();
        this->report["Speed"]["Max"] = this->stepper.maxSpeed();
        this->report["Acceleration"] = this->stepper.acceleration();
        this->report["Distance left"] = this->stepper.distanceToGo();

        return this->report;
    }

    void Stepper::Run(void *pvParams)
    {
        auto self = static_cast<Stepper *>(pvParams);
        bool finished = false;

        for (;;)
        {
            taskENTER_CRITICAL(&self->spinLock);
            if (self->indefiniteSteps)
            {
                self->stepper.setCurrentPosition(0);
            }

            finished = !self->stepper.run();
            taskEXIT_CRITICAL(&self->spinLock);

            if (finished)
            {
                vTaskSuspend(nullptr);
            }
        }
    }
}
