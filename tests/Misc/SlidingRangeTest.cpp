#include "../../src/Misc/SlidingRange.hpp"
#include "../tests.hpp"
#include "../assertions.hpp"

namespace SlidingRangeTest
{
    auto sr = new CleaningDevice::SlidingRange<10>();

    void CapacityTest()
    {
        // Uncomment only if private members of `SlidingRange` are public
        // assertEqual(sr->buffer.GetCapacity(), 11);
    }

    void AddValueTest()
    {
        std::array<float, 14> data{
            0.f,
            0.f,
            0.f,
            10.f,
            10.4f,
            13.f,
            17.f,
            28.5f,
            29.6f,
            29.1f,
            29.2f,
            29.2f,
            29.201f,
            29.198f};

        for (auto e : data)
        {
            sr->AddValue(e);
        }
    }

    void BufferTest()
    {
        // Uncomment only if private members of `SlidingRange` are public
        // int i = 0;
        // for (auto e : sr->buffer)
        // {
        //     i++;
        //     Serial.println(e);
        // }
        // assertEqual(i, 11);
    }

    void DeriveTest()
    {
        assertNear(-.5f, sr->Derive(.5f, 1.f), .001f);
    }

    void IntegrateTest()
    {
        auto integral = sr->Integrate(.2f, .7f, 1.f);
        Serial.println(integral);
        assertNear(125.3f, integral, .001f);
    }

    void Run()
    {
        // TEST(CapacityTest);
        TEST(AddValueTest);
        // TEST(BufferTest);
        TEST(DeriveTest);
        TEST(IntegrateTest);
    }
}
