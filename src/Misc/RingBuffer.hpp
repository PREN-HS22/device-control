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
        RingBuffer() : empty(true), head(0), tail(0) {}
        ~RingBuffer() {}

        void Push(T obj)
        {
            // Move head one slot ahead if buffer is not empty
            this->head = this->empty ? this->head : this->head + 1;
            // Wrap around head if it exceeds the buffer size
            this->head = this->head < this->GetCapacity() ? this->head : 0;

            this->buffer[this->head] = obj;
            this->empty = false;

            // Override and move tail one slot ahead if buffer is not empty
            if (this->tail == this->head && !this->empty)
            {
                this->tail++;
                // Wrap around tail if it exceeds the buffer size
                this->tail = this->tail < this->GetCapacity() ? this->tail : 0;
            }
        }

        void Clear()
        {
            this->empty = true;
            this->head = 0;
            this->tail = 0;
        }

        T Pop()
        {
            if (!this->IsEmpty())
            {
                return;
            }

            T next = this->buffer[this->tail];
            this->tail++;
            // Wrap around tail if it exceeds the buffer size
            this->tail = this->tail < this->GetCapacity() ? this->tail : 0;
            this->empty = this->tail == this->head;
            return next;
        }

        T PeekHead() { return this->buffer[this->head]; }
        T PeekTail() { return this->buffer[this->tail]; }
        std::size_t GetCapacity() { return this->buffer->max_size; }
        bool IsEmpty() { return this->empty; }

        // Provide constant iterator for range iteration
        typename std::array<T, N>::const_iterator begin() const { return this->buffer->begin(); }
        typename std::array<T, N>::const_iterator cbegin() const { return this->buffer->cbegin(); };
        typename std::array<T, N>::const_iterator end() const { return this->buffer->end(); }
        typename std::array<T, N>::const_iterator cend() const { return this->buffer->cend(); }
    };
}
