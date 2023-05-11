#pragma once
#include "RingBuffer.hpp"

namespace CleaningDevice
{
    template <std::size_t N>
    class PowerConsumption
    {
    private:
        using const_iterator = typename std::array<float, N>::const_iterator;
        RingBuffer<float, N> data;
        float totalWatts;

    public:
        PowerConsumption() : totalWatts(0) {}
        ~PowerConsumption() {}

        void AddWattsMeasurement(float v)
        {
            this->data.Push(v);
            // TODO: Multiply `v` with `dt` to correct for the time delta
            this->totalWatts += v;
        }

        void Clear() { this->data.Clear(); }
        std::size_t GetCapacity() { return this->data.GetCapacity(); }
        float GetCurrentWatts() { return this->data.PeekHead(); }
        float GetTotalWatts() { return this->totalWatts; }

        // Implement iterator
        const_iterator begin() const { return this->data.begin(); }
        const_iterator cbegin() const { return this->data.cbegin(); }
        const_iterator end() const { return this->data.end(); }
        const_iterator cend() const { return this->data.cend(); }
    };
}
