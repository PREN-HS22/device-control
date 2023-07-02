#include "Vacuum.hpp"

namespace CleaningDevice::Components
{
    Vacuum::Vacuum(Controller &c)
        : AbstractComponent(c),
          speedFraction(0.f),
          motor()
    {
        this->motor.attach(18, Servo::CHANNEL_NOT_ATTACHED, 0, 100);
    }

    Vacuum::~Vacuum()
    {
        this->motor.write(0.f);
        this->motor.detach();
    }

    void Vacuum::Start()
    {
        this->motor.write(this->speedFraction * 100.f);
    }

    void Vacuum::Stop()
    {
        this->motor.write(0.f);
    }

    void Vacuum::SetTargetSpeed(float fraction)
    {
        fraction = std::clamp(fraction, 0.f, 1.f);
        this->speedFraction = fraction;
        motor.write(fraction * 100.f);
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
