#include <Application.h>
#include <BoodskapTransceiver.h>

#if defined(USE_UDP)
#include <BoodskapUdpTransceiver.h>
#elif defined(USE_MQTT)
#include <BoodskapMqttTransceiver.h>
#elif defined(USE_HTTP)
#include <BoodskapHttpTransceiver.h>
#endif

#if defined(IMPL_TOUCH_SENSOR)
#pragma message("*** Using Touch Sensor Implementation ****")
#include <TouchSensor.h>
#elif defined(IMPL_TEMP_SENSOR)
#pragma message("*** Using Temperature Sensor Implementation ****")
#include <TemperatureSensor.h>
#else
#error "*** No Implementation Selected, Use one of IMPL_TOUCH_SENSOR, IMPL_TEMP_SENSOR, etc... ***"
#endif


void setup() {

  DEBUG_PORT.begin(BAUD_RATE);

  setupApp();
}

void loop() {

  loopApp();

}
