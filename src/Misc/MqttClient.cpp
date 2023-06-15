#include "MqttClient.hpp"

namespace CleaningDevice
{
    MqttClient::MqttClient(WiFiClient &client, std::string server, std::uint16_t port, std::string user, std::string pass, std::string id)
        : server(server),
          port(port),
          user(user),
          pass(pass),
          pubsubClient(client),
          id(id)
    {
        this->pubsubClient.setServer(this->server.c_str(), this->port);
        this->pubsubClient.setCallback(MqttClient::OnIncoming);
    }

    MqttClient::~MqttClient()
    {
        this->pubsubClient.publish((this->id + "/status").c_str(), "[Status] Shutting down");
        this->pubsubClient.disconnect();
        WiFi.disconnect();
    }

    void MqttClient::OnIncoming(char *topic, std::uint8_t *payload, std::size_t length)
    {
    }

    void MqttClient::Connect()
    {
        while (!this->pubsubClient.connected())
        {
            if (this->pubsubClient.connect(this->id.c_str()))
            {
                this->Publish("/status", "[Status] Connected");
            }
            else
            {
                // Display error on LCD
            }

            delay(5000);
        }
    }

    void MqttClient::Publish(std::string topic, std::string message)
    {
        this->pubsubClient.publish((this->id + topic).c_str(), message.c_str());
    }
}
