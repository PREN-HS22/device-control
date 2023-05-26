#include "MqttClient.hpp"

namespace CleaningDevice
{
    MqttClient::MqttClient(WiFiClient &client, std::string server, std::uint16_t port, std::string user, std::string pass)
        : client(client),
          server(server),
          port(port),
          user(user),
          pass(pass),
          pubsubClient()
    {
        // mqttServer connection
        pubsubClient.setServer(this->server.c_str(), this->port);
        pubsubClient.setCallback(MqttClient::OnIncoming);
        pubsubClient.setBufferSize(512);
    }

    void MqttClient::OnIncoming(char *topic, std::uint8_t *payload, std::size_t length)
    {
        /*
        Serial.print("Message arrived [");
        Serial.print(topic);
        Serial.print("] ");

        String receivedTopic = String(topic);
        String messageTemp;

        for (int i = 0; i < length; i++)
        {
            messageTemp += (char)payload[i];
        }

        std::uint8_t position = receivedTopic.indexOf("callback/") + 9;
        String receivedTopicCut = receivedTopic.substring(position);

        Serial.println(receivedTopicCut);

        if (receivedTopicCut == "reset_mcu")
        {
            // reset mcu if payload is 1
            if (messageTemp == "1")
            {
                Serial.println("resetting mcu");
                delay(200);
                // reset_mcu();
            }
        }

        if (receivedTopicCut == "set_fan_speed")
        {
            fanSpeed = messageTemp.toInt();
            Serial.print("set fan speed to: ");
            Serial.println(fanSpeed);
            setServos(fan, fanSpeed);
        }

        if (receivedTopicCut == "set_stepA_enable")
        {
            stepAEnable = messageTemp.toInt();
            Serial.print("Enable Stepper A: ");
            Serial.println(stepAEnable);
        }

        if (receivedTopicCut == "set_stepA_speed")
        {
            stepASpeed = messageTemp.toInt();
            Serial.print("set Speed Stepper A: ");
            Serial.println(stepASpeed);
            stepperA.setMaxSpeed(stepASpeed);
        }

        if (receivedTopicCut == "set_stepA_accel")
        {
            stepAAccel = messageTemp.toInt();
            Serial.print("set Accelation Stepper A: ");
            Serial.println(stepAAccel);
            stepperA.setAcceleration(stepAAccel);
        }

        if (receivedTopicCut == "set_stepA_moveto")
        {
            stepAMoveTo = messageTemp.toInt();
            Serial.print("Move To Stepper A: ");
            Serial.println(stepAMoveTo);
            stepperA.moveTo(stepAMoveTo);
        }

        if (receivedTopicCut == "set_stepB_enable")
        {
            stepBEnable = messageTemp.toInt();
            Serial.print("Enable Stepper B: ");
            Serial.println(stepBEnable);
        }

        if (receivedTopicCut == "set_stepB_speed")
        {
            stepBSpeed = messageTemp.toInt();
            Serial.print("set Speed Stepper B: ");
            Serial.println(stepBSpeed);
            stepperA.setMaxSpeed(stepBSpeed);
        }

        if (receivedTopicCut == "set_stepB_accel")
        {
            stepBAccel = messageTemp.toInt();
            Serial.print("set Accelation Stepper B: ");
            Serial.println(stepBAccel);
            stepperA.setAcceleration(stepBAccel);
        }

        if (receivedTopicCut == "set_stepB_moveto")
        {
            stepBMoveTo = messageTemp.toInt();
            Serial.print("Move To Stepper B: ");
            Serial.println(stepBMoveTo);
            stepperA.moveTo(stepBMoveTo);
        }

        if (receivedTopicCut == "set_dcMotA_enable")
        {
            dcMotAEnable = messageTemp.toInt();
            Serial.print("Enable DC-Motor A: ");
            Serial.println(dcMotAEnable);
        }

        if (receivedTopicCut == "set_dcMotA_speed")
        {
            dcMotASpeed = messageTemp.toInt();
            Serial.print("Set Speed DC-Motor A: ");
            Serial.println(dcMotASpeed);
            motors.setSpeedA(dcMotASpeed);
        }

        if (receivedTopicCut == "set_dcMotA_dir")
        {
            directionA = messageTemp.toInt();
            Serial.print("Set Direction DC-Motor A: ");
            Serial.println(directionA);

            if (directionA > 10)
            {
                dcMotADir = L298N::BACKWARD;
                Serial.println("DC-Motor A: Backward ");
            }
            else
            {
                dcMotADir = L298N::FORWARD;
                Serial.println("DC-Motor A: Forward ");
            }
        }

        if (receivedTopicCut == "set_dcMotA_delay")
        {
            dcMotADelay = messageTemp.toInt();
            Serial.print("Set Delay DC-Motor A: ");
            Serial.println(dcMotADelay);
        }

        if (receivedTopicCut == "set_dcMotB_enable")
        {
            dcMotBEnable = messageTemp.toInt();
            Serial.print("Enable DC-Motor B: ");
            Serial.println(dcMotBEnable);
        }

        if (receivedTopicCut == "set_dcMotB_speed")
        {
            dcMotBSpeed = messageTemp.toInt();
            Serial.print("Set Speed DC-Motor B: ");
            Serial.println(dcMotBSpeed);
            motors.setSpeedB(dcMotBSpeed);
        }

        if (receivedTopicCut == "set_dcMotB_dir")
        {
            directionB = messageTemp.toInt();
            Serial.print("Set Direction DC-Motor B: ");
            Serial.println(directionB);

            if (directionB > 10)
            {
                dcMotBDir = L298N::BACKWARD;
                Serial.println("DC-Motor B: Backward ");
            }
            else
            {
                dcMotBDir = L298N::FORWARD;
                Serial.println("DC-Motor B: Forward ");
            }
        }

        if (receivedTopicCut == "set_dcMotB_delay")
        {
            dcMotBDelay = messageTemp.toInt();
            Serial.print("Set Delay DC-Motor B: ");
            Serial.println(dcMotBDelay);
        }
        */
    }

