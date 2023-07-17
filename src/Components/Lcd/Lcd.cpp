#include "Lcd.hpp"
#include "LcdCharacters.hpp"

using CleaningDevice::LcdCharacters;

namespace CleaningDevice::Components
{
    Lcd::Lcd(Controller &c, std::uint8_t address, std::uint8_t cols, std::uint8_t rows)
        : AbstractComponent(c),
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
        this->print("[Lcd] Emergency raised");
    }

    Report &Lcd::GetReport()
    {
        this->report["Running"] = true;

        return this->report;
    }
}
