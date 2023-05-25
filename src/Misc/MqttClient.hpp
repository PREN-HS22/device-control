#pragma once
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>
#include <Arduino_JSON.h>

namespace CleaningDevice
{
    class MqttClient
    {
    private:
        WiFiClient &client;
        PubSubClient pubsubClient;

        // Add your MQTT Broker IP address
        const std::string server;
        const std::uint16_t port;
        const std::string user;
        const std::string pass;

    public:
        MqttClient(WiFiClient &client, std::string server, std::uint16_t port, std::string user, std::string pass);

        static void OnIncoming(char *topic, byte *payload, std::size_t length);
        static void Run(void *pvParams);
        void Connect();
        void Publish(JSONVar &json, std::string topic);
    };
}
