#pragma once
#include "../AbstractComponent.hpp"
#include <L298N.h>
#include <freertos/task.h>

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

    class DcMotor : public AbstractComponent
    {
    private:
        DcMotorCfg config;
        L298N motor;
        unsigned long startTime, endTime;
        TimerHandle_t timer;
        portMUX_TYPE spinLock = portMUX_INITIALIZER_UNLOCKED;

    private:
        void Rotate(L298N::Direction dir, float speedFraction, std::uint64_t start, std::uint64_t end);
        static void TimerCallback(TimerHandle_t timer);

    public:
        DcMotor(Controller &c, DcMotorCfg config);
        ~DcMotor();

        void Rotate(L298N::Direction dir, float speedFraction);
        void Rotate(L298N::Direction dir, float speedFraction, std::uint64_t duration);
        void Stop();
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
