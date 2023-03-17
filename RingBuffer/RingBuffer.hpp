#pragma once
#include <ArduinoSTL.h>
#include <array>

namespace PREN
{
    template <typename T, std::size_t N>
    class RingBuffer
    {
    private:
        bool empty;
        unsigned int head, tail;
        std::array<T, N> buffer;

    public:
        RingBuffer();
        ~RingBuffer();

        std::size_t GetCapacity();
        void Push(T obj);
        void Clear();
        bool IsEmpty();
        T Pop();
        T PeekTail();
        T PeekHead();
    };
}
