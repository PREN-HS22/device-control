#pragma once
#include "../AbstractComponent.hpp"
#include <LiquidCrystal_I2C.h>
#include <cstdint>

namespace CleaningDevice::Components
{
    class Lcd : public LiquidCrystal_I2C, public AbstractComponent
    {
    private:
        std::string lastMessage;

    public:
        Lcd(Controller &c, std::uint8_t address, std::uint8_t cols, std::uint8_t rows);
        ~Lcd();

        template <typename T>
        void print(T msg);

        template <typename T>
        void println(T msg);

        void RaiseEmergency();
        Report &GetReport();
    };
}
