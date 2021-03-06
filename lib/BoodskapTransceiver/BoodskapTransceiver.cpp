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

/**
WiFiEventHandler onStationModeConnected(std::function<void(const WiFiEventStationModeConnected&)>);
WiFiEventHandler onStationModeDisconnected(std::function<void(const WiFiEventStationModeDisconnected&)>);
WiFiEventHandler onStationModeAuthModeChanged(std::function<void(const WiFiEventStationModeAuthModeChanged&)>);
WiFiEventHandler onStationModeGotIP(std::function<void(const WiFiEventStationModeGotIP&)>);
WiFiEventHandler onStationModeDHCPTimeout(std::function<void(void)>); 
*/

void onStationConnected(const WiFiEventStationModeConnected &event)
{
  DEBUG_PORT.printf("SSID %s connected, CHANNEL: %s\n", event.ssid.c_str(), event.channel);
}

void onStationDisconnected(const WiFiEventStationModeDisconnected &event)
{

  DEBUG_PORT.printf("SSID %s disconnected, REASON: ", event.ssid.c_str());

  switch(event.reason){
    case WIFI_DISCONNECT_REASON_AUTH_EXPIRE: DEBUG_PORT.println("AUTH_EXPIRE"); break;
    case WIFI_DISCONNECT_REASON_AUTH_LEAVE: DEBUG_PORT.println("AUTH_LEAVE"); break;
    case WIFI_DISCONNECT_REASON_ASSOC_EXPIRE: DEBUG_PORT.println("ASSOC_EXPIRE"); break;
    case WIFI_DISCONNECT_REASON_ASSOC_TOOMANY: DEBUG_PORT.println("ASSOC_TOOMANY"); break;
    case WIFI_DISCONNECT_REASON_NOT_AUTHED: DEBUG_PORT.println("NOT_AUTHED"); break;
    case WIFI_DISCONNECT_REASON_NOT_ASSOCED: DEBUG_PORT.println("NOT_ASSOCED"); break;
    case WIFI_DISCONNECT_REASON_ASSOC_LEAVE: DEBUG_PORT.println("ASSOC_LEAVE"); break;
    case WIFI_DISCONNECT_REASON_ASSOC_NOT_AUTHED: DEBUG_PORT.println("ASSOC_NOT_AUTHED"); break;
    case WIFI_DISCONNECT_REASON_DISASSOC_PWRCAP_BAD: DEBUG_PORT.println("DISASSOC_PWRCAP_BAD"); break;
    case WIFI_DISCONNECT_REASON_DISASSOC_SUPCHAN_BAD: DEBUG_PORT.println("DISASSOC_SUPCHAN_BAD"); break;
    case WIFI_DISCONNECT_REASON_IE_INVALID: DEBUG_PORT.println("IE_INVALID"); break;
    case WIFI_DISCONNECT_REASON_MIC_FAILURE: DEBUG_PORT.println("MIC_FAILURE"); break;
    case WIFI_DISCONNECT_REASON_4WAY_HANDSHAKE_TIMEOUT: DEBUG_PORT.println("4WAY_HANDSHAKE_TIMEOUT"); break;
    case WIFI_DISCONNECT_REASON_GROUP_KEY_UPDATE_TIMEOUT: DEBUG_PORT.println("GROUP_KEY_UPDATE_TIMEOUT"); break;
    case WIFI_DISCONNECT_REASON_IE_IN_4WAY_DIFFERS: DEBUG_PORT.println("IE_IN_4WAY_DIFFERS"); break;
    case WIFI_DISCONNECT_REASON_GROUP_CIPHER_INVALID: DEBUG_PORT.println("GROUP_CIPHER_INVALID"); break;
    case WIFI_DISCONNECT_REASON_PAIRWISE_CIPHER_INVALID: DEBUG_PORT.println("PAIRWISE_CIPHER_INVALID"); break;
    case WIFI_DISCONNECT_REASON_AKMP_INVALID: DEBUG_PORT.println("AKMP_INVALID"); break;
    case WIFI_DISCONNECT_REASON_UNSUPP_RSN_IE_VERSION: DEBUG_PORT.println("UNSUPP_RSN_IE_VERSION"); break;
    case WIFI_DISCONNECT_REASON_INVALID_RSN_IE_CAP: DEBUG_PORT.println("INVALID_RSN_IE_CAP"); break;
    case WIFI_DISCONNECT_REASON_802_1X_AUTH_FAILED: DEBUG_PORT.println("802_1X_AUTH_FAILED"); break;
    case WIFI_DISCONNECT_REASON_CIPHER_SUITE_REJECTED: DEBUG_PORT.println("CIPHER_SUITE_REJECTED"); break;
    case WIFI_DISCONNECT_REASON_BEACON_TIMEOUT: DEBUG_PORT.println("BEACON_TIMEOUT"); break;
    case WIFI_DISCONNECT_REASON_NO_AP_FOUND: DEBUG_PORT.println("NO_AP_FOUND"); break;
    case WIFI_DISCONNECT_REASON_AUTH_FAIL: DEBUG_PORT.println("AUTH_FAIL"); break;
    case WIFI_DISCONNECT_REASON_ASSOC_FAIL: DEBUG_PORT.println("ASSOC_FAIL"); break;
    case WIFI_DISCONNECT_REASON_HANDSHAKE_TIMEOUT: DEBUG_PORT.println("HANDSHAKE_TIMEOUT"); break;
    case WIFI_DISCONNECT_REASON_UNSPECIFIED:
    default:  DEBUG_PORT.println("UNSPECIFIED"); break;
  }
  
}

