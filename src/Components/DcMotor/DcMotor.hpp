#pragma once
#include "../AbstractComponent.hpp"
#include <L298N.h>

namespace CleaningDevice::Components
{
    class DcMotorCfg
    {
    public:
        const std::uint8_t Enable, In1, In2;
        const std::uint16_t Pwm;

        DcMotorCfg(std::uint8_t enable, std::uint8_t in1, std::uint8_t in2, std::uint16_t pwm = 0)
            : Enable(enable),
              In1(in1),
              In2(in2),
              Pwm(pwm) {}
    };

    class DcMotor : public AbstractComponent<DcMotor>
    {
    private:
        DcMotorCfg config;
        L298N motor;

    public:
        DcMotor(Controller &c, State<DcMotor> *start, DcMotorCfg config);
        ~DcMotor();

        void Rotate(L298N::Direction dir, uint16_t pwmDutyCycle);
        void Rotate(L298N::Direction dir, uint16_t pwmDutyCycle, float duration);
        void Stop();
        void RaiseEmergency();
        Report &GetReport();
    };
}
