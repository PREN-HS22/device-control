#include "ElectroMotor.hpp"

namespace PREN::Components
{
    ElectroMotor::ElectroMotor(Controller *c) : BaseComponent(c), status(Idle)
    {
    }

    ElectroMotor::~ElectroMotor()
    {
    }

    void ElectroMotor::Rotate(float angularVel, float torque)
    {
        this->angularVel = angularVel;
        this->torque = torque;
    }

    void ElectroMotor::Rotate(float angularVel, float torque, float duration)
    {
        this->angularVel = angularVel;
        this->torque = torque;
    }

    void ElectroMotor::Stop()
    {
        this->angularVel = 0.f;
        this->torque = 0.f;
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
