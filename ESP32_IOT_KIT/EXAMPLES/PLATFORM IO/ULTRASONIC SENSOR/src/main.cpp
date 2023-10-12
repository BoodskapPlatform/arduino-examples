#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>
 
            


#define trig_Pin  5
#define echo_Pin  18
#define SOUND_SPEED 0.034    


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
            Serial.println("Client not connected ....");
            client.connect(clientid.c_str());    
            delay(10000);                                 // You can change the Server connection waiting time
         }
   }
  
  else
   {
       Serial.println("wifi connecting....");
       delay(100);
   }
}