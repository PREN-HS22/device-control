#include "Container.hpp"

namespace PREN::Component
{
    Container::Container(ContainerType t)
    {
    }

    Container::~Container()
    {
    }

    ContainerType Container::GetType()
    {
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
