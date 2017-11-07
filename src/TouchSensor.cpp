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
#ifdef IMPL_TOUCH_SENSOR

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#pragma message("*** Using Touch Sensor Implementation ****")

#define TOUCH_PIN D5

#if defined(USE_UDP)
const String deviceModel = "BSKP-TS-UDP";
#elif defined(USE_MQTT)
const String deviceModel = "BSKP-TS-MQTT";
#elif defined(USE_HTTP)
const String deviceModel = "BSKP-TS-HTTP";
#endif

const String firmwareVersion = "1.0.0";

bool touched = false;
int lastState = LOW;

void setupApp()
{

  pinMode(TOUCH_PIN, INPUT);

  DEBUG_PORT.println();
  DEBUG_PORT.printf("TOUCH_PIN: %d\n", TOUCH_PIN);

  delay(1000);
}

void loopApp()
{

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

#endif //IMPL_TOUCH_SENSOR