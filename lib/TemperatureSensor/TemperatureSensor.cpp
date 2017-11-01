#ifdef IMPL_TEMP_SENSOR

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#include "TemperatureSensor.h"

long lastPrint = 0;

void setupApp()
{

  pinMode(TOUCH_PIN, INPUT);

  DEBUG_PORT.println();
}

void loopApp()
{

  checkAndConnect();

  if ((millis() - lastPrint) >= 5000)
  {
    DEBUG_PORT.println(millis());
  }

  checkIncoming();
}

bool handleIncoming(JsonObject &header, JsonObject &data)
{
  //Messages from platform reaches here

  bool acked = false;
  uint16_t mid = header["mid"].as<uint16_t>();

  switch (mid)
  {
  }

  return acked;
}

#endif //IMPL_TEMP_SENSOR