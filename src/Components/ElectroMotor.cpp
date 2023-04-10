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
        // Stop device
    }

    Report &ElectroMotor::GetReport()
    {
        this->report["Status"] = this->GetStatus();
        this->report["AngularVelocity"] = this->angularVel;
        this->report["Torque"] = this->torque;

        return this->report;
    }
}