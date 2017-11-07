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
#ifdef USE_HTTP

#include "BoodskapHttpTransceiver.h"

void sendMessage(int messageId, JsonObject &data)
{

      HTTPClient http;
    
      //https://api.boodskap.io/push/raw/{dkey}/{akey}/{did}/{dmdl}/{fwver}/{mid}
      sprintf(API_URL, "%s/push/raw/%s/%s/%s/%s/%s/%d", API_BASE_PATH, domainKey.c_str(), apiKey.c_str(), deviceId.c_str(), deviceModel.c_str(), firmwareVersion.c_str(), messageId);
    
      String jsonStr;
      data.printTo(jsonStr);
    
      DEBUG_PORT.print("Sending: ");
      DEBUG_PORT.println(API_URL);
      DEBUG_PORT.println(jsonStr);

      #ifdef API_HTTPS
      http.begin(API_URL, API_FINGERPRINT);
      #else
      http.begin(API_URL);
      #endif

      http.addHeader("Content-Type", "text/plain");
    
      int httpCode = http.POST(jsonStr);
      String payload = http.getString();
    
      DEBUG_PORT.println(httpCode);
      DEBUG_PORT.println(payload);
    
      http.end();

      lastMessage = millis();
}

void initController()
{
  //No initialization required for HTTP controller
  DEBUG_PORT.println("!!! Using HTTP controller, downstream messages are not handled !!!");
  
}

void checkIncoming()
{

  //HTTP won't receive messages from the platform

  if ((millis() - lastMessage) >= (HTTP_HEARTBEAT*1000))
  {
    sendHeartbeat();
  }
}

void sendAck(JsonObject& header, uint32_t corrId, int ack)
{
  //Since we don't receive messages through HTTP, we don't implement this
}

#endif //USE_HTTP