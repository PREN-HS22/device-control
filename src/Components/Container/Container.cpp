#include "Container.hpp"

namespace CleaningDevice::Components
{
    Container::Container(Controller &c, ContainerType t)
        : AbstractComponent(c),
          type(t),
          lc(c, 2U, 3U),
          amount(0U),
          confidence(0.f)
    {
    }

    Container::~Container()
    {
    }

    ContainerType Container::GetType()
    {
        return this->type;
    }

    std::uint32_t Container::GetContentAmount()
    {
        return this->amount;
    }

    float Container::GetConfidence()
    {
        return this->confidence;
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

    void Container::OnObjectDetected(std::uint32_t amount, float confidence)
    {
        auto cWeight = this->amount;        // Current confidence weight
        auto nWeight = amount;              // New confidence weight
        auto tWeight = cWeight + nWeight;   // Total confidence weight

        // Weighted confidence calculation
        this->confidence = (cWeight * this->confidence + nWeight * confidence) / tWeight;
        this->amount += amount;
    }
}
