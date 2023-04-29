#include "Lcd.hpp"

namespace CleaningDevice::Components
{
    Lcd::Lcd(Controller &c, State<Lcd> &start)
        : BaseComponent<Lcd>(c, start)
    {
    }

    Lcd::~Lcd()
    {
    }

    void Lcd::RaiseEmergency()
    {
        // Display emergency
    }

    Report &Lcd::GetReport()
    {
        this->report["Status"] = this->GetState().GetName();

        return this->report;
    }
}
