#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "Controller.hpp"

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
