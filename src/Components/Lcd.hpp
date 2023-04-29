#pragma once
#include "BaseComponent.hpp"

namespace CleaningDevice::Components
{
    class Lcd : public BaseComponent<Lcd>
    {
    public:
        enum Status
        {
            Idle,
            Active
        };

    public:
        Lcd(Controller &c, State<Lcd> &start);
        ~Lcd();

        void RaiseEmergency();
        Report &GetReport();
    };
}
