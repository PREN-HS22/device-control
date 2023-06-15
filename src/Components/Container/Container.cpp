#include "Container.hpp"

namespace CleaningDevice::Components
{
    Container::Container(Controller &c, ContainerType t)
        : AbstractComponent(c),
          type(t),
          lc(c, 2U, 3U)
    {
    }

    Container::~Container()
    {
    }

    ContainerType Container::GetType()
    {
        return this->type;
    }

    unsigned int Container::GetContentAmount()
    {
    }

    float Container::GetConfidence()
    {
    }

    void Container::RaiseEmergency()
    {
        // Stop device
    }

    Report &Container::GetReport()
    {
        this->report["ContainerType"] = this->GetType();
        this->report["Amount"] = this->GetContentAmount();
        this->report["Confidence"] = this->GetConfidence();
        this->report["Load cell"] = this->lc.GetReport();

        return this->report;
    }
}