#ifdef USE_MQTT

#include <WiFiUdp.h>
#include <BoodskapTransceiver.h>
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

  sprintf(MQTT_OUT_TOPIC, "/%s/device/%s/msgs/%d/%s/%s", DOMAIN_KEY, deviceId.c_str(), messageId, DEVICE_MODEL, FIRMWARE_VERSION);

  String jsonStr;
  data.printTo(jsonStr);

  if (messageId >= 100)
  { //Print only user defined messages
    DEBUG_PORT.println(MQTT_OUT_TOPIC);
    DEBUG_PORT.println(jsonStr);
  }

  if (!mqtt.connected())
  {
    return;
  }

  mqtt.publish(MQTT_OUT_TOPIC, jsonStr.c_str());
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
  sprintf(MQTT_USER_ID, "DEV_%s", DOMAIN_KEY);
  sprintf(MQTT_PASSWD, "%s", API_KEY);

  sprintf(MQTT_IN_TOPIC, "/%s/device/%s/cmds", DOMAIN_KEY, deviceId.c_str());

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
}

#endif //USE_MQTT