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
#ifdef BSKP_FW

#include <Application.h>
#include <BoodskapTransceiver.h>
#include <Timer.h>

#if defined(USE_UDP)
#include <BoodskapUdpTransceiver.h>
#elif defined(USE_MQTT)
#include <BoodskapMqttTransceiver.h>
#elif defined(USE_HTTP)
#include <BoodskapHttpTransceiver.h>
#endif

Timer timer;

void setup()
{

  DEBUG_PORT.begin(BAUD_RATE);
  DEBUG_PORT.println();
  DEBUG_PORT.println();
  DEBUG_PORT.println("///");
  DEBUG_PORT.printf("MODEL:%s\r\n", deviceModel.c_str());
  DEBUG_PORT.printf("VERSION:%s\r\n", firmwareVersion.c_str());
  DEBUG_PORT.printf("BUILD:%d\r\n", BUILD_TIMESTAMP);
  DEBUG_PORT.println("///");

  delay(100);

  setupTransceiver();

  setupApp();

#ifdef ESP8266
  pinMode(0, INPUT);
#endif
}

void loop()
{

#ifdef ESP8266
  if (digitalRead(0) == LOW) //If FLASH button is pressed for more than a 2 seconds
  {
    delay(1500);
    if (digitalRead(0) == LOW)
    {
      _factoryResetRequested = true;
    }
  }
#endif

  checkAndConnect();

  loopApp();

  checkIncoming();

  timer.update();
}

#endif //BSKP_FW