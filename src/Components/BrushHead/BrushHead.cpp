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
        this->motor.Rotate(L298N::FORWARD, .8f); // Determine correct direction
    }

    void BrushHead::Stop()
    {
        this->motor.Stop();
    }

    void BrushHead::SetSpeed(float fraction)
    {
        this->motor.Rotate(L298N::FORWARD, fraction);
    }

    float BrushHead::GetSpeed()
    {
        return this->motor.GetSpeed();
    }

    float BrushHead::GetPower()
    {
        return 0.f;
    }

    void BrushHead::RaiseEmergency()
    {
        this->motor.Stop();
    }

    Report &BrushHead::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();
        this->report["Motor"] = this->motor.GetReport();

        return this->report;
    }
}
