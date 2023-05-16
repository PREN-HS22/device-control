#include "BrushHead.hpp"

namespace CleaningDevice::Components
{
    BrushHead::BrushHead(Controller &c, State<BrushHead> &start)
        : BaseComponent<BrushHead>(c, start)
    {
    }

    BrushHead::~BrushHead()
    {
    }

    void BrushHead::Start()
    {
    }

    void BrushHead::Stop()
    {
    }

    void BrushHead::SetSpeed(float s)
    {
    }

    float BrushHead::GetSpeed()
    {
    }

    void BrushHead::RaiseEmergency()
    {
    }

    Report &BrushHead::GetReport()
    {
        return this->report;
    }
}
