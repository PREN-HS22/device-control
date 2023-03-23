#include "Container.hpp"

namespace PREN::Components
{
    Container::Container(Controller *c, ContainerType t) : BaseComponent(c), status(Idle), type(t), lc(c, 2, 3)
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

    Container::Status Container::GetStatus()
    {
        return this->status;
    }

    void Container::RaiseEmergency()
    {
    }

    Report &Container::GetReport()
    {
        return this->report;
    }
}
