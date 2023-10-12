#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>
 

#define voltagepin        34


/********************************************************************************************************/
#define MQTT_SERVER     "your MQTT server url"                       // Enter Your MQTT Server
#define MQTT_PORT       1883                                         // Enter Your MQTT PORT     
#define SSID            "your wifi ssid "                            // Enter Your WIFI Name
#define PASSWORD        "your wifi password"                         // Enter Your WIFI Password
#define MSG_ID          1234                                         // Enter Your Message ID
#define DEVICE_TOKEN    "your boodskap platform device token"        // Enter Your Boodskap Platform token

String clientid = DEVICE_TOKEN;                                      // Enter your Token
String topic = "/"+String(DEVICE_TOKEN)+"/pub/"+String(MSG_ID);      // topic = "/YOUR_DEVICE_TOKEN/pub/YOUR MESSSAGE ID"

/************************************************************************************************************/



float vout = 0.0;
float R1   = 30000.0;
float R2   = 7500.0;
float vin  = 0.0;


uint32_t REPORTING_INTERVAL = (15*1000);
uint32_t lastReport = 0;


WiFiClient espClient;
PubSubClient client(espClient);



void setup() 
{
    Serial.begin(9600); 
    WiFi.begin(WIFI_SSID ,WIFI_PSK);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
  
}

void loop() 
{ 
  int value = analogRead(voltagepin);
  vout = (value * 3.3) / 4096.0; 
  vin = vout / (R2/(R1+R2));
  StaticJsonDocument < 256 > voltagedata;
  voltagedata["volt"] = vin ;
  String Jsonvalue;
  serializeJson(voltagedata, Jsonvalue);
   if (WiFi.status() == WL_CONNECTED) 
   {
     Serial.println("WiFi Connected");
     delay(100);
       if (client.connected()== 1)
         {
            Serial.println("mqtt connected");
            delay(100);
             if (millis() - lastReport >= REPORTING_INTERVAL)
                {
                   client.publish(topic.c_str(), Jsonvalue.c_str());
                   lastReport = millis();
                }   
         }
        else
         {
                  Serial.println("Client not connected ....");
                  client.connect(clientid.c_str());
                  delay(5000);         
         }
   }
  
  else
   {
       Serial.println("wifi connecting....");
       delay(100);
   }
 }  
