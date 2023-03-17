#pragma once
#include "../Emergency.hpp"
#include "../Reportable.hpp"

namespace PREN::Component
{
    class Container : public Emergency, public Reportable
    {
        enum ContainerType
        {
            A,
            B,
            C,
            D,
            E
        };

    public:
        Container(ContainerType t);
        virtual ~Container();

        ContainerType GetType();
        unsigned int GetAmount();
        float GetConfidence();
        void RaiseEmergency();
        Report* GetStatusReport();
    };
}
