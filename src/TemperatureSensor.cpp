#ifdef IMPL_TEMP_SENSOR

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#pragma message("*** Using Temperature Sensor Implementation ****")

long lastPrint = 0;

void setupApp()
{

  DEBUG_PORT.println();
}

void loopApp()
{

  checkAndConnect();

  if ((millis() - lastPrint) >= 5000)
  {
    DEBUG_PORT.println(millis());
    lastPrint = millis();
  }

  checkIncoming();
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

#endif //IMPL_TEMP_SENSOR