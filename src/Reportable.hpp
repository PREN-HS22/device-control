#pragma once
#include "Report.hpp"

namespace PREN
{
    class Reportable
    {
    public:
        virtual Report &GetReport() = 0;
    };
}