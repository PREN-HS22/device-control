#include "ElectroMagnet.hpp"

namespace PREN::Components
{
    ElectroMagnet::ElectroMagnet(Controller *c) : BaseComponent(c)
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
    }

    void ElectroMagnet::RaiseEmergency()
    {
    }

    Report &ElectroMagnet::GetStatusReport()
    {
        return this->report;
    }
}
