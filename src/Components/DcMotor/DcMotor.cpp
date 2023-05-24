#include "DcMotor.hpp"

namespace CleaningDevice::Components
{
    DcMotor::DcMotor(Controller &c, State<DcMotor> *start)
        : AbstractComponent(c, start)
    {
    }

    DcMotor::~DcMotor()
    {
    }

    void DcMotor::Rotate(float angularVel, float torque)
    {
        this->angularVel = angularVel;
        this->torque = torque;
    }

    void DcMotor::Rotate(float angularVel, float torque, float duration)
    {
        this->angularVel = angularVel;
        this->torque = torque;
    }

    void DcMotor::Stop()
    {
        this->angularVel = 0.f;
        this->torque = 0.f;
    }

    void DcMotor::RaiseEmergency()
    {
        // Stop device
    }

    Report &DcMotor::GetReport()
    {
        this->report["Status"] = this->GetState()->GetName();
        this->report["AngularVelocity"] = this->angularVel;
        this->report["Torque"] = this->torque;

        return this->report;
    }
}
