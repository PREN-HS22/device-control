#pragma once
#include "BaseComponent.hpp"
#include "LoadCell.hpp"

namespace PREN::Components
{
    enum ContainerType
    {
        PlasticCap,
        CigaretteStup,
        CrownCap,
        Valuables
    };

    class Container : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        ContainerType type;
        Status status;
        LoadCell<> lc;

    public:
        Container(Controller *c, ContainerType t);
        ~Container();

        ContainerType GetType();
        unsigned int GetContentAmount();
        float GetConfidence();
        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
