#pragma once
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

namespace CleaningDevice
{
    class MqttClient
    {
    private:
        PubSubClient pubsubClient;
        const std::string id;
        const std::string server;
        const std::uint16_t port;
        const std::string user;
        const std::string pass;

    public:
        MqttClient(WiFiClient &client, std::string server, std::uint16_t port, std::string user, std::string pass, std::string id);
        ~MqttClient();

        static void OnIncoming(char *topic, std::uint8_t *payload, std::size_t length);
        void Connect();
        void Publish(std::string topic, std::string message);
    };
}
