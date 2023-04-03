#pragma once
#include <ArduinoSTL.h>
#include "Derivable.hpp"
#include "Integratable.hpp"
#include "RingBuffer.hpp"

namespace PREN
{
    template <std::size_t N>
    class SlidingRange : public Derivable<float, float>, public Integratable<float, float>
    {
    private:
        RingBuffer<float, N + 1> buffer;
        std::size_t capacity = N;

    public:
        SlidingRange() {}
        ~SlidingRange() {}

        void AddValue(float value) { this->buffer.Push(value); }

        float Derive(float x, float dx)
        {
            unsigned int _x = ((unsigned int)x) % this->capacity;
            unsigned int offset = this->buffer.tail;
            unsigned int a = (_x + offset) % this->capacity;
            unsigned int b = (a + 1) % this->capacity;

            float yb = this->buffer.buffer.at(b);
            float ya = this->buffer.buffer.at(a);

            return (yb - ya) * (1 / dx);
        }

        float Integrate(float a, float b, float dx)
        {
            auto _a = (unsigned int)(this->capacity * a);
            auto _b = (unsigned int)(this->capacity * b);
            unsigned int span = abs(_b - _a);

            if ((unsigned int)(abs(b - a) + 0.5f) == 0 || span > this->capacity)
            {
                return 0.f;
            }

            auto tempA = _a + this->buffer.tail;
            auto tempB = _b + this->buffer.head;
            auto x1 = tempA < this->capacity ? tempA : tempA - this->capacity;
            auto x2 = tempB < this->capacity ? tempB : tempB - this->capacity;
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
    };
}
