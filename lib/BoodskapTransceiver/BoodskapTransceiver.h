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
#include <ArduinoJson.h>
#include <Storage.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#endif //ESP8266

#ifdef ESP32_DEV
#include <WiFi.h>
#endif //ESP32_DEV

#ifndef _BSKP_TRANSCEIVER_H_
#define _BSKP_TRANSCEIVER_H_

#define DEBUG_PORT Serial

#ifndef MESSAGE_BUFF_SIZE
#define MESSAGE_BUFF_SIZE 512
#endif


/**
 * Implement these methods in your code to handle incoming commands
 * Return true to ack the message, false to nack the message
 */
extern bool handleIncoming(uint32_t messageId, JsonObject& header, JsonObject& message);

//===================================================================


/**
 * These methods has to be implemented by Transceivers
 */ 
extern void initController();
extern void sendMessage(int messageId, JsonObject& data);
extern void sendAck(JsonObject& header, uint32_t corrId, int ack);
extern void checkIncoming();

//===================================================================

void checkAndConnect();
void parseIncoming(byte* data);
void sendHeartbeat();
void doOTA(String model, String version);

extern String wifiSSID;
extern String wifiPSK;
extern String domainKey;
extern String apiKey;
extern const String deviceModel;
extern const String firmwareVersion;
extern String deviceId;
extern long lastMessage;
extern char API_URL[];

#define MSG_PING 1
#define MSG_ACK 2
#define MSG_FACTORY_RESET 97
#define MSG_OTA 98
#define MSG_REBOOT 99

extern String apiBastPath;
extern String apiFingerprint;
extern bool apiHttps;
extern bool _factoryResetRequested;
extern bool _rebootRequested;
extern bool _otaRequested;

#ifdef USE_UDP

extern String udpHost;
extern uint16_t udpPort;
extern uint16_t udpHeartbeat; 

#endif //USE_UDP

#ifdef USE_MQTT

#define MQTT_CLIENT_ID_LEN 25
#define MQTT_USER_ID_LEN 40
#define MQTT_PASSWD_LEN 25
#define MQTT_IN_TOPIC_LEN 80
#define MQTT_OUT_TOPIC_LEN 128

extern String mqttHost;
extern uint16_t mqttPort;
extern uint16_t mqttHeartbeat;

#endif //USE_MQTT

#ifdef USE_HTTP

extern uint16_t httpHeartbeat;

#endif //USE_HTTP

#endif //_BSKP_TRANSCEIVER_H_
