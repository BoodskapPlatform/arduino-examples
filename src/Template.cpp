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
#ifdef IMPL_YOUR_IMPL

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#pragma message("*** Your Implementation ****")

#ifdef ESP8266
const String mPrefix = "BSKP-%s-ESP8266";
#elif ESP32_DEV
const String mPrefix = "BSKP-%s-ESP32";
#endif

#if defined(USE_UDP)
const String deviceModel = mPrefix + String("UDP");
#elif defined(USE_MQTT)
const String deviceModel = mPrefix + String("MQTT");
#elif defined(USE_HTTP)
const String deviceModel = mPrefix + String("HTTP");
#endif

const String firmwareVersion = "1.0.0";

void takeReading();
void sendReading();

void setupApp()
{

  timer.every(1000, &takeReading);
  timer.every(60000, &sendReading);

  delay(1000);
}

void loopApp()
{
}

void takeReading()
{
}

void sendReading()
{

  StaticJsonBuffer<YOUR_SIZE> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();
  data["your_value"] = your_value;

  sendMessage(YOUR_MESSAGE_ID, data);
}

bool handleMessage(uint32_t messageId, JsonObject &header, JsonObject &data)
{
  //Messages from platform reaches here

  DEBUG_PORT.println("Handling message");
  
  bool acked = false;

  switch (messageId)
  {
  }

  return acked;
}

bool handleData(byte *data)
{
  DEBUG_PORT.println("Handling data");

  return true;
}

#endif //IMPL_YOUR_IMPL