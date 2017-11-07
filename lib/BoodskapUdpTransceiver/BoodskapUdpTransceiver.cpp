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
#ifdef USE_UDP

#include "BoodskapUdpTransceiver.h"

WiFiUDP Udp;
char UDP_PACKET[MESSAGE_BUFF_SIZE];

void sendData(int messageId, JsonObject &root)
{

  String jsonStr;
  root.printTo(jsonStr);

  if (messageId >= 0)
  { //Print only user defined messages
    DEBUG_PORT.print("Sending: ");
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

  header["key"] = domainKey.c_str();
  header["api"] = apiKey.c_str();
  header["did"] = deviceId.c_str();
  header["dmdl"] = deviceModel.c_str();
  header["fwver"] = firmwareVersion.c_str();
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

  header["key"] = domainKey.c_str();
  header["api"] = apiKey.c_str();
  header["did"] = deviceId.c_str();
  header["dmdl"] = deviceModel.c_str();
  header["fwver"] = firmwareVersion.c_str();
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

  if ((millis() - lastMessage) >= (UDP_HEARTBEAT*1000))
  {
    sendHeartbeat();
  }
}

#endif //USE_UDP