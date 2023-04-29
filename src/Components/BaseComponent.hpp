#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"
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
    class BaseComponent
        : public FiniteStateMachine<T>,
          public Emergency,
          public Reportable
    {
    protected:
        Controller &ctrl;
        Report report;

        BaseComponent(Controller &c, State<T> &start) : ctrl(c), FiniteStateMachine<T>(start) {}
    };
}