void onStationAuthModeChanged(const WiFiEventStationModeAuthModeChanged &event)
{
  DEBUG_PORT.printf("WiFi Auth Mode Changed from: %d to: %d\n", event.oldMode, event.newMode);
}

void onStationGotIP(const WiFiEventStationModeGotIP &event)
{
  DEBUG_PORT.printf("WiFI Station IP: ");
  event.ip.printTo(DEBUG_PORT);
  DEBUG_PORT.println();
}

void onStationDHCPTimeout()
{
  DEBUG_PORT.println("DHCP Timeout");
}

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
  sprintf(cid, "%04X", (uint16_t)(chipid >> 32));
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

  WiFi.onStationModeAuthModeChanged(&onStationAuthModeChanged);
  WiFi.onStationModeConnected(&onStationConnected);
  //WiFi.onStationModeDHCPTimeout(&onStationDHCPTimeout);
  WiFi.onStationModeDisconnected(&onStationDisconnected);
  WiFi.onStationModeGotIP(&onStationGotIP);

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

    WiFiManager wifiManager;
    wifiManager.resetSettings();

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

    wifiManager.addParameter(&_p_dkey);
    wifiManager.addParameter(&_p_akey);
    wifiManager.addParameter(&_p_api_url);
    wifiManager.addParameter(&_p_api_fp);

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
      DEBUG_PORT.println("Configuration timeout, re-looping...");
      return;
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

  if (WiFi.status() == WL_CONNECTED)
  {
    maxTries = 0;
    return;
  }else{

    DEBUG_PORT.print("WiFI not connected, state: ");

    switch(WiFi.status()){
      case WL_NO_SHIELD: DEBUG_PORT.println("WL_NO_SHIELD"); break;
      case WL_IDLE_STATUS: DEBUG_PORT.println("WL_IDLE_STATUS"); break;
      case WL_NO_SSID_AVAIL: DEBUG_PORT.println("WL_NO_SSID_AVAIL"); break;
      case WL_SCAN_COMPLETED: DEBUG_PORT.println("WL_SCAN_COMPLETED"); break;
      case WL_CONNECT_FAILED: DEBUG_PORT.println("WL_CONNECT_FAILED"); break;
      case WL_CONNECTION_LOST: DEBUG_PORT.println("WL_CONNECTION_LOST"); break;
      case WL_DISCONNECTED: DEBUG_PORT.println("WL_DISCONNECTED"); break;
    }
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
#ifdef ESP8266
          DEBUG_PORT.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
#elif defined ESP32_DEV
          DEBUG_PORT.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
#endif
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

void parseIncoming(byte *data)
{

  DEBUG_PORT.println("\n**** Message received ****");
  DEBUG_PORT.println((char*)data);
  DEBUG_PORT.println();
  
  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(data);

  bool invalid = !root.success();

  invalid = invalid || (!root.containsKey("header"));
  invalid = (invalid || !root.containsKey("data"));

  if (invalid)
  {
    DEBUG_PORT.println("Not a JSON message");
    handleData(data);
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
    DEBUG_PORT.printf("*** User Defined Message : %d ***\n", messageId);
    ack = handleMessage(messageId, header, message);
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
        _otaModel = message["model"].as<String>();
        _otaVersion = message["version"].as<String>();
      }

      ack = _otaRequested;
      break;

    case MSG_REBOOT:
      _rebootRequested = ack = true;
      break;
    default:
      DEBUG_PORT.printf("*** Unimplemented Message: %d ***\n", messageId);
    }
  }

  if (shouldAck)
  {
    uint32_t corrId = header["corrid"];
    sendAck(header, corrId, ack ? 1 : 0);
  }
}
