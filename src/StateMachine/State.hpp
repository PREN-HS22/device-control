#pragma once
#include <Arduino.h>

namespace CleaningDevice::StateMachine
{
    template <typename T> class Message;

    template <typename T>
    class State
    {
    private:
        String name;

    protected:
        State(String name) : name(name) {}
        ~State() {}

    public:
        String GetName() { return this->name; }
        virtual State<T> *Handle(T *fsm, Message<T> *msg) = 0;
    };
}
