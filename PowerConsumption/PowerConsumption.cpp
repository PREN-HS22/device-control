#include "PowerConsumption.hpp"

namespace PREN
{
    template <std::size_t N>
    PowerConsumption<N>::PowerConsumption() : totalWatts(0)
    {
    }

    template <std::size_t N>
    PowerConsumption<N>::~PowerConsumption()
    {
    }

    template <std::size_t N>
    void PowerConsumption<N>::AddWattsMeasurement(float v)
    {
        this->data.Push(v);
    }

    template <std::size_t N>
    void PowerConsumption<N>::Clear()
    {
        this->data.Clear();
    }

    template <std::size_t N>
    std::size_t PowerConsumption<N>::GetCapacity()
    {
        return this->data.GetCapacity();
    }

    template <std::size_t N>
    float PowerConsumption<N>::GetCurrentWatts()
    {
        return this->data.PeekHead();
    }

    template <std::size_t N>
    float PowerConsumption<N>::GetTotalWatts()
    {
        return this->totalWatts;
    }

    template <std::size_t N>
    typename std::array<float, N>::const_iterator PowerConsumption<N>::begin() const
    {
        return this->data.begin();
    }

    template <std::size_t N>
    typename std::array<float, N>::const_iterator PowerConsumption<N>::cbegin() const
    {
        return this->data.cbegin();
    }

    template <std::size_t N>
    typename std::array<float, N>::const_iterator PowerConsumption<N>::end() const
    {
        return this->data.end();
    }

    template <std::size_t N>
    typename std::array<float, N>::const_iterator PowerConsumption<N>::cend() const
    {
        return this->data.cend();
    }
}
