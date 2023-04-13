#pragma once
#include "BaseComponent.hpp"

namespace CleaningDevice::Components
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
        ~Lcd();

        Status GetStatus();
        void RaiseEmergency();
        Report &GetReport();
    };
}
