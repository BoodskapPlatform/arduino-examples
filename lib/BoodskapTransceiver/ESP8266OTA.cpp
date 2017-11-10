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
 #ifdef ESP8266

#include "BoodskapTransceiver.h"

void doOTA(String model, String version)
{
  t_httpUpdate_return ret;

  //https://api.boodskap.io/push/raw/{dkey}/{akey}/{did}/{dmdl}/{fwver}/{mid}
  sprintf(API_URL, "%s/mservice/esp8266/ota?dkey=%s&akey=%s&dmodel=%s&fwver=%s", API_BASE_PATH, domainKey.c_str(), apiKey.c_str(), model.c_str(), version.c_str());

  DEBUG_PORT.println("Downloading new firmware from ");
  DEBUG_PORT.println(API_URL);

#ifdef API_HTTPS
  ret = ESPhttpUpdate.update(API_URL, version.c_str(), API_FINGERPRINT);
#else
  ret = ESPhttpUpdate.update(API_URL, version.c_str());
#endif //API_HTTPS

  switch (ret)
  {
  case HTTP_UPDATE_FAILED:
    DEBUG_PORT.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
    break;

  case HTTP_UPDATE_NO_UPDATES:
    DEBUG_PORT.println("HTTP_UPDATE_NO_UPDATES");
    break;

  case HTTP_UPDATE_OK:
    DEBUG_PORT.println("HTTP_UPDATE_OK");
    break;
  }
}


#endif