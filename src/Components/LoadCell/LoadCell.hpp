#pragma once
#include <HX711_ADC.h>
#include "../BaseComponent.hpp"
#include "../../Misc/SlidingRange.hpp"

namespace CleaningDevice::Components
{
    template <std::size_t D = 1, std::size_t S = 20> // D: Duration in s, S: samples/s
    class LoadCell : public BaseComponent<LoadCell<D, S>>
    {
    public:
        enum Status
        {
            Idle,
            Taring,
            Active
        };

    private:
        HX711_ADC device;
        SlidingRange<(D * S)> data;

    public:
        LoadCell(Controller &c, unsigned int dout, unsigned int sck)
            : BaseComponent<LoadCell<D, S>>(c, null), // TODO: Define start state
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
            if (this->device.update() != 0)
            {
                return this->device.getData();
            }
        }

        void Tare() {}

        void RaiseEmergency() {}

        Report &GetReport()
        {
            this->report["Status"] = this->GetState().GetName();
            return this->report;
        }
    };
}
