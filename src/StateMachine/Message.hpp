#pragma once
#include <string>

namespace CleaningDevice::StateMachine
{
    template <typename T>
    class Message
    {
    private:
        std::string name;

    protected:
        Message(std::string name) : name(name) {}

    public:
        virtual ~Message() {}
        std::string GetName() { return this->name; }
    };
}
