#ifndef _BSKP_TRANSCEIVER_H_
#define _BSKP_TRANSCEIVER_H_

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define DEBUG_PORT Serial

#ifndef MESSAGE_BUFF_SIZE
#define MESSAGE_BUFF_SIZE 512
#endif

/**
 * Implement these methods in your code to handle incoming commands
 */
// * Return true to ack the message, false to nack the message
extern bool handleIncoming(uint32_t messageId, JsonObject& header, JsonObject& message);

//===================================================================


/**
 * These methods has to be implemented by Transceivers
 */ 
extern void initController();
extern void sendMessage(int messageId, JsonObject& data);
extern void sendAck(JsonObject& header, uint32_t corrId, int ack);
extern void checkIncoming();

//===================================================================

void checkAndConnect();
void parseIncoming(byte* data);
void sendHeartbeat();
void doOTA(const char *url, bool https, const char *fingerprint);


extern String deviceId;

#define MSG_PING 1
#define MSG_ACK 2
#define MSG_OTA 98
#define MSG_REBOOT 99


#endif //_BSKP_TRANSCEIVER_H_
