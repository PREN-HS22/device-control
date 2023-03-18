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
        std::size_t capacity;

    public:
        SlidingRange();
        ~SlidingRange();

        void AddValue(float value);
        float Derive(float x, float dx);
        float Integrate(float a, float b, float dx);
    };
}
