#include "Container.hpp"

namespace CleaningDevice::Components
{
    Container::Container(Controller &c, State<Container> *start, ContainerType t)
        : AbstractComponent<Container>(c, start),
          type(t),
          lc(c, nullptr, 2U, 3U)
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
        this->report["Status"] = this->GetState()->GetName();
        this->report["ContainerType"] = this->GetType();
        this->report["Amount"] = this->GetContentAmount();
        this->report["Confidence"] = this->GetConfidence();

        return this->report;
    }
}
