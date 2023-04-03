#include "SlidingRange.hpp"

namespace PREN
{
    template <std::size_t N>
    SlidingRange<N>::SlidingRange() : capacity(N)
    {
    }

    template <std::size_t N>
    SlidingRange<N>::~SlidingRange()
    {
    }

    template <std::size_t N>
    void SlidingRange<N>::AddValue(float value)
    {
        this->buffer.Push(value);
    }

    template <std::size_t N>
    float SlidingRange<N>::Derive(float x, float dx)
    {
        unsigned int _x = ((unsigned int)x) % this->capacity;
        unsigned int offset = this->buffer.tail;
        unsigned int a = (_x + offset) % this->capacity;
        unsigned int b = (a + 1) % this->capacity;

        float yb = this->buffer.buffer.at(b);
        float ya = this->buffer.buffer.at(a);

        return (yb - ya) * (1 / dx);
    }

    template <std::size_t N>
    float SlidingRange<N>::Integrate(float a, float b, float dx)
    {
        auto _a = (unsigned int)(this->capacity * a);
        auto _b = (unsigned int)(this->capacity * b);
        unsigned int span = abs(_b - _a);

        if ((unsigned int)(abs(b - a) + 0.5f) == 0 || span > this->capacity)
        {
            return 0.f;
        }

        auto temp = _a + this->buffer.tail;
        auto x1 = temp < this->capacity ? temp : temp - this->capacity;
        bool reverse = _b < _a;

        // \int_a^b y dx = (0.5 * (y_a + y_b) + (\sum_{i=a+1}^b y_i)) * dx

        float sum = 0.f;
        unsigned int i = x1 + 1;

        while (i != x2)
        {
            sum += this->buffer.buffer.at(i);

            if (++i > this->capacity)
            {
                i = 0;
            }
        }

        sum += 0.5f * (this->buffer.buffer.at(x1) + this->buffer.buffer.at(x2));
        return sum * dx;
    }
}
