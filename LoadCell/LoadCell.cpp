#include "LoadCell.hpp"

namespace PREN::Component
{
    template <std::size_t D, std::size_t S>
    LoadCell<D, S>::LoadCell(unsigned int dout, unsigned int sck) : device(dout, sck)
    {
    }

    LoadCell<D, S>::~LoadCell()
    {
    }

    float LoadCell<D, S>::GetValue()
    {
    }

    void LoadCell<D, S>::Tare()
    {
    }

    void LoadCell<D, S>::RaiseEmergency()
    {
    }

    void LoadCell<D, S>::RaiseEmergency()
    {
    }

    Report &LoadCell<D, S>::GetStatusReport()
    {
        return this->status;
    }
}
