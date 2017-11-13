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
#ifdef IMPL_GAS_SENSOR

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#pragma message("*** Using GAS Sensor Implementation ****")

#ifdef ESP8266
const String mPrefix = "BSKP-ESP8266-GAS-";
#define SENSOR_ANALOG_PIN A0
#define SENSOR_DIGITAL_PIN D5
#elif ESP32_DEV
const String mPrefix = "BSKP-ESP32-GAS-";
#define SENSOR_ANALOG_PIN A0
#define SENSOR_DIGITAL_PIN 14
#endif

#if defined(USE_UDP)
const String deviceModel = mPrefix + String("UDP");
#elif defined(USE_MQTT)
const String deviceModel = mPrefix + String("MQTT");
#elif defined(USE_HTTP)
const String deviceModel = mPrefix + String("HTTP");
#endif

#define MSG_STATUS 500000200

#define SEND_DEVIATION_PERCENTAGE 10

const String firmwareVersion = "1.0.3";

void takeReading();
void sendReading();

int oldValue = 0;

void setupApp()
{

  pinMode(SENSOR_DIGITAL_PIN, INPUT);
  pinMode(SENSOR_ANALOG_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  DEBUG_PORT.println();
  DEBUG_PORT.printf("SENSOR_DIGITAL_PIN: %d\n", SENSOR_DIGITAL_PIN);
  DEBUG_PORT.printf("SENSOR_ANALOG_PIN: %d\n", SENSOR_ANALOG_PIN);

  timer.oscillate(LED_BUILTIN, 3000, LOW);
  timer.every(1000, &takeReading);
  timer.every(60000, &sendReading);
  
  delay(1000);
}

void loopApp()
{
  //We do nothing here, we timer functions takes cares...
}


void takeReading()
{
  int currentState = digitalRead(SENSOR_DIGITAL_PIN);
  int value = analogRead(SENSOR_ANALOG_PIN);

  DEBUG_PORT.printf("gasleak:%s, value=%d\n", currentState == HIGH ? "true" : "false" , value);

  int diff = (value - oldValue);
  if(diff < 0){
    diff = (diff * -1);
  }

  if(diff >= SEND_DEVIATION_PERCENTAGE){
    sendReading();
  }

  oldValue = value;
}

void sendReading()
{

  digitalWrite(LED_BUILTIN, LOW);

  int currentState = digitalRead(SENSOR_DIGITAL_PIN);
  int value = analogRead(SENSOR_ANALOG_PIN);

  StaticJsonBuffer<64> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();
  data["gasleak"] = currentState == HIGH ? false : true;
  data["value"] = value;

  sendMessage(MSG_STATUS, data);

}

bool handleIncoming(uint32_t messageId, JsonObject &header, JsonObject &data)
{
  //Messages from platform reaches here

  bool acked = false;

  switch (messageId)
  {
  }

  return acked;
}

bool handleIncoming(byte* data){
  return true;
}

#endif //IMPL_GAS_SENSOR