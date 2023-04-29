#include "../../src/StateMachine/FiniteStateMachine.hpp"
#include "../../src/StateMachine/State.hpp"
using CleaningDevice::StateMachine::FiniteStateMachine;
using CleaningDevice::StateMachine::State;

namespace StateMachineTest
{
    class MockFSM : public FiniteStateMachine<MockFSM>
    {
    public:
        MockFSM(State<MockFSM> &start) : FiniteStateMachine<MockFSM>(start) {}
        ~MockFSM() {}
    };
}
