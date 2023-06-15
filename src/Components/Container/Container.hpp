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

    public:
        Container(Controller &c, ContainerType t);
        ~Container();

        ContainerType GetType();
        unsigned int GetContentAmount();
        float GetConfidence();
        void RaiseEmergency();
        Report &GetReport();
    };
}
