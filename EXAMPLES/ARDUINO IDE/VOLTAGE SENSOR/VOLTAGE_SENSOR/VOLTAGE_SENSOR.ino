#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>
 

#define voltagepin        34


# define DOMAIN_KEY     " your domain key "             // Enter Your Platform Domain Key   
# define API_KEY        " your api key  "               // Enter Your Platform API key
# define DEVICE_ID      " your device id  "             // Enter Your Device ID
# define DEVICE_MODEL   "ESP32"                         // Enter Your Device Model
# define FIRMWARE_VER   "V2.2022.2.0"                   // Enter Your Firmware Version
# define MSG_ID          1234                           // Enter Your Message ID
# define MQTT_SERVER    "your MQTT server url"          // Enter Your MQTT Server
# define MQTT_PORT       1883                           // Enter Your MQTT PORT     

# define SSID           " your wifi ssid "              // Enter Your WIFI Name
# define PASSWORD       " your wifi password"           // Enter Your WIFI Password



float vout = 0.0;
float R1   = 30000.0;
float R2   = 7500.0;
float vin  = 0.0;

String mqttUser = "DEV_" + String(DOMAIN_KEY);
String mqttPassword = API_KEY;
String clientid = "DEV_" + String(DEVICE_ID);

String topic =
"/" + String(DOMAIN_KEY) + "/device/" + String(DEVICE_ID) + "/msgs/" + String(DEVICE_MODEL) + "/" + String(FIRMWARE_VER) + "/" + String(MSG_ID);

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
            client.connect(clientid.c_str(), mqttUser.c_str(), mqttPassword.c_str());
            delay(6000);
            Serial.println("Client failed ....");
            delay(100);
         }
   }
  
  else
   {
       Serial.println("wifi connecting....");
       delay(100);
   }
 }  
