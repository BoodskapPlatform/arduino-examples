#include <PubSubClient.h >
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>                           // Adafruit sensor library by Adafruit
#include <DHT.h>                                       // DHT sensor library by Adafrui

#define DHT_PIN         13                             // Enter the DHT pin 
#define DHT_TYPE        DHT22

/********************************************************************************************************/

#define MQTT_SERVER    "your MQTT server url"                        // Enter Your MQTT Server
#define MQTT_PORT       1883                                         // Enter Your MQTT PORT     

#define SSID           " your wifi ssid "                            // Enter Your WIFI Name
#define PASSWORD       " your wifi password"                         // Enter Your WIFI Password

#define MSG_ID          1234                                         // Enter Your Message ID


#define DEVICE_TOKEN    "your boodskap platform device token"        // Enter Your Boodskap Platform token

String clientid = DEVICE_TOKEN;                                      // Enter your Token
String topic = "/"+String(DEVICE_TOKEN)+"/pub/"+String(MSG_ID);      // topic = "/YOUR_DEVICE_TOKEN/pub/YOUR MESSSAGE ID"


/************************************************************************************************************/

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t lastReport=0;
uint32_t Reporting_Interval=1000*15;

DHT dht(DHT_PIN,DHT_TYPE);

void setup()
{
    Serial.begin(9600); 
    dht.begin();
    WiFi.begin(SSID,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();
}
void loop()
{  
    float T_data = dht.readTemperature();
    float H_data = dht.readHumidity();

    if (isnan(H_data) || isnan(T_data) ) 
     {
        Serial.println(F("Kindly connect your DHT11 sensor "));
        return;
     }                                                                                                                         
    StaticJsonDocument <256> DHT22json;
    DHT22json["temperature"]= T_data ;
    DHT22json["humidity"]= H_data;
    String DHT22data;
    serializeJson(DHT22json,DHT22data);
    Serial.print("TEMP :");
    Serial.print(T_data);
    Serial.print('\t');
    Serial.print("HUMI :");
    Serial.println(H_data);

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
                  client.publish(topic.c_str(), DHT22data.c_str());
                  lastReport = millis();
                  Serial.println(DHT22data);
                  Serial.println("data published to server");
                  delay(2000);
            }
        }
         else
        {

            Serial.println("Client not connected ....");
            client.connect(clientid.c_str());
            delay(5000);                                                                    // You can change the Server connection waiting time
        }
    } 
     else
    
    {
       Serial.println("wifi connecting....");
       delay(100);
    }

}
