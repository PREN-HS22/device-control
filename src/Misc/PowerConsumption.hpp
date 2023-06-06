#pragma once

namespace CleaningDevice
{
    class PowerConsumption
    {
    private:
        float current;
        float total;
        float deltaTime;

    public:
        PowerConsumption() : total(0) {}
        ~PowerConsumption() {}

        float GetDeltaTime() { return this->deltaTime; }
        void SetDeltaTime(float dt) { this->deltaTime = dt; }

        float GetCurrent() { return this->current; }
        void SetCurrent(float v)
        {
            this->current = v;
            this->total += v * this->deltaTime;
        }

        float GetTotal() { return this->total; }
    };
}
