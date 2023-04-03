#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN
{
    class Controller;
}

using PREN::Emergency, PREN::Reportable, PREN::Controller, PREN::Report;

namespace PREN::Components
{
    class BaseComponent : public Emergency, public Reportable
    {
    protected:
        Controller *ctrl;
        Report report;
        BaseComponent(Controller *c);
    };
}
