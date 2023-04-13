#pragma once
#include <ArduinoSTL.h>
#include "Derivable.hpp"
#include "Integratable.hpp"
#include "RingBuffer.hpp"

namespace CleaningDevice
{
    template <std::size_t N>
    class SlidingRange : public Derivable<float, float>, public Integratable<float, float>
    {
    private:
        RingBuffer<float, N + 1U> buffer;

    public:
        SlidingRange() {}
        ~SlidingRange() {}

        void AddValue(float value) { this->buffer.Push(value); }

        float Derive(float x = 1.f, float dx = 1.f/N)
        {
            // Clamp x between 0 and 1
            x = x < 0 ? 0 : x > 1.f ? 1.f : x;
            // Clamp dx: (1/N) <= dx <= N
            dx = dx < 1/N ? 1/N : dx > N ? N : dx;

            // Scale x by N
            x = x * N;
            auto offset = this->buffer.tail;
            unsigned int a, b;
            // Offset `a` & `b` and wrap around if necessary
            a = ((unsigned int)x + offset) % N;
            b = ((unsigned int)x + offset + 1) % N;

            float ya = this->buffer.buffer.at(a);
            float yb = this->buffer.buffer.at(b);

            return (yb - ya) * (1 / dx);
        }

        float Integrate(float a = 0.f, float b = 1.f, float dx = 1.f/N)
        {
            // Clamp a & b between 0 and 1
            a = a < 0 ? 0.f : a > 1.f ? 1.f : a;
            b = b < 0 ? 0.f : b > 1.f ? 1.f : b;

            // Scale a & b by N
            a = a * N;
            b = b * N;
            unsigned int _a = a;
            unsigned int _b = b;
            unsigned int span = abs(_b - _a);

            if ((unsigned int)(span + 0.5f) == 0 || span > N)
            {
                return 0.f;
            }

            _a = (_a + this->buffer.tail) % N;
            _b = (_b + this->buffer.head) % N;     
            // If b < a, integration is reversed -> \int_b^a = -\int_a^b       
            int h = b < a ? -1 : 1;

            // \int_a^b y dx = (0.5 * (y_a + y_b) + (\sum_{i=a+1}^b y_i)) * dx

            float sum = 0.f;
            unsigned int i = _a + 1;

            while (i != _b)
            {
                sum += this->buffer.buffer.at(i);
                i = (i + 1) % N;
            }

            sum += .5f * (this->buffer.buffer.at(_a) + this->buffer.buffer.at(_b));
            return h * sum * dx;
        }
    };
}
