#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN::Component
{
    class LoadCell : public Emergency, public Reportable
    {
    public:
        LoadCell(unsigned int out, unsigned int clk);
        ~LoadCell();

        float GetValue();
        void Tare();
        void RaiseEmergency();
        Report* GetStatusReport();
    };

}
