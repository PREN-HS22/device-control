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
        TwoWire wire;
        Adafruit_INA219 ina;
        float sampleRate, totalPower;

    private:
        static void TimerCallback(TimerHandle_t timer)
        {
            auto self = static_cast<PowerConsumption *>(pvTimerGetTimerID(timer));
            auto ina = self->ina;
            auto sample = self->sample;
            auto delta = 1.f / self->sampleRate;

            auto shuntVoltage = ina.getShuntVoltage_mV() / 1000.f;
            auto busVoltage = ina.getBusVoltage_V();
            auto current = ina.getCurrent_mA() / 1000.f;
            auto power = ina.getPower_mW() / 1000.f;
            auto loadVoltage = busVoltage + shuntVoltage;
            auto totalPower = self->totalPower + power * delta;

            taskENTER_CRITICAL(&self->spinLock);
            sample.ShuntVoltage = shuntVoltage;
            sample.BusVoltage = busVoltage;
            sample.Current = current;
            sample.Power = power;
            sample.LoadVoltage = loadVoltage;
            self->totalPower = totalPower;
            taskEXIT_CRITICAL(&self->spinLock);
        }

    public:
        PowerConsumption(float rate, int sda, int scl, std::uint8_t address)
            : sampleRate(rate < 1.f ? 1.f : rate),
              totalPower(0),
              wire(0),
              ina(address)
        {
            this->wire.setPins(sda, scl);
            this->timer = xTimerCreate("PowerConsumption::TimerCallback", pdMS_TO_TICKS((TickType_t)(1000.f / rate)), pdFALSE, this, PowerConsumption::TimerCallback);

            for (int i = 0; i < 10; i++)
            {
                if (ina.begin(&(this->wire)))
                {
                    break;
                }
                delay(50);
            }

            xTimerReset(this->timer, pdMS_TO_TICKS(5));
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
