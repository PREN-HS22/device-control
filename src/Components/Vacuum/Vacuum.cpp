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
            self->motor.write(180 * self->speedFraction);
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

    void Vacuum::SetTargetSpeed(float fraction)
    {
        fraction = std::clamp(fraction, 0.f, 1.f);
    }

    float Vacuum::GetTargetSpeed()
    {
        return this->speedFraction;
    }

    bool Vacuum::IsReady() {
        return this->motor.attached();
    }

    void Vacuum::RaiseEmergency()
    {
        this->Stop();
    }

    Report &Vacuum::GetReport()
    {
        this->report["Target speed"] = this->GetTargetSpeed();

        return this->report;
    }
}
