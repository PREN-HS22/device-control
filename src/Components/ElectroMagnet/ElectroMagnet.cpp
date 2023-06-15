#include "ElectroMagnet.hpp"

namespace CleaningDevice::Components
{
    ElectroMagnet::ElectroMagnet(Controller &c)
        : AbstractComponent(c)
    {
    }

    ElectroMagnet::~ElectroMagnet()
    {
    }

    void ElectroMagnet::Enable()
    {
    }

    void ElectroMagnet::Disable()
    {
    }

    bool ElectroMagnet::IsEnabled()
    {
    }

    void ElectroMagnet::Rotate(float angle, float speed)
    {
    }

    void ElectroMagnet::Cycle(int dir)
    {
    }

    void ElectroMagnet::RaiseEmergency()
    {
        // Stop device
    }

    Report &ElectroMagnet::GetReport()
    {
        this->report[""] = "";

        return this->report;
    }
}
