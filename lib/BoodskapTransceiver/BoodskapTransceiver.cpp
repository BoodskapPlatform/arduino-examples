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
#include "BoodskapTransceiver.h"

Storage flash;

String deviceId;
String domainKey;
String apiKey;
String wifiSSID;
String wifiPSK;
long lastMessage = 0;
char API_URL[API_URL_LEN];
bool _factoryResetRequested = false;
bool _rebootRequested = false;
bool _otaRequested = false;
String _otaModel;
String _otaVersion;
bool configured = false;
bool shouldSaveConfig = false;
String apiBastPath;
String apiFingerprint;
bool apiHttps = true;
int maxTries = 0;

#ifdef USE_UDP
String udpHost;
uint16_t udpPort;
uint16_t udpHeartbeat;
#elif defined USE_MQTT
String mqttHost;
uint16_t mqttPort;
uint16_t mqttHeartbeat;
#elif defined USE_HTTP
uint16_t httpHeartbeat;
#endif

void setupTransceiver()
{

  domainKey = DOMAIN_KEY;
  apiKey = API_KEY;
  wifiSSID = WIFI_SSID;
  wifiPSK = WIFI_PSK;
  apiBastPath = API_BASE_PATH;
  apiFingerprint = API_FINGERPRINT;
  apiHttps = apiBastPath.startsWith("https");

#ifdef ESP8266
  deviceId = "ESP8266-";
  deviceId += String(ESP.getChipId());
#elif defined ESP32_DEV
  char cid[32];
  uint64_t chipid = ESP.getEfuseMac();
  sprintf(cid, "%04X", (uint16_t)(chipid>>32));
  deviceId = "ESP32-";
  deviceId += cid;
#endif

#ifdef USE_UDP

  udpHost = UDP_HOST;
  udpPort = UDP_PORT;
  udpHeartbeat = UDP_HEARTBEAT;

#elif defined USE_MQTT

  mqttHost = MQTT_HOST;
  mqttPort = MQTT_PORT;
  mqttHeartbeat = MQTT_HEARTBEAT;

#elif defined USE_HTTP

  httpHeartbeat = HTTP_HEARTBEAT;

#endif

  if (!flash.open())
  {
    DEBUG_PORT.println("SPI Flash File System, failed opening, formatting....");
    flash.format();
    flash.open();
  }

  if (flash.exists(BSKP_CONFIG_FILE))
  {
    size_t read = 0;
    String content = flash.readFile(BSKP_CONFIG_FILE, &read);
    if (read > 0)
    {
      DEBUG_PORT.printf("Read %d bytes from FLASH\nContent:\n%s\n", read, content.c_str());

      StaticJsonBuffer<CONFIG_SIZE> jsonBuffer;
      JsonObject &root = jsonBuffer.parse(content);

      if (root.success())
      {

        configured = true;
        wifiSSID = root["ssid"].as<String>();
        wifiPSK = root["psk"].as<String>();
        domainKey = root["dkey"].as<String>();
        apiKey = root["akey"].as<String>();

        apiBastPath = root["api_url"].as<String>();
        apiFingerprint = root["api_fp"].as<String>();

        apiBastPath.toLowerCase();
        apiHttps = apiBastPath.startsWith("https");

#ifdef USE_UDP

        udpHost = root["udp_host"].as<String>();
        udpPort = root["udp_port"].as<uint16_t>();

#elif defined USE_MQTT

        mqttHost = root["mqtt_host"].as<String>();
        mqttPort = root["mqtt_port"].as<uint16_t>();

#endif
      }
      else
      {
        DEBUG_PORT.println("**** UNABLE TO PARSE CONFIG ****");
      }
    }
  }
  else
  {
    DEBUG_PORT.printf("Config file %s not found\n", BSKP_CONFIG_FILE);
  }

FINISH:

  flash.close();

  DEBUG_PORT.printf("*** Configured = %d ***\n", configured);

  delay(300);
}

void saveConfigCallback()
{
  DEBUG_PORT.println("Should save config = true");
  shouldSaveConfig = true;
}

