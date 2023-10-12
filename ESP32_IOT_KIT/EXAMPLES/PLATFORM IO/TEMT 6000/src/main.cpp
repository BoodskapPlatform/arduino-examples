#include <Arduino.h>
#include <PubSubClient.h >
#include<WiFi.h>
#include <ArduinoJson.h>

#define light_pin 32                               // Enter the GPIO pin 



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

WiFiClient espClient;
PubSubClient client(espClient);


uint32_t lastReport=0;
uint32_t Reporting_Interval=1000*15;


void setup()
{
    Serial.begin(9600); 
    pinMode(light_pin, INPUT);
    WiFi.begin(SSID,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
}
void loop()
{

    float Light = analogRead(light_pin) *3.3 / 4096;  //  Read the volts from the temt 6000 
    float Amps  = Light/10000;                        // across 10,000 Ohms 10K ONBOARD RESISTANCE ON TEMT6000
    float Microamps = Amps*1000000;                   // one ampere (A) is equal to 1,000,000 microamperes (uA).
    float Lux = Microamps*2.0;                        // The datasheet for the TEMT6000 specifies a proportional correlation between current and illuminance   
                                                      //  Every 2 µA of current correlates to 1 lx in the illuminance.
                                                      //  micro amps to lux convertion
    StaticJsonDocument <256> Lightvalue;
    Lightvalue["light"]=Lux;
    String Lightdata;
    serializeJson(Lightvalue,Lightdata);
    Serial.println(Lightdata);

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
                  client.publish(topic.c_str(), Lightdata.c_str());
                  lastReport = millis();
                  Serial.println("data published to server");
                  delay(2000);
            }
        }
         else
        {

            Serial.println("Client not connected ....");
            client.connect(clientid.c_str());
            delay(10000);                                                                    // You can change the Server connection waiting time
        }
    } 
     else
    
    {
       Serial.println("wifi connecting....");
       delay(100);
    }

}