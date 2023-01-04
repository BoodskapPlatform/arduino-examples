#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>

#define trig_Pin       5
#define echo_Pin       18
#define SOUND_SPEED    0.034   


# define DOMAIN_KEY     " your domain key "             // Enter Your Platform Domain Key   
# define API_KEY        " your api key  "               // Enter Your Platform API key
# define DEVICE_ID      " your device id  "             // Enter Your Device ID
# define DEVICE_MODEL   "ESP32"                         // Enter Your Device Model
# define FIRMWARE_VER   "V2.2022.2.0"                   // Enter Your Firmware Version
# define MSG_ID         1234                            // Enter Your Message ID
# define MQTT_SERVER    "your MQTT server url"          // Enter Your MQTT Server
# define MQTT_PORT       1883                           // Enter Your MQTT PORT     

# define SSID           " your wifi ssid "              // Enter Your WIFI Name
# define PASSWORD       " your wifi password"           // Enter Your WIFI Password


String mqttUser = "DEV_" + String(DOMAIN_KEY);
String mqttPassword = API_KEY;
String clientid = "DEV_" + String(DEVICE_ID);

String topic =
"/" + String(DOMAIN_KEY) + "/device/" + String(DEVICE_ID) + "/msgs/" + String(DEVICE_MODEL) + "/" + String(FIRMWARE_VER) + "/" + String(MSG_ID);

uint32_t lastReport = 0;
uint32_t REPORTING_INTERVAL = (15*1000);

WiFiClient espClient;
PubSubClient client(espClient);



long duration;
float dist_cm;
      

void setup() 
{
    Serial.begin(9600); 
    pinMode(trig_Pin, OUTPUT); 
    pinMode(echo_Pin, INPUT); 
    WiFi.begin(SSID ,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
}

void loop() 
{ 
  digitalWrite(trig_Pin, LOW); 
  delayMicroseconds(100);
  digitalWrite(trig_Pin, HIGH); 
  delayMicroseconds(100);
  digitalWrite(trig_Pin, LOW);

  duration = pulseIn(echo_Pin, HIGH);
  //Serial.println(duration);
  dist_cm = duration * SOUND_SPEED/2; 
  Serial.println(String(dist_cm)+":cm");
  StaticJsonDocument < 256 > ultrasonicdata;
  ultrasonicdata["distance"] = dist_cm ;
  String Jsonvalue;
  serializeJson(ultrasonicdata, Jsonvalue);
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
