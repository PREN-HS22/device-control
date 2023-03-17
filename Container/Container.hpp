#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "LoadCell.hpp"

namespace PREN::Component
{
    enum ContainerType
    {
        PlasticCap,
        CigaretteStup,
        CrownCap,
        Valuables
    };

    class Container : public Emergency, public Reportable
    {
    private:
        ContainerType type;
        Report status;
        LoadCell<2, 3> lc;

    public:
        Container(ContainerType t);
        virtual ~Container();

        ContainerType GetType();
        unsigned int GetContentAmount();
        float GetConfidence();
        void RaiseEmergency();
        Report &GetStatusReport();
    };
}
