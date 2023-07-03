#include "Vacuum.hpp"

namespace CleaningDevice::Components
{
    Vacuum::Vacuum(Controller &c)
        : AbstractComponent(c),
          speedFraction(0.f),
          motor()
    {
    }

    Vacuum::~Vacuum()
    {
        this->motor.write(0.f);
        this->motor.detach();
    }

    void Vacuum::Enable()
    {
        if (this->motor.attached())
        {
            return;
        }

        // Min pulse width: 900us, max pulse width 2140us
        this->motor.attach(18, Servo::CHANNEL_NOT_ATTACHED, 0, 1000, 900, 2140);
        this->motor.write(0);
    }

    void Vacuum::Disable()
    {
        if (!this->motor.attached())
        {
            return;
        }

        this->motor.write(0);
        this->motor.detach();
    }

    void Vacuum::SetTargetSpeed(float fraction)
    {
        if (!this->motor.attached())
        {
            this->speedFraction = 0.f;
            return;
        }

        // Cut-off % -> 17.5
        // Idle % -> 18.0
        // Min % cig -> 22.0
        // Min % cap -> 22.0
        // Min % metal cap -> 26.0
        // Max %. loudness -> 28.0
        fraction = std::clamp(fraction, 0.f, 1.f);
        this->speedFraction = fraction;
        this->motor.write((int)(fraction * 1000.f));
    }

    float Vacuum::GetTargetSpeed()
    {
        return this->speedFraction;
    }

    void Vacuum::CutOff()
    {
        if (!this->IsReady())
        {
            return;
        }

        this->motor.write(0);
    }

    void Vacuum::Idle()
    {
        if (!this->IsReady())
        {
            return;
        }

        this->SetTargetSpeed(.18f);
    }

    void Vacuum::OperationalSpeed()
    {
        if (!this->IsReady())
        {
            return;
        }

        this->SetTargetSpeed(.26f);
    }

    bool Vacuum::IsReady()
    {
        return this->motor.attached();
    }

    void Vacuum::RaiseEmergency()
    {
        this->Disable();
    }

    Report &Vacuum::GetReport()
    {
        this->report["Ready"] = this->IsReady();
        this->report["Target speed"] = this->GetTargetSpeed();

        return this->report;
    }
}
