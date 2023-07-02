#include "BrushHead.hpp"

namespace CleaningDevice::Components
{
    BrushHead::BrushHead(Controller &c)
        : AbstractComponent(c),
          motor(c, DcMotorCfg(12, 15, 5)),
          pc(50, INA219_CALC_ADDRESS(1, 0))
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

    float BrushHead::GetPower() {
        return this->pc.GetLatestSample().Power;
    }

    void BrushHead::RaiseEmergency()
    {
    }

    Report &BrushHead::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();
        this->report["Motor"] = this->motor.GetReport();
        this->report["Power"] = this->pc.GetReport();

        return this->report;
    }
}
