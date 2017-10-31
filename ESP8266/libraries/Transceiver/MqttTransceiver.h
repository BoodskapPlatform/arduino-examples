#ifndef _MQTT_CONTROLLER_H_
#define _MQTT_CONTROLLER_H_

#include "Transceiver.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_HOST "mqtt.boodskap.io"
#define MQTT_PORT 1883

WiFiClient espClient;
PubSubClient mqtt(espClient);

char MQTT_CLIENT_ID[25];
char MQTT_USER_ID[40];
char MQTT_PASSWD[25];
char MQTT_IN_TOPIC[80];
char MQTT_OUT_TOPIC[128];

void sendMessage(int messageId, JsonObject& data) {

  if (!mqtt.connected()) {
    initController();
  }

  sprintf(MQTT_OUT_TOPIC, "/%s/device/%s/msgs/%d/%s/%s", DOMAIN_KEY, deviceId.c_str(), messageId, DEVICE_MODEL, FIRMWARE_VERSION);

  String jsonStr;
  data.printTo(jsonStr);

  DEBUG_PORT.println(MQTT_OUT_TOPIC);
  DEBUG_PORT.println(jsonStr);

  if (!mqtt.connected()) {
    return;
  }

  mqtt.publish(MQTT_OUT_TOPIC, jsonStr.c_str());
}

void messageCallback(char* topic, byte* payload, unsigned int length) {
  DEBUG_PORT.printf("MQTT Received %d bytes from %s\n", length, topic);
  payload[length] = '\0'; // Null terminate
  parseIncoming(payload);
}


void initController() {

  if (mqtt.connected()) return;

  sprintf(MQTT_CLIENT_ID, "DEV_%s", deviceId.c_str());
  sprintf(MQTT_USER_ID, "DEV_%s", DOMAIN_KEY);
  sprintf(MQTT_PASSWD, "%s", API_KEY);

  sprintf(MQTT_IN_TOPIC, "/%s/device/%s/cmds", DOMAIN_KEY, deviceId.c_str());

  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(messageCallback);

  DEBUG_PORT.printf("Connecting to MQTT server as ID: %s, User: %s, Pswd: %s\n", MQTT_CLIENT_ID, MQTT_USER_ID, MQTT_PASSWD);

  if (mqtt.connect(MQTT_CLIENT_ID, MQTT_USER_ID, MQTT_PASSWD)) {

    DEBUG_PORT.println("Connected to MQTT server !!!");

    if (!mqtt.subscribe(MQTT_IN_TOPIC)) {
      DEBUG_PORT.printf("Unable to subscribe MQTT Topic: %s\n", MQTT_IN_TOPIC);
    }else{
      DEBUG_PORT.printf("Subscribed topic: %s\n", MQTT_IN_TOPIC);
    }
  } else {
    DEBUG_PORT.println("!!! MQTT not connected !!!");
  }
}

void checkIncoming() {

  if (!mqtt.connected()) {
    initController();
  }

  mqtt.loop();
}

#endif //_MQTT_CONTROLLER_H_
