#pragma once

#include <array>
#include <WiFi.h>
#include "Misc/Emergency.hpp"
#include "Misc/Reportable.hpp"
#include "Misc/MqttClient.hpp"
#include "Components/Arm/Arm.hpp"
#include "Components/BrushHead/BrushHead.hpp"
#include "Components/Container/Container.hpp"
#include "Components/Conveyor/Conveyor.hpp"
#include "Components/ElectroMagnet/ElectroMagnet.hpp"
#include "Components/DcMotor/DcMotor.hpp"
#include "Components/Lcd/Lcd.hpp"
#include "Components/LoadCell/LoadCell.hpp"
#include "Components/Vacuum/Vacuum.hpp"

namespace CleaningDevice
{
    class Controller
        : public Emergency,
          public Reportable
    {
    private:
        Report report;
        WiFiClient wifiClient;
        MqttClient mqttClient;
        Components::Arm arm;
        Components::Vacuum vacuum;
        Components::Conveyor conveyor;
        Components::Container cont_a, cont_b, cont_c, cont_d;

    public:
        Controller();
        ~Controller();

        void StartDevice();
        void StopDevice();
        void StartCollecting();
        void StopCollecting();
        bool IsReady();
        bool IsCollecting();
        float CurrentPowerConsumption();
        float TotalPowerConsumption();
        void RaiseEmergency();
        Report &GetReport();

    private:
        void ConnectToWiFiAP();
        void ConnectToMqttBroker();
    };
}
