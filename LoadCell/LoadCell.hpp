#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "HX711_ADC.h"
#include "SlidingRange.hpp"

namespace PREN::Components
{
    template <std::size_t D = 1, std::size_t S = 20> // D: Duration in s, S: samples/s
    class LoadCell : public Emergency, public Reportable
    {
    private:
        HX711_ADC device;
        Report status;
        SlidingRange<D * S> data;

    public:
        LoadCell(unsigned int dout, unsigned int sck);
        virtual ~LoadCell();

        float GetValue();
        void Tare();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
