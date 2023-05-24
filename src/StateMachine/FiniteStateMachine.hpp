#pragma once
#include "Message.hpp"
#include "State.hpp"

namespace CleaningDevice::StateMachine
{
    template <typename T>
    class FiniteStateMachine
    {
    protected:
        State<T> *state;

        FiniteStateMachine(State<T> *start) : state(start) {}

    public:
        virtual ~FiniteStateMachine() {}
        void UpdateState(Message<T> &msg) { this->state = this->state->Handle(this, msg); }
        State<T> *GetState() { return this->state; }
    };
}
