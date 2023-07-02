#include "DcMotor.hpp"

namespace CleaningDevice::Components
{
    DcMotor::DcMotor(Controller &c, DcMotorCfg cfg)
        : AbstractComponent(c),
          config(cfg),
          motor(cfg.Enable, cfg.In1, cfg.In2)
    {
        this->timer = xTimerCreate("DcMotor::Rotate", pdMS_TO_TICKS(1000), pdFALSE, this, DcMotor::TimerCallback);
    }

    DcMotor::~DcMotor()
    {
        xTimerDelete(this->timer, pdMS_TO_TICKS(5));
    }

    void DcMotor::Rotate(L298N::Direction dir, float speedFraction, std::uint64_t start, std::uint64_t end)
    {
        this->startTime = start;
        this->endTime = end;
        speedFraction = std::clamp(speedFraction, 0.f, 1.f);
        auto pwm = (std::uint16_t)(speedFraction * 255);
        this->motor.setSpeed(pwm);
        this->motor.run(dir);
    }

    void DcMotor::Rotate(L298N::Direction dir, float speedFraction)
    {
        this->Rotate(dir, speedFraction, 0UL, 0UL);
    }

    void DcMotor::Rotate(L298N::Direction dir, float speedFraction, std::uint64_t duration)
    {
        if (duration == 0)
        {
            return;
        }

        xTimerChangePeriod(this->timer, pdMS_TO_TICKS(duration), pdMS_TO_TICKS(5));
        xTimerReset(this->timer, pdMS_TO_TICKS(5));
        this->Rotate(dir, speedFraction, millis(), millis() + duration);
    }

    void DcMotor::Stop()
    {
        this->motor.stop();
    }

    float DcMotor::GetSpeed()
    {
        return (float)(this->motor.getSpeed()) / 255.f;
    }

    void DcMotor::RaiseEmergency()
    {
        this->Stop();
    }

    Report &DcMotor::GetReport()
    {
        std::string dir;
        switch (this->motor.getDirection())
        {
        case L298N::FORWARD:
            dir = "Forward";
            break;
        case L298N::BACKWARD:
            dir = "Backward";
            break;
        case L298N::STOP:
            dir = "Stopped";
            break;
        }

        auto timeLeft = this->endTime - this->startTime;

        this->report["Duty cycle"] = this->GetSpeed();
        this->report["Direction"] = dir.c_str();
        this->report["Duration"] = timeLeft > 0 ? (std::to_string(timeLeft) + "ms").c_str() : "Indefinite";

        return this->report;
    }

    void DcMotor::TimerCallback(TimerHandle_t timer)
    {
        auto self = static_cast<DcMotor *>(pvTimerGetTimerID(timer));

        taskENTER_CRITICAL(&self->spinLock);
        self->Stop();
        taskEXIT_CRITICAL(&self->spinLock);
    }
}
