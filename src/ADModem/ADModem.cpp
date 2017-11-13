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
#ifdef IMPL_AD_MODEM

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#pragma message("*** Using Touch Sensor Implementation ****")

#ifdef ESP8266
const String mPrefix = "BSKP-ESP8266-ADM-";
#define TOUCH_PIN D5
#elif ESP32_DEV
const String mPrefix = "BSKP-ESP32-ADM-";
#define TOUCH_PIN 14
#endif

#if defined(USE_UDP)
const String deviceModel = mPrefix + String("UDP");
#elif defined(USE_MQTT)
const String deviceModel = mPrefix + String("MQTT");
#elif defined(USE_HTTP)
const String deviceModel = mPrefix + String("HTTP");
#endif

const String firmwareVersion = "1.0.0";

bool touched = false;
int lastState = LOW;
bool blink = false;
long lastRun;

void setupApp()
{


  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  DEBUG_PORT.println();
  DEBUG_PORT.printf("TOUCH_PIN: %d\n", TOUCH_PIN);


  delay(1000);
}

void loopApp()
{

  if(millis() - lastRun >= 1000){
    blink = !blink;
    digitalWrite(LED_BUILTIN, blink ? HIGH : LOW);
  }

  lastRun = millis();

  int currentState = digitalRead(TOUCH_PIN);

  if (currentState == HIGH && lastState == LOW)
  {

    touched = !touched; //toggle state

    StaticJsonBuffer<32> jsonBuffer;
    JsonObject &data = jsonBuffer.createObject();
    data["state"] = touched;

    DEBUG_PORT.println(touched ? "ON" : "OFF");

    sendMessage(100, data);
  }

  lastState = currentState;

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

#endif //IMPL_AD_MODEM