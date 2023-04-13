#include "Misc/RingBufferTest.cpp"
#include "Misc/SlidingRangeTest.cpp"
#include "StateMachine/StateMachineTest.cpp"

namespace TestSuite
{
    void StartTests()
    {
        RingBufferTest::Run();
        SlidingRangeTest::Run();
        StateMachineTest::Run();
    }
}
