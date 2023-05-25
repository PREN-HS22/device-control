#include "Lcd.hpp"
#include "LcdCharacters.hpp"

using CleaningDevice::LcdCharacters;

namespace CleaningDevice::Components
{
    Lcd::Lcd(Controller &c, State<Lcd> *start, std::uint8_t address, std::uint8_t cols, std::uint8_t rows)
        : AbstractComponent(c, start),
          LiquidCrystal_I2C(address, cols, rows)
    {
        // Register custom characters
        std::uint8_t i = 0;
        for (auto c : LcdCharacters)
        {
            this->createChar(i++, const_cast<std::uint8_t *>(c));
        }
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
        this->report["Status"] = this->GetState()->GetName();

        return this->report;
    }
}
