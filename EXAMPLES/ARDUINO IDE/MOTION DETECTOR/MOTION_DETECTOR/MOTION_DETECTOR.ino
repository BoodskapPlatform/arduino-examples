#include <PubSubClient.h >
#include<WiFi.h>
#include <ArduinoJson.h>


#define motion_pin  36                                  // Enter the GPIO pin 


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


String mqttUser = "DEV_" + String(DOMAIN_KEY);
String mqttPassword = API_KEY;
String clientid = "DEV_" + String(DEVICE_ID);

//MQTT Topic
String topic =
"/" + String(DOMAIN_KEY) + "/device/" + String(DEVICE_ID) + "/msgs/" + String(DEVICE_MODEL) + "/" + String(FIRMWARE_VER) + "/" + String(MSG_ID);

WiFiClient espClient;
PubSubClient client(espClient);


uint32_t lastReport=0;
uint32_t Reporting_Interval=1000*15;

void setup()
{
    Serial.begin(9600); 
    pinMode(motion_pin, INPUT);
    WiFi.begin(SSID,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
}
void loop()
{

    int Motion = digitalRead(motion_pin);                             
    StaticJsonDocument <256> motionstate;
    motionstate["motion"]=Motion;
    String jsonstate;
    serializeJson(motionstate,jsonstate);
    Serial.println(jsonstate);

  
    if(WiFi.status()==WL_CONNECTED)
    {
        Serial.println("wifi connected");
        delay(100);      
        if (client.connected()== 1)
        {
            Serial.println("mqtt connected");
            delay(100);

            if((millis()-lastReport)>= Reporting_Interval)
            {
                  client.publish(topic.c_str(), jsonstate.c_str());
                  lastReport = millis();
                  Serial.println("data published to server");
                  delay(2000);
            }
        }
        else
        {

            Serial.println("Client not connected ....");
            client.connect(clientid.c_str(), mqttUser.c_str(), mqttPassword.c_str());
            delay(10000);                                                                    // You can change the Server connection waiting time
        }
    } 

    else
    
    {
       Serial.println("wifi connecting....");
       delay(100);
    }

}
