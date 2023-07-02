#include "Conveyor.hpp"

namespace CleaningDevice::Components
{
    Conveyor::Conveyor(Controller &c)
        : AbstractComponent(c),
          stepper(c, 200, 16, 17),
          rpm(20.f)
    {
    }

    Conveyor::~Conveyor()
    {
    }

    void Conveyor::Start()
    {
        this->stepper.MoveIndefinite(this->rpm);
    }

    void Conveyor::Stop()
    {
        this->stepper.Stop();
    }

    void Conveyor::SetRpm(float rpm)
    {
        this->rpm = rpm;
        if (this->IsRunning())
        {
            this->stepper.MoveIndefinite(rpm);
        }
    }

    float Conveyor::GetRpm()
    {
        return this->rpm;
    }

    bool Conveyor::IsRunning()
    {
        return this->stepper.IsRunning();
    }

    void Conveyor::RaiseEmergency()
    {
        this->stepper.Stop();
    }

    Report &Conveyor::GetReport()
    {
        this->report["RPM"] = this->GetRpm();
        this->report["Stepper"] = this->stepper.GetReport();

        return this->report;
    }
}
