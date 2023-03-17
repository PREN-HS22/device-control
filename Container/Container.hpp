#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"

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

    private:
        Report status;

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
