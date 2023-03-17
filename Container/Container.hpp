#pragma once
#include "Emergency.hpp"
#include "Reportable.hpp"

namespace PREN::Component
{
    enum ContainerType
    {
        A,
        B,
        C,
        D,
        E
    };

    class Container : public Emergency, public Reportable
    {
    private:
        ContainerType type;
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
