#ifdef USE_UDP

#include <WiFiUdp.h>
#include <BoodskapTransceiver.h>
#include "BoodskapUdpTransceiver.h"

WiFiUDP Udp;
char UDP_PACKET[MESSAGE_BUFF_SIZE];
long lastMessage = 0;

void sendData(int messageId, JsonObject &root)
{

  String jsonStr;
  root.printTo(jsonStr);

  if (messageId >= 100)
  { //Print only user defined messages
    DEBUG_PORT.println(jsonStr);
  }

  Udp.beginPacket(UDP_HOST, UDP_PORT);
  Udp.write(jsonStr.c_str());
  Udp.endPacket();

  lastMessage = millis();
}

void sendMessage(int messageId, JsonObject &data)
{

  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  JsonObject &header = jsonBuffer.createObject();

  header["key"] = DOMAIN_KEY;
  header["api"] = API_KEY;
  header["did"] = deviceId.c_str();
  header["dmdl"] = DEVICE_MODEL;
  header["fwver"] = FIRMWARE_VERSION;
  header["mid"] = messageId;

  root["header"] = header;
  root["data"] = data;

  sendData(messageId, root);
}

void sendAck(JsonObject& header, uint32_t corrId, int ack)
{

  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  JsonObject &data = jsonBuffer.createObject();

  header["mid"] = MSG_ACK;
  data["acked"] = ack;

  root["header"] = header;
  root["data"] = data;

  sendData(MSG_ACK, root);
  
}

void initController()
{
  Udp.begin(UDP_LOCAL_PORT);
  DEBUG_PORT.printf("UDP is Now listening at IP %s\n", WiFi.localIP().toString().c_str());
}

void checkIncoming()
{

  int packetSize = Udp.parsePacket();

  if (packetSize)
  {
    DEBUG_PORT.printf("UDP Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(UDP_PACKET, MESSAGE_BUFF_SIZE);
    if (len > 0)
    {
      UDP_PACKET[len] = 0; //Null terminate
      parseIncoming((byte *)UDP_PACKET);
    }
  }

  if ((millis() - lastMessage) >= UDP_HEARTBEAT_INTERVAL)
  {
    sendHeartbeat();
  }
}

#endif //USE_UDP