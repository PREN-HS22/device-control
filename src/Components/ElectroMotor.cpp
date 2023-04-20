#include "ElectroMotor.hpp"

namespace CleaningDevice::Components
{
    ElectroMotor::ElectroMotor(Controller *c, State<ElectroMotor> *start)
        : BaseComponent<ElectroMotor>(c, start)
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

    void ElectroMotor::RaiseEmergency()
    {
        // Stop device
    }

    Report &ElectroMotor::GetReport()
    {
        this->report["Status"] = this->GetState()->GetName();
        this->report["AngularVelocity"] = this->angularVel;
        this->report["Torque"] = this->torque;

        return this->report;
    }
}