void checkAndConnect()
{

START:
  ++maxTries;
  int tries = 0;

  if (_factoryResetRequested)
  {
    DEBUG_PORT.println("*** Performing factory reset *****");

#ifdef ESP8266
    WiFiManager wifiManager;
    wifiManager.resetSettings();
#endif

    bool formatted = flash.format();
    DEBUG_PORT.printf("Formatted FLASH = %s\n", formatted ? "true" : "false");
    _rebootRequested = true;
  }

  if (_rebootRequested)
  {
    DEBUG_PORT.println("*** Rebooting *****");
    ESP.restart();
    _rebootRequested = false;
  }

  if (_otaRequested)
  {
    doOTA(_otaModel, _otaVersion);
    _otaRequested = false;
  }

#ifdef ESP8266
  if (!configured)
  {

    WiFiManager wifiManager;
    //wifiManager.resetSettings();
    wifiManager.setTimeout(120);
    wifiManager.setConfigPortalTimeout(300);
    wifiManager.setConnectTimeout(30);
    wifiManager.setSaveConfigCallback(saveConfigCallback);

    WiFiManagerParameter _p_dkey("dkey", "Domain Key", domainKey.c_str(), 15);
    WiFiManagerParameter _p_akey("akey", "API Key", apiKey.c_str(), 15);
    WiFiManagerParameter _p_api_url("api_url", "API Base URL", apiBastPath.c_str(), 40);
    WiFiManagerParameter _p_api_fp("api_fp", "API HTTPS Fingerprint", apiFingerprint.c_str(), 60);
    WiFiManagerParameter _p_api_https("api_https", "If HTTPS API", "true", 6);

    wifiManager.addParameter(&_p_dkey);
    wifiManager.addParameter(&_p_akey);
    wifiManager.addParameter(&_p_api_url);
    wifiManager.addParameter(&_p_api_fp);
    wifiManager.addParameter(&_p_api_https);

#ifdef USE_UDP
    WiFiManagerParameter _p_udp_host("udp_host", "UDP Host/IP", UDP_HOST, 40);
    WiFiManagerParameter _p_udp_port("udp_port", "UDP Port", String(UDP_PORT).c_str(), 8);
    wifiManager.addParameter(&_p_udp_host);
    wifiManager.addParameter(&_p_udp_port);
#elif defined USE_MQTT
    WiFiManagerParameter _p_mqtt_host("mqtt_host", "MQTT Host/IP", MQTT_HOST, 40);
    WiFiManagerParameter _p_mqtt_port("mqtt_port", "MQTT Port", String(MQTT_PORT).c_str(), 8);
    wifiManager.addParameter(&_p_mqtt_host);
    wifiManager.addParameter(&_p_mqtt_port);
#endif

    //set static ip
    wifiManager.setAPStaticIPConfig(IPAddress(10, 0, 1, 99), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));

    if (!wifiManager.startConfigPortal(deviceId.c_str(), "boodskap"))
    {
      DEBUG_PORT.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }

    if (shouldSaveConfig)
    {

      StaticJsonBuffer<CONFIG_SIZE> jsonBuffer;
      JsonObject &root = jsonBuffer.createObject();

      root["ssid"] = WiFi.SSID();
      root["psk"] = WiFi.psk();
      root["dkey"] = _p_dkey.getValue();
      root["akey"] = _p_akey.getValue();
      root["api_url"] = _p_api_url.getValue();
      root["api_fp"] = _p_api_fp.getValue();
      root["api_https"] = String(_p_api_https.getValue()).equalsIgnoreCase("true");

#ifdef USE_UDP
      root["udp_host"] = _p_udp_host.getValue();
      root["udp_port"] = String(_p_udp_port.getValue()).toInt();
#elif defined USE_MQTT
      root["mqtt_host"] = _p_mqtt_host.getValue();
      root["mqtt_port"] = String(_p_mqtt_port.getValue()).toInt();
#endif

      String jsonStr;
      root.printTo(jsonStr);
      flash.open();
      flash.writeFile(BSKP_CONFIG_FILE, jsonStr);
      flash.close();

      _rebootRequested = true;
    }

    return;
  }
#endif //ESP8266

  if (WiFi.status() == WL_CONNECTED)
  {
    maxTries = 0;
    return;
  }

