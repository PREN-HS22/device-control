#include <ArduinoSTL.h>
#include <map>
#include "../../src/StateMachine/Message.hpp"
#include "../../src/StateMachine/State.hpp"
#define TYPENAME(T) #T
using CleaningDevice::StateMachine::Message;
using CleaningDevice::StateMachine::State;

namespace StateMachineTest
{
    class MockFSM;
    using MockMsg = Message<MockFSM>;
    using MockState = State<MockFSM>;
    extern std::map<std::string, MockState *> *states;

    class StateA : public MockState
    {
    public:
        StateA() : MockState(TYPENAME(StateA)) {}
        ~StateA() {}

        MockState &Handle(MockFSM &fsm, MockMsg &msg)
        {
            Serial.print("StateA::Handle(MockMsg(");
            Serial.print(msg.GetName());
            Serial.println("))");
            return *(*StateMachineTest::states)["B"];
        }
    };

    class StateB : public MockState
    {
    public:
        StateB() : MockState(TYPENAME(StateB)) {}
        ~StateB() {}

        MockState &Handle(MockFSM &fsm, MockMsg &msg)
        {
            Serial.print("StateB::Handle(MockMsg(");
            Serial.print(msg.GetName());
            Serial.println("))");
            return *(*StateMachineTest::states)["C"];
        }
    };

    class StateC : public MockState
    {
    public:
        StateC() : MockState(TYPENAME(StateC)) {}
        ~StateC() {}

        MockState &Handle(MockFSM &fsm, MockMsg &msg)
        {
            Serial.print("StateC::Handle(MockMsg(");
            Serial.print(msg.GetName());
            Serial.println("))");
            return *(*StateMachineTest::states)["C"];
        }
    };
}
