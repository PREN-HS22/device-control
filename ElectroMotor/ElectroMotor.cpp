#include "ElectroMotor.hpp"

namespace PREN::Components
{
    ElectroMotor::ElectroMotor(Controller *c) : BaseComponent(c), status(Idle)
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

    ElectroMotor::Status ElectroMotor::GetStatus()
    {
        return this->status;
    }

    void ElectroMotor::RaiseEmergency()
    {
    }

    Report &ElectroMotor::GetReport()
    {
        return this->report;
    }
}