BEGIN:

  ++tries;
  long started = millis();

  DEBUG_PORT.printf("Connecting to %s ", wifiSSID.c_str());

  WiFi.begin(wifiSSID.c_str(), wifiPSK.c_str());

  while (WiFi.status() != WL_CONNECTED)
  {

    delay(500);

    DEBUG_PORT.print(".");

    if ((millis() - started) > 15000)
    {
      DEBUG_PORT.println("\n");

      int n = WiFi.scanNetworks();

      if (n <= 0)
      {
        DEBUG_PORT.println("No WiFi network found!!");
      }
      else
      {
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

      if (maxTries >= 9)
      {
        _rebootRequested = true;
        return;
      }
      else if (tries >= 3)
      {
        configured = false;
        goto START;
      }
      else
      {
        goto BEGIN;
      }
    }
  }

  DEBUG_PORT.println();

  DEBUG_PORT.printf("Connected to %s \n", wifiSSID.c_str());
  DEBUG_PORT.printf("DomainKey: %s, ApiKey: %s, DeviceID: %s, Model: %s, FWVersion: %s\n", domainKey.c_str(), apiKey.c_str(), deviceId.c_str(), deviceModel.c_str(), firmwareVersion.c_str());

  initController();
}

void sendHeartbeat()
{
  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();
  data["uptime"] = millis();
  data["freeheap"] = ESP.getFreeHeap();
  
  #ifdef ESP8266
  data["vcc"] = ESP.getVcc();
  #endif

  sendMessage(MSG_PING, data);
}

#ifdef ESP8266

void doESP8266OTA(String model, String version)
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

#endif //ESP8266

#ifdef ESP32_DEV
void doESP32OTA(String model, String version)
{
}
#endif //ESP32_DEV

void doOTA(String model, String version)
{
#ifdef ESP8266
  doESP8266OTA(model, version);
#elif defined ESP32_DEV
  doESP32OTA(model, version);
#endif
}

void parseIncoming(byte *data)
{

  //DEBUG_PORT.println("Message received");
  //DEBUG_PORT.println((char*)data);

  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(data);

  bool invalid = !root.success();

  if (invalid)
  {
    DEBUG_PORT.println("Invalid json data received, unable to parse.");
    DEBUG_PORT.println((char *)data);
    return;
  }

  invalid = (!root.containsKey("header"));
  invalid = (invalid || !root.containsKey("data"));

  if (invalid)
  {
    DEBUG_PORT.println("Invalid message received");
    DEBUG_PORT.println((char *)data);
    return;
  }

  JsonObject &header = root["header"];
  JsonObject &message = root["data"];

  invalid = (!header.containsKey("key") || !header["key"].is<const char *>());
  invalid = (invalid || !header.containsKey("api") || !header["api"].is<const char *>());
  invalid = (invalid || !header.containsKey("did") || !header["did"].is<const char *>());
  invalid = (invalid || !header.containsKey("mid") || !header["mid"].is<uint32_t>());

  if (invalid)
  {
    DEBUG_PORT.println("Invalid message received");
    DEBUG_PORT.println((char *)data);
    return;
  }

  String dkey = header["key"];
  if (dkey != domainKey)
  {
    DEBUG_PORT.println("Invalid message received, DOMAIN_KEY mismatch");
    return;
  }

  String akey = header["api"];
  if (akey != apiKey)
  {
    DEBUG_PORT.println("Invalid message received, API_KEY mismatch");
    return;
  }

  String did = header["did"];
  if (did != deviceId)
  {
    DEBUG_PORT.println("Invalid message received, DEVICE_ID mismatch");
    return;
  }

  bool shouldAck = header.containsKey("corrid");
  uint32_t messageId = header["mid"].as<uint32_t>();

  bool ack = false;

  if (messageId >= 100 || messageId < 0)
  { //User defined commands
    ack = handleIncoming(messageId, header, message);
  }
  else
  { //System commands

    switch (messageId)
    {
    case MSG_PING: //ping
      shouldAck = false;
      sendHeartbeat();
      break;
    case MSG_FACTORY_RESET:
      ack = _factoryResetRequested = true;
      break;
    case MSG_OTA:

      _otaRequested = message.containsKey("model");
      _otaRequested = _otaRequested && message.containsKey("version");

      if (_otaRequested)
      {
        const char *model = message["model"];
        const char *version = message["version"];
      }

      ack = _otaRequested;
      break;

    case MSG_REBOOT:
      _rebootRequested = ack = true;
      break;
    }
  }

  if (shouldAck)
  {
    uint32_t corrId = header["corrid"];
    sendAck(header, corrId, ack ? 1 : 0);
  }
}
