#pragma once
#include "Derivable.hpp"
#include "Integratable.hpp"

namespace PREN
{
    class SlidingRange : public Derivable<float, float>, public Integratable<float, float>
    {
    public:
        SlidingRange(unsigned int length, float stepSize);
        ~SlidingRange();

        void AddValue(float value);
        float Derive(float x);
        float Integrate(float a, float b);
    };
}
