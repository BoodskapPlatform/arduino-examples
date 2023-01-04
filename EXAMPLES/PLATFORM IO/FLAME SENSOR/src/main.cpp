#include <Arduino.h>
#include <PubSubClient.h >
#include<WiFi.h>
#include <ArduinoJson.h>

#define flame_pin 34                               // Enter the GPIO pin 


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
    pinMode(flame_pin, INPUT);
    WiFi.begin(SSID,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
}
void loop()
{
    String flamestatus;

    int Fire = analogRead(flame_pin);

    if (Fire < 2500) 
    {
        Serial.println("FIRE DETECTED");
        flamestatus ="FIRE DETECTED";
    }  
    else
    {
        Serial.println("FIRE NOT DETECTED");
        flamestatus ="FIRE NOT DETECTED";
    }              
                                                
    StaticJsonDocument <256> flamejson;
    flamejson["flame"]= flamestatus;
    String flamedata;
    serializeJson(flamejson,flamedata);
    Serial.println(flamestatus);

    if(WiFi.status()==WL_CONNECTED)
    {
          Serial.println("wifi connected");
          delay(100);      
        if (client.connected()== 1)
        {
            Serial.println(" MQTT CONNECTED");
            delay(100);

           if(((millis()-lastReport)>= Reporting_Interval) || (Fire < 2500))              // every 15 sec data pushed to platform . 
            {                                                                             // if fire detected immedietly data send to platform
                  client.publish(topic.c_str(), flamedata.c_str());
                  lastReport = millis();
                  Serial.println("data published to server");
                  Serial.println(flamedata);
                  delay(2000);
            }
        }
         else
        {
            Serial.println("Client not connected ....");
            client.connect(clientid.c_str(), mqttUser.c_str(), mqttPassword.c_str());
            delay(10000);                                                                  // You can change the Server connection waiting time
        }
    } 
     else
    {
       Serial.println("wifi connecting....");
       delay(100);
    }

}
