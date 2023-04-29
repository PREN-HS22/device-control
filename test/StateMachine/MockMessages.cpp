#include "../../src/StateMachine/Message.hpp"
#define TYPENAME(T) #T
using CleaningDevice::StateMachine::Message;

namespace StateMachineTest
{
    class MockFSM;
    using MockMsg = Message<MockFSM>;

    class MessageA : public MockMsg
    {
    public:
        MessageA() : MockMsg(TYPENAME(MessageA)) {}
        ~MessageA() {}
    };

    class MessageB : public MockMsg
    {
    public:
        MessageB() : MockMsg(TYPENAME(MessageB)) {}
        ~MessageB() {}
    };

    class MessageC : public MockMsg
    {
    public:
        MessageC() : MockMsg(TYPENAME(MessageC)) {}
        ~MessageC() {}
    };
}
