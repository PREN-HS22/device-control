#pragma once
#include "BaseComponent.hpp"
#include "LoadCell.hpp"

namespace CleaningDevice::Components
{
    enum ContainerType
    {
        PlasticCap,
        CigaretteStump,
        CrownCap,
        Valuables
    };

    class Container : public BaseComponent<Container>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        ContainerType type;
        LoadCell<> lc;

    public:
        Container(Controller &c, State<Container> &start, ContainerType t);
        ~Container();

        ContainerType GetType();
        unsigned int GetContentAmount();
        float GetConfidence();
        void RaiseEmergency();
        Report &GetReport();
    };
}
