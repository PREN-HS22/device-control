#include "ElectroMagnet.hpp"

namespace PREN::Components
{
    ElectroMagnet::ElectroMagnet(Controller *c) : BaseComponent(c), status(Idle)
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

    ElectroMagnet::Status ElectroMagnet::GetStatus()
    {
        return this->status;
    }

    void ElectroMagnet::RaiseEmergency()
    {
    }

    Report &ElectroMagnet::GetReport()
    {
        return this->report;
    }
}
