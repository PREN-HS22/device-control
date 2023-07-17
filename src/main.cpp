#include <Arduino.h>
#include "Controller.hpp"

using namespace CleaningDevice;
Controller *c;
WiFiClient wc;
MqttClient *mc;

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("Ready!");
    delay(2000);
    Serial.println(((std::string) "esp32/" + WiFi.macAddress().c_str()).c_str());
    mc = new MqttClient(wc, "broker.hivemq.com", 1883U, "", "", (std::string) "esp32/" + WiFi.macAddress().c_str());
    c = new Controller(wc, *mc);
}

void loop()
{
}
