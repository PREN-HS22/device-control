#pragma once

#include <array>
#include <WiFi.h>
#include <freertos/task.h>
#include "Misc/Emergency.hpp"
#include "Misc/Reportable.hpp"
#include "Misc/MqttClient.hpp"
#include "Misc/PowerConsumption.hpp"
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
        PowerConsumption consumption;
        WiFiClient wifiClient;
        MqttClient mqttClient;
        Components::Arm arm;
        Components::Vacuum vacuum;
        Components::Conveyor conveyor;
        Components::Container cont_a, cont_b, cont_c, cont_d;
        Components::Lcd lcd;
        bool collecting;

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
        static void Run(void *pvParams);

    private:
        void ConnectToWiFiAP();
    };
}
