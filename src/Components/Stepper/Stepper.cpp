#include "Stepper.hpp"

namespace CleaningDevice::Components
{
    Stepper::Stepper(Controller &c, std::uint16_t steps, std::uint8_t dirPin, std::uint8_t stepPin)
        : AbstractComponent(c),
          driver(steps, dirPin, stepPin),
          indefiniteSteps(false),
          stepsRemaining(0)
    {
        // After initialisation, set current position as the new 0-position
        this->driver.begin();
        this->driver.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
        xTaskCreatePinnedToCore(Stepper::Run, "Stepper::Run", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->task), 1);
        vTaskSuspend(this->task);
    }

    Stepper::~Stepper()
    {
        this->Stop();
        vTaskDelete(this->task);
    }

    void Stepper::Move(long steps, float rpm)
    {
        this->Stop();
        this->indefiniteSteps = false;
        this->driver.setRPM(std::abs(rpm));
        this->driver.startMove(steps);
        vTaskResume(this->task);
    }

    void Stepper::MoveIndefinite(float rpm)
    {
        this->Stop();
        this->indefiniteSteps = true;
        this->driver.setRPM(std::abs(rpm));
        this->driver.startMove(rpm > 0.f ? 1000000 : -1000000);
        vTaskResume(this->task);
    }

    bool Stepper::Calibrate()
    {
        auto canCalibrate = !this->driver.getCurrentState() != BasicStepperDriver::STOPPED;

        return canCalibrate;
    }

    void Stepper::Suspend()
    {
        if (this->driver.getCurrentState() != BasicStepperDriver::STOPPED)
        {
            vTaskSuspend(this->task);
            this->stepsRemaining = this->driver.stop();
        }
    }

    void Stepper::Resume()
    {
        if (this->driver.getCurrentState() == BasicStepperDriver::STOPPED)
        {
            this->driver.startMove(this->stepsRemaining);
            vTaskResume(this->task);
        }
    }

    void Stepper::Stop()
    {
        if (this->driver.getCurrentState() != BasicStepperDriver::STOPPED)
        {
            vTaskSuspend(this->task);
            this->driver.stop();
        }
    }

    bool Stepper::IsRunning()
    {
        return this->driver.getCurrentState() != BasicStepperDriver::STOPPED;
    }

    void Stepper::RaiseEmergency()
    {
        this->Stop();
    }

    Report &Stepper::GetReport()
    {
        this->report["Running"] = this->driver.getCurrentState() != BasicStepperDriver::STOPPED;
        this->report["Run indefinitely"] = this->indefiniteSteps;
        this->report["Steps"]["Completed"] = this->driver.getStepsCompleted();
        this->report["Steps"]["Remaining"] = this->driver.getStepsRemaining();

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
                self->driver.startMove(self->driver.getDirection() * 1000000);
            }
            taskEXIT_CRITICAL(&self->spinLock);

            finished = !self->driver.nextAction() > 0;

            if (finished)
            {
                vTaskSuspend(nullptr);
            }
        }
    }
}
