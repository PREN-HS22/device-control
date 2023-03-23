#include "LoadCell.hpp"

namespace PREN::Components
{
    template <std::size_t D, std::size_t S>
    LoadCell<D, S>::LoadCell(unsigned int dout, unsigned int sck) : device(dout, sck)
    {
    }

    template <std::size_t D, std::size_t S>
    LoadCell<D, S>::~LoadCell()
    {
    }

    template <std::size_t D, std::size_t S>
    float LoadCell<D, S>::GetValue()
    {
    }

    template <std::size_t D, std::size_t S>
    void LoadCell<D, S>::Tare()
    {
    }

    void LoadCell<D, S>::RaiseEmergency()
    {
    }

    template <std::size_t D, std::size_t S>
    void LoadCell<D, S>::RaiseEmergency()
    {
    }

    template <std::size_t D, std::size_t S>
    Report &LoadCell<D, S>::GetStatusReport()
    {
        return this->status;
    }
}
