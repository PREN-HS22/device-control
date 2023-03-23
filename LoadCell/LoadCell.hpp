#pragma once
#include "BaseComponent.hpp"
#include "HX711_ADC.h"
#include "SlidingRange.hpp"

namespace PREN::Components
{
    template <std::size_t D = 1, std::size_t S = 20> // D: Duration in s, S: samples/s
    class LoadCell : public BaseComponent
    {
    private:
        HX711_ADC device;
        SlidingRange<D * S> data;

    public:
        LoadCell(Controller *c, unsigned int dout, unsigned int sck);
        virtual ~LoadCell();

        float GetValue();
        void Tare();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
