#pragma once

#include <ArduinoSTL.h>
#include <array>
#include "Emergency.hpp"
#include "Reportable.hpp"
#include "StateMachine/FiniteStateMachine.hpp"
#include "Components/Arm.hpp"
#include "Components/Container.hpp"
#include "Components/Conveyor.hpp"
#include "Components/ElectroMagnet.hpp"
#include "Components/ElectroMotor.hpp"
#include "Components/Lcd.hpp"
#include "Components/LoadCell.hpp"
#include "Components/Vacuum.hpp"

using CleaningDevice::StateMachine::State, CleaningDevice::StateMachine::FiniteStateMachine;

namespace CleaningDevice
{
    class Controller
        : public FiniteStateMachine<Controller>,
          public Emergency,
          public Reportable
    {
    private:
        Report report;
        Components::ElectroMagnet em;
        Components::Arm arm;
        Components::Vacuum vacuum;
        Components::Conveyor conveyor;
        Components::Container cont_a, cont_b, cont_c, cont_d;

    public:
        Controller(State<Controller> &start);
        ~Controller();

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
