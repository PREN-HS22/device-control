#pragma once
#include <freertos/task.h>
#include <Adafruit_INA219.h>
#include "Reportable.hpp"

namespace CleaningDevice
{
    class MeasurementSample
    {
    public:
        float ShuntVoltage, BusVoltage, LoadVoltage, Current, Power;

        MeasurementSample() : ShuntVoltage(0), BusVoltage(0), LoadVoltage(0), Current(0), Power(0) {}
    };
    class PowerConsumption : public Reportable
    {
    private:
        Report report;
        MeasurementSample sample;
        TaskHandle_t task;
        portMUX_TYPE spinLock = portMUX_INITIALIZER_UNLOCKED;
        TwoWire i2c;
        Adafruit_INA219 ina;
        float sampleRate, totalPower;

    private:
        static void Run(void *pvParams)
        {
            auto self = static_cast<PowerConsumption *>(pvParams);
            TickType_t lastExecutedTick = xTaskGetTickCount();

            taskENTER_CRITICAL(&(self->spinLock));
            // ----
            auto i2c = self->i2c;
            auto ina = self->ina;
            auto sample = self->sample;
            auto delta = 1.f / self->sampleRate;

            int i = 0;
            while (!ina.begin(&i2c))
            {
                if (i++ > 9)
                {
                    vTaskDelete(nullptr);
                }

                vTaskDelay(pdMS_TO_TICKS(100));
            }
            // ----
            taskEXIT_CRITICAL(&(self->spinLock));

            for (;;)
            {
                taskENTER_CRITICAL(&(self->spinLock));
                // ----
                sample.ShuntVoltage = ina.getShuntVoltage_mV() / 1000.f;
                sample.BusVoltage = ina.getBusVoltage_V();
                sample.Current = ina.getCurrent_mA() / 1000.f;
                sample.Power = ina.getPower_mW() / 1000.f;
                sample.LoadVoltage = sample.BusVoltage + (sample.ShuntVoltage);
                self->totalPower += sample.Power * delta;
                // ----
                taskEXIT_CRITICAL(&(self->spinLock));

                xTaskDelayUntil(&lastExecutedTick, pdMS_TO_TICKS(1000.f * delta));
            }
        }

    public:
        PowerConsumption(float rate)
            : sampleRate(rate),
              totalPower(0),
              i2c(0)
        {
            this->i2c.setPins(13, 4);
            xTaskCreatePinnedToCore(PowerConsumption::Run, "PowerConsumption::Run", CONFIG_ARDUINO_LOOP_STACK_SIZE, this, tskIDLE_PRIORITY, &(this->task), 0);
        }

        ~PowerConsumption() { vTaskDelete(this->task); }

        float GetSampleRate() { return this->sampleRate; }
        void SetSampleRate(float rate) { this->sampleRate = rate; }

        MeasurementSample GetLatestSample() { return this->sample; }
        float GetTotalPower() { return this->totalPower; }

        Report &GetReport()
        {
            this->report["Voltages"]["Shunt"] = this->sample.ShuntVoltage;
            this->report["Voltages"]["Bus"] = this->sample.BusVoltage;
            this->report["Voltages"]["Load"] = this->sample.LoadVoltage;
            this->report["Current"] = this->sample.Current;
            this->report["Power"]["Momentary"] = this->sample.Power;
            this->report["Power"]["Total"] = this->totalPower;

            return this->report;
        }
    };
}
