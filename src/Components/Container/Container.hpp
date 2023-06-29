#pragma once
#include "../AbstractComponent.hpp"
#include "../LoadCell/LoadCell.hpp"

namespace CleaningDevice::Components
{
    enum ContainerType
    {
        PlasticCap,
        CigaretteStump,
        CrownCap,
        Valuables
    };

    class Container : public AbstractComponent
    {
    private:
        ContainerType type;
        LoadCell<> lc;
        std::uint32_t amount;
        float confidence;

    private:
        void OnObjectDetected(std::uint32_t amount, float confidence);

    public:
        Container(Controller &c, ContainerType t);
        ~Container();

        ContainerType GetType();
        std::uint32_t GetContentAmount();
        float GetConfidence();
        void RaiseEmergency();
        Report &GetReport();
    };
}
