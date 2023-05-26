#include "Vacuum.hpp"

namespace CleaningDevice::Components
{
    Vacuum::Vacuum(Controller &c, State<Vacuum> *start)
        : AbstractComponent<Vacuum>(c, start),
          motor(c, nullptr, DcMotorCfg(-1, -1, -1)) // Determine correct pins
    {
    }

    Vacuum::~Vacuum()
    {
    }

    void Vacuum::Start()
    {
        auto pwm = (std::uint16_t)(this->speedFraction * 255);
        this->motor.Rotate(L298N::FORWARD, pwm);
    }

    void Vacuum::Stop()
    {
        this->motor.Stop();
    }

    void Vacuum::SetSpeed(float fraction)
    {
        fraction = std::clamp(fraction, 0.f, 1.f);
        this->speedFraction = fraction;
        auto pwm = (std::uint16_t)(fraction * 255);
        this->motor.Rotate(L298N::FORWARD, pwm);
    }

    float Vacuum::GetSpeed()
    {
        return this->speedFraction;
    }

    void Vacuum::RaiseEmergency()
    {
        this->Stop();
        // Stop device
    }

    Report &Vacuum::GetReport()
    {
        this->report["Status"] = this->GetState()->GetName();
        this->report["Speed"] = this->GetSpeed();
        this->report["Motor"] = this->motor.GetReport();

        return this->report;
    }
}
