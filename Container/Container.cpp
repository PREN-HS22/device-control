#include "Container.hpp"

namespace PREN::Components
{
    Container::Container(Controller *c, ContainerType t) : BaseComponent(c), type(t)
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
    }

    Report &Container::GetStatusReport()
    {
        return this->report;
    }
}
