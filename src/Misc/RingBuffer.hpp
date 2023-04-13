#pragma once
#include <ArduinoSTL.h>
#include <array>

namespace CleaningDevice
{
    template <typename T, std::size_t N>
    class RingBuffer
    {
    private:
        bool overflowed;
        unsigned int head, tail;
        std::array<T, N> buffer;
        template <std::size_t M>
        friend class SlidingRange;

        void advanceHead()
        {
            ++this->head;
            this->head = this->head < N ? this->head : 0;
        }

        void advanceTail()
        {
            ++this->tail;
            this->tail = this->tail < N ? this->tail : 0;
        }

        class Iterator
        {
        private:
            RingBuffer<T, N> *rb;
            unsigned int next;
            bool overflowed;

        public:
            Iterator(RingBuffer *rb) : rb(rb), next(rb->tail), overflowed(rb->overflowed) {}
            ~Iterator() {}

            Iterator &operator++()
            {
                this->next++;
                // Wrap around tail if it exceeds the buffer size
                this->next = this->next < N ? this->next : 0;

                return *this;
            }

            Iterator &operator+(unsigned int i)
            {
                this->next = (this->next + i) % N;
                this->overflowed = false;
                return *this;
            }

            bool operator!=(std::size_t i)
            {
                if (this->overflowed && this->next == i)
                {
                    this->overflowed = false;
                    return true;
                }

                return this->next != i;
            }

            T const &operator*() const { return this->rb->buffer.at(this->next); }
            T &operator*() { return this->rb->buffer.at(this->next); }
        };

    public:
        RingBuffer() : overflowed(false), head(0), tail(0) {}
        ~RingBuffer() {}

        void Push(T obj)
        {
            if (this->overflowed)
            {
                this->advanceTail();
            }

            this->buffer[this->head] = obj;
            this->advanceHead();
            this->overflowed = this->tail == this->head;
        }

        T Pop()
        {
            if (this->IsEmpty())
            {
                return;
            }

            T next = this->buffer[this->tail];
            this->advanceTail();
            this->overflowed = false;
            return next;
        }

        T PeekHead()
        {
            if (this->IsEmpty())
            {
                return;
            }

            auto prevHead = (this->head - 1 + N) % N;
            return this->buffer[prevHead];
        }

        T PeekTail()
        {
            if (this->tail == this->head && !this->overflowed)
            {
                return;
            }
            return this->buffer[this->tail];
        }

        void Clear()
        {
            this->overflowed = false;
            this->head = 0;
            this->tail = 0;
        }

        std::size_t GetCapacity() const noexcept { return N; }
        bool IsEmpty() { return this->tail == this->head && !this->overflowed; }

        // Provide constant iterator for range iteration
        Iterator begin() const
        {
            return Iterator(this);
        }
        std::size_t end() const { return this->head; }
    };
}
