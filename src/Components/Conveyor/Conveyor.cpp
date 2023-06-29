#include "Conveyor.hpp"

namespace CleaningDevice::Components
{
    Conveyor::Conveyor(Controller &c)
        : AbstractComponent(c),
          stepper(c, AccelStepper::FULL2WIRE, 17, 16),
          maxStepperSpeed(5000.f),
          speedFraction(.5f)
    {
    }

    Conveyor::~Conveyor()
    {
    }

    void Conveyor::Start()
    {
        this->stepper.MoveIndefinite(this->speedFraction * this->maxStepperSpeed);
    }

    void Conveyor::Stop()
    {
        this->stepper.Stop();
    }

    void Conveyor::SetSpeed(float fraction)
    {
        this->speedFraction = std::clamp(fraction, 0.f, 1.f);
        this->stepper.MoveIndefinite(this->speedFraction * this->maxStepperSpeed);
    }

    float Conveyor::GetSpeed()
    {
        return this->speedFraction;
    }

    void Conveyor::RaiseEmergency()
    {
        this->stepper.Stop();
    }

    Report &Conveyor::GetReport()
    {
        this->report["Speed"] = this->GetSpeed();
        this->report["Stepper"] = this->stepper.GetReport();

        return this->report;
    }
}
