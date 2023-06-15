#include "Conveyor.hpp"

namespace CleaningDevice::Components
{
    Conveyor::Conveyor(Controller &c)
        : AbstractComponent(c),
          motor(c, DcMotorCfg(-1, -1, -1)) // Determine correct pins
    {
    }

    Conveyor::~Conveyor()
    {
    }

    void Conveyor::Start()
    {
        this->motor.Rotate(L298N::FORWARD, 100);
    }

    void Conveyor::Stop()
    {
        this->motor.Stop();
    }

    void Conveyor::SetSpeed(float fraction)
    {
        fraction = std::clamp(fraction, 0.f, 1.f);
        auto pwm = (std::uint16_t)(fraction * 255);
        this->motor.Rotate(L298N::FORWARD, pwm);
    }

    float Conveyor::GetSpeed()
    {
        return (float)this->motor.GetSpeed();
    }

    void Conveyor::RaiseEmergency()
    {
        // Stop device
    }

    Report &Conveyor::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();
        this->report["Motor"] = this->motor.GetReport();

        return this->report;
    }
}