    void MqttClient::Run(void *pvParams)
    {
        // Check connection state
        // Reconnect if necessary
        // Call PubSubClient::loop
        // Publish device information periodically
        auto mqttClient = *(static_cast<MqttClient*>(pvParams));
        auto pubsubClient = mqttClient.pubsubClient;
        std::uint64_t lastMsg = 0;
        for (;;)
        {
            // put your main code here, to run repeatedly:
            if (!pubsubClient.connected())
            {
                mqttClient.Connect();
            }

            pubsubClient.loop();

            long now = millis();
            if (now - lastMsg > 5000)
            {
                lastMsg = now;
            }
        }
    }

    void MqttClient::Connect()
    {
        auto macAddress = WiFi.macAddress().c_str();

        while (!this->pubsubClient.connected())
        {
            Serial.println("Reconnecting MQTT...");

            char willTopic[50];
            sprintf(willTopic, "esp32dev/%s/status", macAddress);
            this->pubsubClient.subscribe(willTopic);
            if (this->pubsubClient.connect(macAddress, this->user.c_str(), this->pass.c_str(), willTopic, 0, false, "OFFLINE"))
            {
                Serial.println("connected");
                // Once connected, publish an announcement...
                this->pubsubClient.publish(willTopic, "ONLINE");

                // all subsciptions listed bellow
                char callbackTopic[50];
                sprintf(callbackTopic, "esp32dev/%s/callback/#", macAddress);
                this->pubsubClient.subscribe(callbackTopic);

                Serial.print("Subscribed to: ");
                Serial.println(callbackTopic);
            }
            else
            {
                Serial.print("failed, rc=");
                Serial.print(this->pubsubClient.state());
                Serial.println(" retrying in 5 seconds");
                delay(5000);
            }
        }

        Serial.println("MQTT Connected...");
    }

    void MqttClient::Publish(JSONVar &json, std::string topic)
    {
        this->pubsubClient.publish(topic.c_str(), JSON.stringify(json).c_str());
    }

    void somePublishingTest(PubSubClient &client)
    {
        auto macAddress = WiFi.macAddress().c_str();
        // MISC STATE
        JSONVar miscPayload;
        miscPayload["misc_stats"]["mcu_mac"] = macAddress;
        miscPayload["misc_stats"]["ip_address"] = WiFi.localIP().toString().c_str();
        miscPayload["misc_stats"]["rssi"] = WiFi.RSSI();

        char mtopic[50];
        sprintf(mtopic, "esp32dev/%s/misc_stats", macAddress);
        client.publish(mtopic, JSON.stringify(miscPayload).c_str());

        // SERVO STATE
        JSONVar servoPayload;
        servoPayload["servo_stats"]["degrees"] = 1337.f;
        sprintf(mtopic, "esp32dev/%s/servo_stats", macAddress);
        client.publish(mtopic, servoPayload);
    }
}
