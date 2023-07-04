#include "BrushHead.hpp"

namespace CleaningDevice::Components
{
    BrushHead::BrushHead(Controller &c)
        : AbstractComponent(c),
          motor(c, DcMotorCfg(12, 15, 5)),
          running(false),
          speedFraction(.8f),
          pc(20, 13, 4, INA219_CALC_ADDRESS(0, 1))
    {
    }

    BrushHead::~BrushHead()
    {
    }

    void BrushHead::Start()
    {
        if (this->running)
        {
            return;
        }

        this->running = true;
        this->motor.Rotate(L298N::FORWARD, this->speedFraction);
    }

    void BrushHead::Stop()
    {
        if (!this->running)
        {
            return;
        }

        this->running = false;
        this->motor.Stop();
    }

    void BrushHead::SetSpeed(float fraction)
    {
        fraction = std::clamp(fraction, 0.f, 1.f);
        this->speedFraction = fraction;

        if (this->running)
        {
            this->motor.Rotate(L298N::FORWARD, fraction);
        }
    }

    float BrushHead::GetSpeed()
    {
        return this->motor.GetSpeed();
    }

    float BrushHead::GetPower()
    {
        return this->pc.GetLatestSample().Power;
    }

    void BrushHead::RaiseEmergency()
    {
        this->motor.Stop();
    }

    Report &BrushHead::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();
        this->report["Motor"] = this->motor.GetReport();
        this->report["Power"] = this->pc.GetReport();

        return this->report;
    }
}
