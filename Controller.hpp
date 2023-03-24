#pragma once

#include <ArduinoSTL.h>
#include <array>
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "Arm.hpp"
#include "Container.hpp"
#include "Conveyor.hpp"
#include "ElectroMagnet.hpp"
#include "ElectroMotor.hpp"
#include "LoadCell.hpp"
#include "Vacuum.hpp"

namespace PREN
{
    class Controller : public Emergency, public Reportable
    {
    private:
        Report status;
        Components::ElectroMagnet em;
        std::array<Components::Container, 4> containers;
        Components::Arm arm;
        Components::Vacuum vacuum;
        Components::Conveyor conveyor;

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
        float TotalPowerConsumption();
        void RaiseEmergency();
        Report &GetReport();
    };
}
