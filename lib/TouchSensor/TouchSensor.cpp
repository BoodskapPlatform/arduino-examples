#ifdef IMPL_TOUCH_SENSOR

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#include "TouchSensor.h"

bool touched = false;
int lastState = LOW;

void setupApp()
{

  pinMode(TOUCH_PIN, INPUT);

  DEBUG_PORT.println();
}

void loopApp()
{

  checkAndConnect();

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

#endif //IMPL_TOUCH_SENSOR