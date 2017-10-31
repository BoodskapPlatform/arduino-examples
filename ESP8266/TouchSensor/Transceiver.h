#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define DEBUG_PORT Serial
#define MESSAGE_BUFF_SIZE 256

//******************** Platform Configuration **********************************************************************
//                                                                                                                **
#define DOMAIN_KEY "NKCQCVIJGS" // Change with your domain key (boodskap platform domain key)                     **
#define API_KEY "OEz3aDRHG05t" // Change with your api key (boodskap platform api key)                            **
#define DEVICE_MODEL "BSKP-ESP8266-TS" // Change this to your choice of name                                      **
#define FIRMWARE_VERSION "1.0.0" // Please follow Semantic Versioning Specification (SemVer) http://semver.org/   **
//                                                                                                                **
//******************************************************************************************************************

//
// ============================== Device Configuration ===========================================================
//
#define BAUD_RATE 115200
#define WIFI_SSID "boodskap" // Change this to suit your wifi environment
#define WIFI_PASSWORD "b00dskap" // Change this to suit your wifi environment
#define UDP_LOCAL_PORT 0 //Local UDP Port

#define TOUCH_PIN D5
//
//===================================================================================================================
//

String deviceId;

/**
 * Implement this method in your code to handle incoming commands
 * Return true to ack the message, false to nack the message
 */
extern bool handleIncoming(JsonObject& header, JsonObject& data);


void checkAndConnect();
extern void initController();
extern void sendMessage(int messageId, JsonObject& data);
extern void checkIncoming();
void parseIncoming(byte* data);

void checkAndConnect() {

  if (WiFi.status() == WL_CONNECTED) return;


  deviceId = "ESP8266-";
  deviceId += ESP.getChipId();

BEGIN:

  long started = millis();

  DEBUG_PORT.printf("Connecting to %s ", WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    DEBUG_PORT.print(".");

    if ((millis() - started) > 15000) {
      DEBUG_PORT.println("\n");

      int n = WiFi.scanNetworks();

      if (n <= 0) {
        DEBUG_PORT.println("No WiFi network found!!");
      } else {
        DEBUG_PORT.printf("%d networks found.\n", n);
        for (int i = 0; i < n; ++i)
        {
          // Print SSID and RSSI for each network found
          DEBUG_PORT.print(i + 1);
          DEBUG_PORT.print(": ");
          DEBUG_PORT.print(WiFi.SSID(i));
          DEBUG_PORT.print(" (");
          DEBUG_PORT.print(WiFi.RSSI(i));
          DEBUG_PORT.print(")");
          DEBUG_PORT.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
          delay(10);
        }
      }

      goto BEGIN;
    }
  }

  DEBUG_PORT.println();

  DEBUG_PORT.printf("Connected to %s \n", WIFI_SSID);
  DEBUG_PORT.printf("DomainKey: %s, ApiKey: %s, DeviceID: %s, Model: %s, FWVersion: %s\n", DOMAIN_KEY, API_KEY, deviceId.c_str(), DEVICE_MODEL, FIRMWARE_VERSION);

  initController();
}

void parseIncoming(byte* data){
  DEBUG_PORT.println("Message received");
  DEBUG_PORT.println((char*)data);
}

#endif //_CONTROLLER_H_
