#pragma once
#include "../AbstractComponent.hpp"
#include "../DcMotor/DcMotor.hpp"

namespace CleaningDevice::Components
{
    class Conveyor : public AbstractComponent<Conveyor>
    {
    private:
        DcMotor motor;

    public:
        Conveyor(Controller &c, State<Conveyor> *start);
        ~Conveyor();

        void Start();
        void Stop();
        void SetSpeed(float fraction);
        float GetSpeed();
        void RaiseEmergency();
        Report &GetReport();
    };
}
