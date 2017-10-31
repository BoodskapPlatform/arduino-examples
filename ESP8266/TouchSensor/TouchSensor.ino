#include <ESP8266WiFi.h>
#include "Transceiver.h"

//#define USE_UDP
#define USE_MQTT
//#define USE_HTTP

#if defined(USE_UDP)
#include "UdpTransceiver.h"
#elif defined(USE_MQTT)
#include "MqttTransceiver.h"
#elif defined(USE_HTTP)
#include "HttpTransceiver.h"
#endif

bool touched = false;
int lastState = LOW;

void setup() {

  DEBUG_PORT.begin(BAUD_RATE);

  pinMode(TOUCH_PIN, INPUT);

  DEBUG_PORT.println();

}

void loop() {

  checkAndConnect();

  int currentState = digitalRead(TOUCH_PIN);

  if (currentState == HIGH && lastState == LOW) {

    touched = !touched; //toggle state

    StaticJsonBuffer<32> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
    data["state"] = touched;

    DEBUG_PORT.println( touched ? "ON" : "OFF");

    sendMessage(100, data);

  }

  lastState = currentState;

  checkIncoming();

}

bool handleIncoming(JsonObject& header, JsonObject& data){
  //Messages from platform reaches here

  bool acked = false;
  uint16_t mid = header["mid"].as<uint16_t>();
  
  switch(mid){
  }

  return acked;
}

