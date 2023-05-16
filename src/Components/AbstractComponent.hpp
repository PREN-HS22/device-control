#pragma once
#include "../Misc/Emergency.hpp"
#include "../Misc/Reportable.hpp"
#include "../StateMachine/FiniteStateMachine.hpp"

namespace CleaningDevice
{
    class Controller;
}

using CleaningDevice::Emergency,
    CleaningDevice::Reportable,
    CleaningDevice::Controller,
    CleaningDevice::Report,
    CleaningDevice::StateMachine::State,
    CleaningDevice::StateMachine::FiniteStateMachine;

namespace CleaningDevice::Components
{
    template <typename T>
    class AbstractComponent
        : public FiniteStateMachine<T>,
          public Emergency,
          public Reportable
    {
    protected:
        Controller &ctrl;
        Report report;

        AbstractComponent(Controller &c, State<T> &start) : ctrl(c), FiniteStateMachine<T>(start) {}
    };
}
