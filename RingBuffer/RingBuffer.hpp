#pragma once
#include <stdlib.h>

namespace PREN
{
    template <typename T>
    class RingBuffer
    {
    private:
        size_t capacity;
        bool empty;
        unsigned int head, tail;
        T buffer[];

    public:
        RingBuffer(size_t capacity);
        ~RingBuffer();

        size_t GetCapacity();
        void Add(T obj);
        void Clear();
        bool IsEmpty();
        T GetNext();
        T PeekTail();
        T PeekHead();
    };
}
