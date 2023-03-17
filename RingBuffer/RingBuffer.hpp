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
        friend class SlidingRange;

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

        // Provide constant iterator for range iteration
        typename std::array<T, N>::const_iterator begin() const;
        typename std::array<T, N>::const_iterator cbegin() const;
        typename std::array<T, N>::const_iterator end() const;
        typename std::array<T, N>::const_iterator cend() const;
    };
}
