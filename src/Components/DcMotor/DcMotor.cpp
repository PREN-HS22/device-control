#include "DcMotor.hpp"

namespace CleaningDevice::Components
{
    DcMotor::DcMotor(Controller &c, DcMotorCfg cfg)
        : AbstractComponent(c),
          config(cfg),
          motor(cfg.Enable, cfg.In1, cfg.In2)
    {
    }

    DcMotor::~DcMotor()
    {
    }

    void DcMotor::Rotate(L298N::Direction dir, float speedFraction)
    {
        speedFraction = std::clamp(speedFraction, 0.f, 1.f);
        auto pwm = (std::uint16_t)(speedFraction * 255);
        this->motor.setSpeed(pwm);
        this->motor.run(dir);
    }

    void DcMotor::Rotate(L298N::Direction dir, float speedFraction, float duration)
    {
        // Use a one-time FreeRTOS timer to stop the motor
        speedFraction = std::clamp(speedFraction, 0.f, 1.f);
        auto pwm = (std::uint16_t)(speedFraction * 255);
        this->motor.setSpeed(pwm);
        this->motor.run(dir);
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
        this->motor.stop();
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

        this->report["Duty cycle"] = this->GetSpeed();
        this->report["Direction"] = dir.c_str();

        return this->report;
    }
}
