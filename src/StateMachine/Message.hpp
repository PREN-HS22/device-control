#pragma once
#include <Arduino.h>

namespace CleaningDevice::StateMachine
{
    template <typename T>
    class Message
    {
    private:
        String name;

    protected:
        Message(String name) : name(name) {}

    public:
        virtual ~Message() {}
        String GetName() { return this->name; }
    };
}
