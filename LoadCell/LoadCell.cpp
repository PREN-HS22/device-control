#include "LoadCell.hpp"

namespace PREN::Component
{
    template <unsigned int P1, unsigned int P2>
    LoadCell<P1, P2>::LoadCell() : device(P1, P2)
    {
    }

    LoadCell<P1, P2>::~LoadCell()
    {
    }

    float LoadCell<P1, P2>::GetValue()
    {
    }

    void LoadCell<P1, P2>::Tare()
    {
    }

    void LoadCell<P1, P2>::RaiseEmergency()
    {
    }

    void LoadCell<P1, P2>::RaiseEmergency()
    {
    }

    Report &LoadCell<P1, P2>::GetStatusReport()
    {
        return this->status;
    }
}
