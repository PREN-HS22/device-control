#pragma once

#include <ArduinoSTL.h>
#include "Arm.hpp"
#include "Container.hpp"
#include "Conveyor.hpp"
#include "ElectroMagnet.hpp"
#include "ElectroMotor.hpp"
#include "LoadCell.hpp"
#include "Vacuum.hpp"

namespace PREN
{
    class Controller {
    private:
        Component::ElectroMagnet em;
        std::array<Component::Container, 4> containers;
        Component::Arm arm;
        Component::Vacuum vacuum;
        Component::Conveyor conveyor;
    public:
        Controller();
        virtual ~Controller();

        void Extend();
        void Retract();
        void StartCollecting();
        void StopCollecting();
        bool IsExtended();
        bool IsCollecting();
        float CurrentPowerConsumption();
        float TotalConsumedPower();
    };
}
