#pragma once
#include <string>

namespace CleaningDevice::StateMachine
{
    template <typename T> class Message;

    template <typename T>
    class State
    {
    private:
        std::string name;

    protected:
        State(std::string name) : name(name) {}

    public:
        virtual ~State() {}
        std::string GetName() { return this->name; }
        virtual State<T> &Handle(T &fsm, Message<T> &msg) = 0;
        virtual std::string ToString() = 0;
    };
}
