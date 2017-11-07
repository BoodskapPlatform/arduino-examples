/**
MIT License

Copyright (c) 2017 Boodskap Inc

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
 */ 
#ifdef USE_MQTT

#include "BoodskapMqttTransceiver.h"

WiFiClient espClient;
PubSubClient mqtt(espClient);

char MQTT_CLIENT_ID[MQTT_CLIENT_ID_LEN];
char MQTT_USER_ID[MQTT_USER_ID_LEN];
char MQTT_PASSWD[MQTT_PASSWD_LEN];
char MQTT_IN_TOPIC[MQTT_IN_TOPIC_LEN];
char MQTT_OUT_TOPIC[MQTT_OUT_TOPIC_LEN];

void sendMessage(int messageId, JsonObject &data)
{

  if (!mqtt.connected())
  {
    initController();
  }

  sprintf(MQTT_OUT_TOPIC, "/%s/device/%s/msgs/%d/%s/%s", domainKey.c_str(), deviceId.c_str(), messageId, deviceModel.c_str(), firmwareVersion.c_str());

  String jsonStr;
  data.printTo(jsonStr);

  if (messageId >= 0)
  { //Print only user defined messages
    DEBUG_PORT.print("Sending: ");
    DEBUG_PORT.println(MQTT_OUT_TOPIC);
    DEBUG_PORT.println(jsonStr);
  }

  if (!mqtt.connected())
  {
    return;
  }

  mqtt.publish(MQTT_OUT_TOPIC, jsonStr.c_str());

  lastMessage = millis();
}

void sendAck(JsonObject& header, uint32_t corrId, int ack)
{

  StaticJsonBuffer<MESSAGE_BUFF_SIZE/4> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();

  data["corrid"] = corrId;
  data["acked"] = ack;

  sendMessage(MSG_ACK, data);
  
}

void messageCallback(char *topic, byte *payload, unsigned int length)
{
  DEBUG_PORT.printf("MQTT Received %d bytes from %s\n", length, topic);
  payload[length] = '\0'; // Null terminate
  parseIncoming(payload);
}

void initController()
{

  if (mqtt.connected())
    return;

  sprintf(MQTT_CLIENT_ID, "DEV_%s", deviceId.c_str());
  sprintf(MQTT_USER_ID, "DEV_%s", domainKey.c_str());
  sprintf(MQTT_PASSWD, "%s", apiKey.c_str());

  sprintf(MQTT_IN_TOPIC, "/%s/device/%s/cmds", domainKey.c_str(), deviceId.c_str());

  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(messageCallback);

  DEBUG_PORT.printf("Connecting to MQTT server as ID: %s, User: %s, Pswd: %s\n", MQTT_CLIENT_ID, MQTT_USER_ID, MQTT_PASSWD);

  if (mqtt.connect(MQTT_CLIENT_ID, MQTT_USER_ID, MQTT_PASSWD))
  {

    DEBUG_PORT.println("Connected to MQTT server !!!");

    if (!mqtt.subscribe(MQTT_IN_TOPIC))
    {
      DEBUG_PORT.printf("Unable to subscribe MQTT Topic: %s\n", MQTT_IN_TOPIC);
    }
    else
    {
      DEBUG_PORT.printf("Subscribed topic: %s\n", MQTT_IN_TOPIC);
    }
  }
  else
  {
    DEBUG_PORT.println("!!! MQTT not connected !!!");
  }
}

void checkIncoming()
{

  if (!mqtt.connected())
  {
    initController();
  }

  mqtt.loop();

  if ((millis() - lastMessage) >= (mqttHeartbeat*1000))
  {
    sendHeartbeat();
  }
}

#endif //USE_MQTT