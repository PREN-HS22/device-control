#include "RingBuffer.hpp"

namespace PREN
{
    template <typename T>
    RingBuffer<T>::RingBuffer(size_t capacity)
    {
        this->capacity = capacity;
        this->empty = true;
        this->head = 0;
        this->tail = 0;
        this->buffer = new T[capacity];
    }

    template <typename T>
    RingBuffer<T>::~RingBuffer()
    {
        delete this->buffer;
    }

    template <typename T>
    size_t RingBuffer<T>::GetCapacity()
    {
        return this->capacity;
    }

    template <typename T>
    void RingBuffer<T>::Add(T obj)
    {
        this->head = this->empty ? this->head : (this->head + 1) % this->capacity;
        this->buffer[this->head] = obj;
        this->empty = false;

        if (this->tail == this->head && !this->empty)
        {
            this->tail = (this->tail + 1) % this->capacity;
        }
    }

    template <typename T>
    void RingBuffer<T>::Clear()
    {
        this->empty = true;
        this->head = 0;
        this->tail = 0;
    }

    template <typename T>
    bool RingBuffer<T>::IsEmpty()
    {
        return this->empty;
    }

    template <typename T>
    T RingBuffer<T>::GetNext()
    {
        if (!this->HasNext())
        {
            return;
        }

        T next = this->buffer[this->tail];
        this->tail = (this->tail + 1) % this->capacity;
        this->empty = this->tail == this->head;
        return next;
    }

    template <typename T>
    T RingBuffer<T>::PeekHead()
    {
        return this->buffer[this->head];
    }

    template <typename T>
    T RingBuffer<T>::PeekTail()
    {
        return this->buffer[this->tail];
    }
}
