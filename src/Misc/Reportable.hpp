#pragma once
#include "Report.hpp"

namespace CleaningDevice
{
    class Reportable
    {
    public:
        virtual Report &GetReport() = 0;
    };
}
