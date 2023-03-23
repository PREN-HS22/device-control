#include "ElectroMotor.hpp"

namespace PREN::Components
{
    ElectroMotor::ElectroMotor(Controller *c) : BaseComponent(c)
    {
    }

    ElectroMotor::~ElectroMotor()
    {
    }

    void ElectroMotor::Rotate(float angularVelocity, float torque, float duration)
    {
    }

    void ElectroMotor::Stop()
    {
    }

    void ElectroMotor::RaiseEmergency()
    {
    }

    void ElectroMotor::RaiseEmergency()
    {
    }

    Report &ElectroMotor::GetStatusReport()
    {
        return this->report;
    }
}
