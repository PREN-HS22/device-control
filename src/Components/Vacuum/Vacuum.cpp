#include "Vacuum.hpp"

namespace CleaningDevice::Components
{
    Vacuum::Vacuum(Controller &c)
        : AbstractComponent(c),
          speedFraction(0.f),
          motor()
    {
        motor.attach(18);
        xTaskCreatePinnedToCore(Vacuum::Run, "Vacuum::Run", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->task), 1);
    }

    Vacuum::~Vacuum()
    {
        motor.detach();
    }

    void Vacuum::Run(void *pvParams)
    {
        auto self = static_cast<Vacuum *>(pvParams);

        for (;;)
        {
            taskENTER_CRITICAL(&self->spinLock);
            // 120° per call to Servo::write
            self->motor.write(0 /* (degrees + (35 * servoNumber)) % 180 */);
            taskEXIT_CRITICAL(&self->spinLock);
        }
    }

    void Vacuum::Start()
    {
        vTaskResume(this->task);
    }

    void Vacuum::Stop()
    {
        vTaskSuspend(this->task);
    }

    void Vacuum::SetSpeed(float fraction)
    {
    }

    float Vacuum::GetSpeed()
    {
        return this->speedFraction;
    }

    void Vacuum::RaiseEmergency()
    {
        this->Stop();
    }

    Report &Vacuum::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();

        return this->report;
    }
}
