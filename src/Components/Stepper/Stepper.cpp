#include "Stepper.hpp"

namespace CleaningDevice::Components
{
    Stepper::Stepper(Controller &c, State<Stepper> *start, AccelStepper::MotorInterfaceType ifType, std::uint8_t pin1, std::uint8_t pin2)
        : AbstractComponent(c, start),
          stepper(ifType, pin1, pin2)
    {
        // After initialisation, set current position as the new 0-position
        this->stepper.setAcceleration(12000);
        this->stepper.setMaxSpeed(3000);
        this->stepper.setSpeed(3000);
        this->stepper.setCurrentPosition(this->stepper.currentPosition());
        xTaskCreate(Stepper::StepTask, "Stepper::StepTask", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY + 1, &(this->task));
        vTaskSuspend(this->task);
    }

    Stepper::~Stepper()
    {
        this->Stop();
        vTaskDelete(this->task);
    }

    void Stepper::MoveAbsolute(long position)
    {
        this->Stop();
        this->stepper.moveTo(position);
        vTaskResume(this->task);
    }

    void Stepper::MoveRelative(long position)
    {
        this->MoveAbsolute(this->stepper.currentPosition() + position);
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
        // this->report["Status"] = this->GetState()->ToString().c_str();
        this->report["Running"] = this->stepper.isRunning();
        this->report["Position"]["Current"] = this->stepper.currentPosition();
        this->report["Position"]["Target"] = this->stepper.targetPosition();
        this->report["Speed"]["Current"] = this->stepper.speed();
        this->report["Speed"]["Max"] = this->stepper.maxSpeed();
        this->report["Acceleration"] = this->stepper.acceleration();
        this->report["Distance left"] = this->stepper.distanceToGo();

        return this->report;
    }

    void Stepper::StepTask(void *pvParams)
    {
        auto self = static_cast<Stepper *>(pvParams);
        bool finished = false;

        for (;;)
        {
            taskENTER_CRITICAL(&self->spinLock);
            finished = !self->stepper.run();
            taskEXIT_CRITICAL(&self->spinLock);

            if (finished)
            {
                vTaskSuspend(nullptr);
            }
        }
    }
}
