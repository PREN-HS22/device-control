#include "BrushHead.hpp"

namespace CleaningDevice::Components
{
    BrushHead::BrushHead(Controller &c)
        : AbstractComponent(c),
          motor(c, DcMotorCfg(12, 15, 5))
    {
    }

    BrushHead::~BrushHead()
    {
    }

    void BrushHead::Start()
    {
        this->motor.Rotate(L298N::FORWARD, 100); // Determine correct direction
    }

    void BrushHead::Stop()
    {
        this->motor.Stop();
    }

    void BrushHead::SetSpeed(float fraction)
    {
        fraction = std::clamp(fraction, .0f, 1.f);
        auto pwm = (std::uint16_t)(fraction * 255);
        this->motor.Rotate(L298N::FORWARD, pwm);
    }

    float BrushHead::GetSpeed()
    {
        return this->motor.GetSpeed();
    }

    void BrushHead::RaiseEmergency()
    {
    }

    Report &BrushHead::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();
        this->report["Motor"] = this->motor.GetReport();

        return this->report;
    }
}
