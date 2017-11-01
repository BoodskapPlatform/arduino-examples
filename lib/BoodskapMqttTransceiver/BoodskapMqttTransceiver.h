#ifdef USE_MQTT

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <BoodskapTransceiver.h>

#ifdef USE_MQTT

#ifndef _BSKP_MQTT_TRANSCEIVER_
#define _BSKP_MQTT_TRANSCEIVER_

#define MQTT_HOST "mqtt.boodskap.io"
#define MQTT_PORT 1883

#define MQTT_CLIENT_ID_LEN 25
#define MQTT_USER_ID_LEN 40
#define MQTT_PASSWD_LEN 25
#define MQTT_IN_TOPIC_LEN 80
#define MQTT_OUT_TOPIC_LEN 128

#endif

#endif //_BSKP_MQTT_TRANSCEIVER_

#endif //USE_MQTT