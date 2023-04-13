#include "Lcd.hpp"

namespace CleaningDevice::Components
{
    Lcd::Lcd(Controller *c) : BaseComponent(c), status(Idle)
    {
    }

    Lcd::~Lcd()
    {
    }

    Lcd::Status Lcd::GetStatus()
    {
        return this->status;
    }

    void Lcd::RaiseEmergency()
    {
        // Display emergency
    }

    Report &Lcd::GetReport()
    {
        this->report["Status"] = this->GetStatus();

        return this->report;
    }
}
