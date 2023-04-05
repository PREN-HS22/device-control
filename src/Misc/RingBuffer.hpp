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
        template <std::size_t M>
        friend class SlidingRange;
        class Iterator
        {
        private:
            std::array<T, N> *range;
            unsigned int next, end;

        public:
            Iterator(std::array<T, N> *range, unsigned int next, unsigned int end) : range(range), next(next), end(end) {}
            ~Iterator() {}

            Iterator &operator++()
            {
                this->next++;
                this->next = this->next < N ? this->next : 0;
                return *this;
            }

            T const &operator*() const { return this->range->at(next); }
            T &operator*() { return this->range->at(next); }

            bool operator!=(Iterator const &rhs) const
            {
                if (rhs.next == rhs.end)
                {
                    return false;
                }

                if (this->next == rhs.end)
                {
                    ++rhs;
                }

                return true;
            }
        };

    public:
        RingBuffer() : empty(true), head(0), tail(0) {}
        ~RingBuffer() {}

        void Push(T obj)
        {
            this->head = this->empty ? this->head : this->head + 1;
            // Wrap around head if it exceeds the buffer size
            this->head = this->head < this->GetCapacity() ? this->head : 0;

            // Move tail ahead if head approaches
            this->tail = this->empty || this->head != this->tail
                             ? this->tail
                             : this->tail + 1;
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
        Iterator begin() const { return Iterator(&this->buffer, this->tail, this->head); }
        Iterator end() const { return Iterator(&this->buffer, this->head - 1, this->head); }
    };
}
