#include "LoadCell.hpp"

namespace PREN::Components
{
    template <std::size_t D, std::size_t S>
    LoadCell<D, S>::LoadCell(Controller *c, unsigned int dout, unsigned int sck) : BaseComponent(c), status(Idle), device(dout, sck)
    {
        this->device.setSamplesInUse(10);
        this->device.begin();
        this->device.setTareOffset(0);
        this->device.start(2000, true);

        if (this->device.getTareTimeoutFlag())
        {
            throw;
        }
        else
        {
            this->device.setCalFactor(696.f);
        }
    }

    template <std::size_t D, std::size_t S>
    LoadCell<D, S>::~LoadCell()
    {
        this->device.powerDown();
    }

    template <std::size_t D, std::size_t S>
    float LoadCell<D, S>::GetValue()
    {
        if (this->device.update() != 0)
        {
            return this->device.getData();
        }
    }

    template <std::size_t D, std::size_t S>
    void LoadCell<D, S>::Tare()
    {
    }

    template <std::size_t D, std::size_t S>
    LoadCell<D, S>::Status LoadCell<D, S>::GetStatus()
    {
        return this->status;
    }

    template <std::size_t D, std::size_t S>
    void LoadCell<D, S>::RaiseEmergency()
    {
        // Stop device
    }

    template <std::size_t D, std::size_t S>
    Report &LoadCell<D, S>::GetReport()
    {
        this->report["Status"] = this->GetStatus();

        return this->report;
    }
}
