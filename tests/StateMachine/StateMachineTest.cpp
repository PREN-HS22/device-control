#include <ArduinoSTL.h>
#include <map>
#include "../tests.hpp"
#include "../assertions.hpp"
#include "MockMessages.cpp"
#include "MockStates.cpp"
#include "MockFSM.cpp"

namespace StateMachineTest
{
    auto messages = new std::map<std::string, Message<MockFSM> *>();
    auto states = new std::map<std::string, State<MockFSM> *>();

    void MessageTest()
    {
        (*messages)["A"] = new MessageA();
        (*messages)["B"] = new MessageB();
        (*messages)["C"] = new MessageC();

        for (auto e : *messages)
        {
            Serial.println(e.second->GetName());
        }
    }

    void StateTest()
    {
        (*states)["A"] = new StateA();
        (*states)["B"] = new StateB();
        (*states)["C"] = new StateC();

        for (auto e : *states)
        {
            Serial.println(e.second->GetName());
        }
    }

    void FSMTest()
    {
        auto fsm = new MockFSM(*(*states)["A"]);
        fsm->UpdateState(*(*messages)["A"]);
        fsm->UpdateState(*(*messages)["B"]);
        fsm->UpdateState(*(*messages)["C"]);
    }

    void Run()
    {
        TEST(MessageTest);
        TEST(StateTest);
        TEST(FSMTest);
    }
}
