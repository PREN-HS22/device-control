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
        template <std::size_t M> friend class SlidingRange;

    public:
        RingBuffer() : empty(true), head(0), tail(0) {}
        ~RingBuffer() {}

        void Push(T obj)
        {
            this->head = this->empty ? this->head : this->head + 1;
            // Wrap around head if it exceeds the buffer size
            this->head = this->head < this->GetCapacity() ? this->head : 0;

            // Move tail ahead if head approaches
            this->tail = this->empty
                || this->head != this->tail
                ? this->tail : this->tail + 1;
            // Wrap around tail if it exceeds the buffer size
            this->tail = this->tail < this->GetCapacity() ? this->tail : 0;
            this->buffer[this->head] = obj;
            this->empty = false;
        }

        void Clear()
        {
            this->empty = true;
            this->head = 0;
            this->tail = 0;
        }

        T Pop()
        {
            if (this->empty)
            {
                return;
            }

            T next = this->buffer[this->tail];
            this->empty = this->tail == this->head;
            this->tail = this->empty ? this->tail : this->tail + 1;
            // Wrap around tail if it exceeds the buffer size
            this->tail = this->tail < this->GetCapacity() ? this->tail : 0;
            return next;
        }

        T PeekHead()
        {
            if (this->empty)
            {
                return;
            }
            return this->buffer[this->head];
        }

        T PeekTail()
        {
            if (this->empty)
            {
                return;
            }
            return this->buffer[this->tail];
        }

        std::size_t GetCapacity() const noexcept { return this->buffer.max_size(); }
        bool IsEmpty() { return this->empty; }

        // Provide constant iterator for range iteration
        typename std::array<T, N>::const_iterator begin() const { return this->buffer.begin(); }
        typename std::array<T, N>::const_iterator cbegin() const { return this->buffer.cbegin(); };
        typename std::array<T, N>::const_iterator end() const { return this->buffer.end(); }
        typename std::array<T, N>::const_iterator cend() const { return this->buffer.cend(); }
    };
}
