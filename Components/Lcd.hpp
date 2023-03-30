#pragma once
#include "BaseComponent.hpp"

namespace PREN::Components
{
    class Lcd : public BaseComponent
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    private:
        Status status;

    public:
        Lcd(Controller *c);
        virtual ~Lcd();

        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
