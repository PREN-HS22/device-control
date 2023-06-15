#pragma once
#include "../Misc/Emergency.hpp"
#include "../Misc/Reportable.hpp"

namespace CleaningDevice
{
    class Controller;
}

using CleaningDevice::Emergency,
    CleaningDevice::Reportable,
    CleaningDevice::Controller,
    CleaningDevice::Report;

namespace CleaningDevice::Components
{
    class AbstractComponent
        : public Emergency,
          public Reportable
    {
    protected:
        Controller &ctrl;
        Report report;

        AbstractComponent(Controller &c) : ctrl(c) {}
    };
}
