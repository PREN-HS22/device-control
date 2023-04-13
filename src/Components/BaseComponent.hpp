#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace CleaningDevice
{
    class Controller;
}

using CleaningDevice::Emergency, CleaningDevice::Reportable, CleaningDevice::Controller, CleaningDevice::Report;

namespace CleaningDevice::Components
{
    class BaseComponent : public Emergency, public Reportable
    {
    protected:
        Controller *ctrl;
        Report report;
        BaseComponent(Controller *c);
    };
}
