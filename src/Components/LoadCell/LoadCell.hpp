#pragma once
#include <HX711_ADC.h>
#include "../AbstractComponent.hpp"
#include "../../Misc/SlidingRange.hpp"

namespace CleaningDevice::Components
{
    template <std::size_t D = 1, std::size_t S = 20> // D: Duration in s, S: samples/s
    class LoadCell : public AbstractComponent
    {
    private:
        HX711_ADC device;
        SlidingRange<(D * S)> data;

    public:
        LoadCell(Controller &c, std::uint8_t dout, std::uint8_t sck)
            : AbstractComponent(c), // TODO: Define start state
              device(dout, sck)
        {
            this->device.setSamplesInUse(10);
            this->device.begin();
            this->device.setTareOffset(0);
            this->device.start(2000, true);

            if (this->device.getTareTimeoutFlag())
            {
            }
            else
            {
                this->device.setCalFactor(696.f);
            }
        }

        ~LoadCell() { this->device.powerDown(); }

        float GetValue()
        {
            return this->device.getData();
        }

        void Tare() {}

        void RaiseEmergency() {}

        Report &GetReport()
        {
            this->report[""] = "";

            return this->report;
        }
    };
}
