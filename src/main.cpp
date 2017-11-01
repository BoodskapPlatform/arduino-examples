#include <Application.h>
#include <BoodskapTransceiver.h>

#if defined(USE_UDP)
#include <BoodskapUdpTransceiver.h>
#elif defined(USE_MQTT)
#include <BoodskapMqttTransceiver.h>
#elif defined(USE_HTTP)
#include <BoodskapHttpTransceiver.h>
#endif

void setup() {

  DEBUG_PORT.begin(BAUD_RATE);

  setupApp();
}

void loop() {

  loopApp();

}
