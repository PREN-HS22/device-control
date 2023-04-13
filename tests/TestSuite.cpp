#include "Misc/RingBufferTest.cpp"
#include "Misc/SlidingRangeTest.cpp"

namespace TestSuite
{
    void StartTests()
    {
        RingBufferTest::Run();
        SlidingRangeTest::Run();
    }
}
