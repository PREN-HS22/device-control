#include "../../tests.hpp"
#include "../../assertions.hpp"
#include "../src/Controller.hpp"
#include "../src/Components/DcMotor/DcMotor.hpp"

using CleaningDevice::Controller;
using namespace CleaningDevice::Components;
Controller ctrl;

namespace DcMotorTest
{
    auto motor = new DcMotor(ctrl, DcMotorCfg(32, 25, 33));

    void RotateIndefinitely()
    {
        // Rotate forward for 1s
        motor->Rotate(L298N::FORWARD, 1.f);
        delay(1000);
        motor->Stop();

        // Rotate backward for 2s
        motor->Rotate(L298N::BACKWARD, 1.f);
        delay(1000);
        motor->Stop();
    }

    void RotateWithLimit()
    {
        // Rotate forward for x ms
        motor->Rotate(L298N::FORWARD, 1.f, 2000);

        // Rotate backward for x ms
        motor->Rotate(L298N::BACKWARD, 1.f, 2000);
    }

    void RotateSeveralSpeeds()
    {
        // Rotate forward with changing speed
        motor->Rotate(L298N::FORWARD, .2f);
        delay(1000);
        motor->Rotate(L298N::FORWARD, .4f);
        delay(1000);
        motor->Rotate(L298N::FORWARD, .6f);
        delay(1000);
        motor->Rotate(L298N::FORWARD, .8f);
        delay(1000);
        motor->Rotate(L298N::FORWARD, 1.f);
        delay(1000);
        motor->Stop();

        // Rotate backward with changing speed
        motor->Rotate(L298N::BACKWARD, .2f);
        delay(1000);
        motor->Rotate(L298N::BACKWARD, .4f);
        delay(1000);
        motor->Rotate(L298N::BACKWARD, .6f);
        delay(1000);
        motor->Rotate(L298N::BACKWARD, .8f);
        delay(1000);
        motor->Rotate(L298N::BACKWARD, 1.f);
        delay(1000);
        motor->Stop();
    }

    void Run()
    {
        TEST(RotateIndefinitely);
        TEST(RotateWithLimit);
        TEST(RotateSeveralSpeeds);
    }
}
