#include "DcMotor.hpp"

namespace CleaningDevice::Components
{
    DcMotor::DcMotor(Controller &c, State<DcMotor> *start, DcMotorCfg cfg)
        : AbstractComponent(c, start),
          config(cfg),
          motor(cfg.Enable, cfg.In1, cfg.In2)
    {
        this->motor.setSpeed(cfg.Pwm);
    }

    DcMotor::~DcMotor()
    {
    }

    void DcMotor::Rotate(L298N::Direction dir, uint16_t pwmDutyCycle)
    {
        this->motor.setSpeed(pwmDutyCycle);
        this->motor.runFor(0, dir);
    }

    void DcMotor::Rotate(L298N::Direction dir, uint16_t pwmDutyCycle, float duration)
    {
        this->motor.setSpeed(pwmDutyCycle);
        this->motor.runFor(duration, dir);
    }

    void DcMotor::Stop()
    {
        this->motor.stop();
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
        this->report["Status"] = this->GetState()->GetName();
        this->report["Duty cycle"] = this->motor.getSpeed();
        this->report["Direction"] = dir.c_str();

        return this->report;
    }
}
