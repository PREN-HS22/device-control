#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "HX711_ADC.h"
#include "SlidingRange.hpp"

namespace PREN::Component
{
    template <std::size_t D, std::size_t S>
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
