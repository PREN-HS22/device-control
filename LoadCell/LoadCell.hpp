#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "HX711_ADC.h"

namespace PREN::Component
{
    template <unsigned int P1, unsigned int P2>
    class LoadCell : public Emergency, public Reportable
    {
    private:
        HX711_ADC device;
        Report status;

    public:
        LoadCell();
        virtual ~LoadCell();

        float GetValue();
        void Tare();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
