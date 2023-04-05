#include "../tests.hpp"
#include "../assertions.hpp"
#include "../../src/Misc/RingBuffer.hpp"

namespace RingBufferTest
{
    PREN::RingBuffer<int, 10> rb;

    void CapacityTest()
    {
        assertEqual(rb.GetCapacity(), 10);
    }

    void ClearTest()
    {
        rb.Clear();
        assertTrue(rb.IsEmpty());

        rb.Push(1);
        assertFalse(rb.IsEmpty());

        rb.Clear();
        assertTrue(rb.IsEmpty());
    }

    void SinglePushTest()
    {
        rb.Clear();
        assertTrue(rb.IsEmpty());

        rb.Push(1);
        assertFalse(rb.IsEmpty());
    }

    void SinglePopTest()
    {
        int n = 5;

        rb.Clear();
        assertTrue(rb.IsEmpty());

        rb.Push(n);
        assertEqual(rb.Pop(), n);
    }

    void FillUpTest()
    {
        rb.Clear();
        assertTrue(rb.IsEmpty());

        for (int i = 0; i < 10; i++)
        {
            rb.Push(i);
        }

        assertFalse(rb.IsEmpty());

        for (int i = 0; i < 10; i++)
        {
            assertEqual(rb.Pop(), i);
        }

        assertTrue(rb.IsEmpty());
    }

    void OverflowTest()
    {
        rb.Clear();
        assertTrue(rb.IsEmpty());

        for (int i = 0; i < 15; i++)
        {
            rb.Push(i);
        }

        assertFalse(rb.IsEmpty());

        for (int i = 5; i < 15; i++)
        {
            assertEqual(rb.Pop(), i);
        }

        assertTrue(rb.IsEmpty());
    }

    void PeekTest()
    {
        rb.Clear();
        assertTrue(rb.IsEmpty());

        rb.Push(1);
        assertEqual(rb.PeekTail(), 1);
        assertEqual(rb.PeekHead(), 1);

        rb.Push(2);
        rb.Push(3);
        assertEqual(rb.PeekHead(), 3);

        rb.Pop();
        rb.Push(4);
        assertEqual(rb.PeekTail(), 2);
        assertEqual(rb.PeekHead(), 4);
    }

    void IteratorTest()
    {
        rb.Clear();
        assertTrue(rb.IsEmpty());

        for (int i = 0; i < 18; i++)
        {
            rb.Push(i);
        }

        int i = 8;
        for (auto e : rb)
        {
            assertEqual(e, i++);
        }
    }

    void Run()
    {
        TEST(CapacityTest);
        TEST(ClearTest);
        TEST(SinglePushTest);
        TEST(SinglePopTest);
        TEST(FillUpTest);
        TEST(OverflowTest);
        TEST(PeekTest);
        TEST(IteratorTest);
    }
}
