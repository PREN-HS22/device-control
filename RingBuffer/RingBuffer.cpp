#include "RingBuffer.hpp"

namespace PREN
{
    template <typename T, std::size_t N>
    RingBuffer<T, N>::RingBuffer()
    {
        this->empty = true;
        this->head = 0;
        this->tail = 0;
    }

    template <typename T, std::size_t N>
    RingBuffer<T, N>::~RingBuffer()
    {
    }

    template <typename T, std::size_t N>
    std::size_t RingBuffer<T, N>::GetCapacity()
    {
        return this->buffer->max_size;
    }

    template <typename T, std::size_t N>
    void RingBuffer<T, N>::Push(T obj)
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

    template <typename T, std::size_t N>
    void RingBuffer<T, N>::Clear()
    {
        this->empty = true;
        this->head = 0;
        this->tail = 0;
    }

    template <typename T, std::size_t N>
    bool RingBuffer<T, N>::IsEmpty()
    {
        return this->empty;
    }

    template <typename T, std::size_t N>
    T RingBuffer<T, N>::Pop()
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

    template <typename T, std::size_t N>
    T RingBuffer<T, N>::PeekHead()
    {
        return this->buffer[this->head];
    }

    template <typename T, std::size_t N>
    T RingBuffer<T, N>::PeekTail()
    {
        return this->buffer[this->tail];
    }

    template <typename T, std::size_t N>
    typename std::array<T, N>::const_iterator RingBuffer<T, N>::begin() const
    {
        return this->buffer->begin();
    }

    template <typename T, std::size_t N>
    typename std::array<T, N>::const_iterator RingBuffer<T, N>::cbegin() const
    {
        return this->buffer->cbegin();
    }

    template <typename T, std::size_t N>
    typename std::array<T, N>::const_iterator RingBuffer<T, N>::end() const
    {
        return this->buffer->end();
    }
   
    template <typename T, std::size_t N>
    typename std::array<T, N>::const_iterator RingBuffer<T, N>::cend() const
    {
        return this->buffer->cend();
    }
}
