#pragma once
#include <ArduinoSTL.h>
#include "RingBuffer.hpp"

namespace PREN
{
    template <std::size_t N>
    class PowerConsumption
    {
    private:
        RingBuffer<float, N> data;
        float totalConsumption;

    public:
        PowerConsumption();
        ~PowerConsumption();

        void AddMeasurement(float v);
        void Clear();
        std::size_t GetCapacity();
        float GetCurrentConsumption();
        float GetTotalConsumption();

        // Implement iterator
        typename std::array<float, N>::const_iterator begin() const;
        typename std::array<float, N>::const_iterator cbegin() const;
        typename std::array<float, N>::const_iterator end() const;
        typename std::array<float, N>::const_iterator cend() const;
    };
}