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