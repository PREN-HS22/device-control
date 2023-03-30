#pragma once
#include <HX711_ADC.h>
#include "BaseComponent.hpp"
#include "../Misc/SlidingRange.hpp"

namespace PREN::Components
{
    template <std::size_t D = 1, std::size_t S = 20> // D: Duration in s, S: samples/s
    class LoadCell : public BaseComponent
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
        Status status;
        SlidingRange<(D * S)> data;

    public:
        LoadCell(Controller *c, unsigned int dout, unsigned int sck);
        virtual ~LoadCell();

        float GetValue();
        void Tare();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
