
#ifndef _UDP_CONTROLLER_H_
#define _UDP_CONTROLLER_H_

#include <WiFiUdp.h>
#include "Transceiver.h"

#define UDP_HOST "udp.boodskap.io"
#define UDP_PORT 5555

WiFiUDP Udp;
char UDP_PACKET[MESSAGE_BUFF_SIZE];

void sendMessage(int messageId, JsonObject& data) {

  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& header = jsonBuffer.createObject();

  header["key"] = DOMAIN_KEY;
  header["api"] = API_KEY;
  header["did"] = deviceId.c_str();
  header["dmdl"] = DEVICE_MODEL;
  header["fwver"] = FIRMWARE_VERSION;
  header["mid"] = messageId;

  root["header"] = header;
  root["data"] = data;

  String jsonStr;
  root.printTo(jsonStr);

  DEBUG_PORT.println(jsonStr);

  Udp.beginPacket(UDP_HOST, UDP_PORT);
  Udp.write(jsonStr.c_str());
  Udp.endPacket();
}

void initController() {
  Udp.begin(UDP_LOCAL_PORT);
  DEBUG_PORT.printf("UDP is Now listening at IP %s\n", WiFi.localIP().toString().c_str());
}

void checkIncoming() {

  int packetSize = Udp.parsePacket();

  if (packetSize) {
    DEBUG_PORT.printf("UDP Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(UDP_PACKET, MESSAGE_BUFF_SIZE);
    if (len > 0)
    {
      UDP_PACKET[len] = 0; //Null terminate
      parseIncoming((byte*)UDP_PACKET);
    }
  }
}



#endif //_UDP_CONTROLLER_H_
