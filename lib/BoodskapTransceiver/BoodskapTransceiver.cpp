#include <ArduinoJson.h>
#include <BoodskapTransceiver.h>
#include <ESP8266httpUpdate.h>

#ifdef DEVICE_ID
String deviceId = DEVICE_ID;
#else
String deviceId;
#endif

bool _rebootRequested = false;
bool _otaRequested = false;
String _otaURI;
bool _otaHttps = false;
String _otaFingerprint;

void checkAndConnect()
{

  if(_rebootRequested){
    ESP.restart();
    _rebootRequested = false;
  }

  if(_otaRequested){
    doOTA(_otaURI.c_str(), _otaHttps, _otaFingerprint.c_str());
    _otaRequested = false;
  }

  if (WiFi.status() == WL_CONNECTED){
    return;
  }

#ifndef DEVICE_ID
  deviceId = "ESP8266-";
  deviceId += ESP.getChipId();
#endif

BEGIN:

  long started = millis();

  DEBUG_PORT.printf("Connecting to %s ", WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

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

      goto BEGIN;
    }
  }

  DEBUG_PORT.println();

  DEBUG_PORT.printf("Connected to %s \n", WIFI_SSID);
  DEBUG_PORT.printf("DomainKey: %s, ApiKey: %s, DeviceID: %s, Model: %s, FWVersion: %s\n", DOMAIN_KEY, API_KEY, deviceId.c_str(), DEVICE_MODEL, FIRMWARE_VERSION);

  initController();
}

void sendHeartbeat()
{
  StaticJsonBuffer<MESSAGE_BUFF_SIZE> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();
  data["uptime"] = millis();
  data["vcc"] = ESP.getVcc();
  data["freeheap"] = ESP.getFreeHeap();
  sendMessage(MSG_PING, data);
}

void doOTA(const char *url, bool https, const char *fingerprint)
{

  t_httpUpdate_return ret;

  DEBUG_PORT.println("Downloading new firmware from ");
  DEBUG_PORT.println(url);

  if (https)
  {
    ret = ESPhttpUpdate.update(url, FIRMWARE_VERSION, fingerprint);
  }
  else
  {
    ret = ESPhttpUpdate.update(url, FIRMWARE_VERSION);
  }

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
  if (dkey != DOMAIN_KEY)
  {
    DEBUG_PORT.println("Invalid message received, DOMAIN_KEY mismatch");
    return;
  }

  String akey = header["api"];
  if (akey != API_KEY)
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
    case MSG_OTA:
      
      _otaRequested = message.containsKey("url");

      if(_otaRequested){
        _otaHttps = message.containsKey("https");
        const char* url = message["url"];
        _otaURI = String(url);
        if(_otaHttps){
          const char* fpr = message["https"];
          _otaFingerprint = String(fpr);
        }else{
          _otaFingerprint = "";
        }
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
