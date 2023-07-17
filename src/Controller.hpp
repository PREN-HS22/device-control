#pragma once

#include <array>
#include <WiFi.h>
#include <freertos/task.h>
#include "Misc/Emergency.hpp"
#include "Misc/Reportable.hpp"
#include "Misc/MqttClient.hpp"
#include "Components/Arm/Arm.hpp"
#include "Components/BrushHead/BrushHead.hpp"
#include "Components/Conveyor/Conveyor.hpp"
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
        Components::BrushHead brush;

    public:
        Controller(WiFiClient &wc, MqttClient &mc);
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
