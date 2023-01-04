#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>
 


# define DOMAIN_KEY     "your_domain_key"          // Enter Your Platform Domain Key   
# define API_KEY        "your_api_key"             // Enter Your Platform API key
# define DEVICE_ID      "your_device_id"           // Enter Your Device ID
# define DEVICE_MODEL   "your_device_model"        // Enter Your Device Model
# define FIRMWARE_VER   "V2.2022.2.0"              // Enter Your Firmware Version
# define MSG_ID          123                       // Enter Your Message ID
# define MQTT_SERVER    "your_mqtt_url"            // Enter Your MQTT Server
# define MQTT_PORT       1883                      // Enter Your MQTT PORT     

# define SSID           "your_wifi_ssid"           // Enter Your WIFI Name
# define PASSWORD       "your_wifi_password"       // Enter Your WIFI Password




#define SENSOR_PIN 14

String mqttUser = "DEV_" + String(DOMAIN_KEY);
String mqttPassword = API_KEY;
String clientid = "DEV_" + String(DEVICE_ID);

String topic =
"/" + String(DOMAIN_KEY) + "/device/" + String(DEVICE_ID) + "/msgs/" + String(DEVICE_MODEL) + "/" + String(FIRMWARE_VER) + "/" + String(MSG_ID);

uint32_t lastReport = 0;
uint32_t REPORTING_INTERVAL = (15*1000);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
    Serial.begin (9600);
    pinMode(SENSOR_PIN, INPUT);
    WiFi.begin(SSID ,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
}

void loop() 
{  
  String soundstatus;
  int val = digitalRead(SENSOR_PIN);
  if (val==HIGH) 
  {
    Serial.println("SOUND DETECTED");
    soundstatus ="SOUND DETECTED";
  }
  else 
  {
    
    Serial.println("SOUND NOT DETECTED");
    soundstatus ="SOUND NOT DETECTED";
  }
  StaticJsonDocument < 256 > sounddata;
  sounddata["s"] = soundstatus;
  String Jsonvalue;
  serializeJson(sounddata, Jsonvalue);
   if (WiFi.status() == WL_CONNECTED) 
   {
     Serial.println("WiFi Connected");
     delay(100);
       if (client.connected()== 1)
         {
            Serial.println("mqtt connected");
            delay(100);
             if ((millis() - lastReport >= REPORTING_INTERVAL) || (val==HIGH)  )
                {
                   client.publish(topic.c_str(), Jsonvalue.c_str());
                   lastReport = millis();
                   Serial.println("data published to server");
                   delay(2000);
                }   
         }
        else
         {
            client.connect(clientid.c_str(), mqttUser.c_str(), mqttPassword.c_str());
            delay(6000);
            Serial.println("Client Not Connected");
            delay(10000);                                 // You can change the Server connection waiting time
         }
   }
  
  else
   {
       Serial.println("wifi connecting....");
       delay(100);
   }
}