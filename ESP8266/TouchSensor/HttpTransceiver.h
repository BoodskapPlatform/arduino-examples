#ifndef _HTTP_CONTROLLER_H_
#define _HTTP_CONTROLLER_H_

#include <ESP8266HTTPClient.h>
#include "Transceiver.h"

#define API_BASE_PATH "https://api.boodskap.io/push/raw"
#define API_FINGERPRINT "B9:01:85:CE:E3:48:5F:5E:E1:19:74:CC:47:A1:4A:63:26:B4:CB:32"

char API_BASE_URL[96];
char API_URL[128];

void sendMessage(int messageId, JsonObject& data) {

  HTTPClient http;

  //https://api.boodskap.io/push/raw/{dkey}/{akey}/{did}/{dmdl}/{fwver}/{mid}
  sprintf(API_URL, "%s/%d", API_BASE_URL, messageId);

  String jsonStr;
  data.printTo(jsonStr);

  DEBUG_PORT.println(API_URL);
  DEBUG_PORT.println(jsonStr);

  http.begin(API_URL, API_FINGERPRINT);
  http.addHeader("Content-Type", "text/plain");

  int httpCode = http.POST(jsonStr);
  String payload = http.getString();

  DEBUG_PORT.println(httpCode);
  DEBUG_PORT.println(payload);

  http.end();
}

void initController() {

  //No initialization required for HTTP controller
  DEBUG_PORT.println("!!! Using HTTP controller, downstream messages are not handled !!!");

  //https://api.boodskap.io/push/raw/{dkey}/{akey}/{did}/{dmdl}/{fwver}/{mid}
  sprintf(API_BASE_URL, "%s/%s/%s/%s/%s/%s", API_BASE_PATH, DOMAIN_KEY, API_KEY, deviceId.c_str(), DEVICE_MODEL, FIRMWARE_VERSION);

  DEBUG_PORT.printf("POST URL: %s\n", API_BASE_URL);

}

void checkIncoming() {
  //HTTP controller don't receive messages from platform, ignore
}



#endif //_HTTP_CONTROLLER_H_
