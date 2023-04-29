#pragma once
#include "BaseComponent.hpp"
#include <LiquidCrystal_I2C.h>
#include <cstdint>

namespace CleaningDevice::Components
{
    class Lcd : public LiquidCrystal_I2C, public BaseComponent<Lcd>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    public:
        Lcd(Controller &c, State<Lcd> &start, std::uint8_t address, std::uint8_t cols, std::uint8_t rows);
        ~Lcd();

        void RaiseEmergency();
        Report &GetReport();
    };
}
