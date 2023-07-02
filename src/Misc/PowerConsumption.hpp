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
        TimerHandle_t timer;
        portMUX_TYPE spinLock = portMUX_INITIALIZER_UNLOCKED;
        TwoWire i2c;
        Adafruit_INA219 ina;
        float sampleRate, totalPower;

    private:
        static void TimerCallback(TimerHandle_t timer)
        {
            auto self = static_cast<PowerConsumption *>(pvTimerGetTimerID(timer));
            auto ina = self->ina;
            auto sample = self->sample;
            auto delta = 1.f / self->sampleRate;

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
        }

    public:
        PowerConsumption(float rate, std::uint8_t address)
            : sampleRate(rate < 1.f ? 1.f : rate),
              totalPower(0),
              i2c(0),
              ina(address)
        {
            this->i2c.setPins(13, 4);
            this->timer = xTimerCreate("PowerConsumption::TimerCallback", pdMS_TO_TICKS((TickType_t)(1000.f / rate)), pdFALSE, this, PowerConsumption::TimerCallback);

            for (int i = 0; i < 10; i++)
            {
                if (ina.begin())
                {
                    break;
                }
                delay(50);
            }
        }

        ~PowerConsumption() { xTimerDelete(this->timer, pdMS_TO_TICKS(5)); }

        float GetSampleRate() { return this->sampleRate; }
        void SetSampleRate(float rate) { this->sampleRate = rate; }

        MeasurementSample &GetLatestSample() { return this->sample; }
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
