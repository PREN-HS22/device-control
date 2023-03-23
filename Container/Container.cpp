#include "Container.hpp"

namespace PREN::Components
{
    Container::Container(ContainerType t) : type(t)
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
        return this->status;
    }
}
