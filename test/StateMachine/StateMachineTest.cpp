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
            Serial.println(e.second->GetName().c_str());
        }
    }

    void StateTest()
    {
        (*states)["A"] = new StateA();
        (*states)["B"] = new StateB();
        (*states)["C"] = new StateC();

        for (auto e : *states)
        {
            Serial.println(e.second->GetName().c_str());
        }
    }

    void FSMTest()
    {
        auto fsm = new MockFSM((*states)["A"]);
        fsm->UpdateState(*(*messages)["A"]);
        fsm->UpdateState(*(*messages)["B"]);
        fsm->UpdateState(*(*messages)["C"]);
        delete fsm;
    }

    void Run()
    {
        TEST(MessageTest);
        TEST(StateTest);
        TEST(FSMTest);

        for (auto [_, msg] : *messages) {
            delete msg;
        }

        for (auto [_, s] : *states) {
            delete s;
        }

        delete messages, states;
    }
}
