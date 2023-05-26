#pragma once
#include "../AbstractComponent.hpp"
#include <L298N.h>

namespace CleaningDevice::Components
{
    class DcMotorCfg
    {
    public:
        const std::uint8_t Enable, In1, In2;

        DcMotorCfg(std::uint8_t enable, std::uint8_t in1, std::uint8_t in2)
            : Enable(enable),
              In1(in1),
              In2(in2) {}
    };

    class DcMotor : public AbstractComponent<DcMotor>
    {
    private:
        DcMotorCfg config;
        L298N motor;

    public:
        DcMotor(Controller &c, State<DcMotor> *start, DcMotorCfg config);
        ~DcMotor();

        void Rotate(L298N::Direction dir, float speedFraction);
        void Rotate(L298N::Direction dir, float speedFraction, float duration);
        void Stop();
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
