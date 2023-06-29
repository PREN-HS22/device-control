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

    template <typename T>
    void Lcd::print(T msg) {
        LiquidCrystal_I2C::print(msg);
        this->lastMessage = std::to_string(msg);
    }

    template <typename T>
    void Lcd::println(T msg) {
        LiquidCrystal_I2C::println(msg);
        this->lastMessage = std::to_string(msg);
    }

    void Lcd::RaiseEmergency()
    {
        // Display emergency
        this->print("[Lcd] Emergency raised");
    }

    Report &Lcd::GetReport()
    {
        this->report["Last message"] = this->lastMessage.c_str();

        return this->report;
    }
}
