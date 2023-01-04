#include <Arduino.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>


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


Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT);  /* To assign a unique ID o this sensor for use with the Adafruit Sensor API
                                                                                 so that you can identify this particular sensor in any data logs  for Eg:(12345)        
                                                                                                           OR
                                                                                 we can use without a unique ID and this code will run */

void setup() 
{   
    Serial.begin(9600); 
    tsl.begin();                                                                // The begin api is used To Start the TSL 2561 sensor
    tsl.enableAutoRange(true);                                                  // Auto-gain ... switches automatically between 1x and 16x 
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);                       // sets the integration time for the TSL2561 light sensor  13MS is fast but low resolution 
    WiFi.begin(SSID,PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();   
}

void loop() 
{
    sensors_event_t value;                                                      //  Get a new sensor event  
    tsl.getEvent(&value);
    Serial.println(value.light);
    
  
    StaticJsonDocument <256> Lightjson;
    Lightjson["lux"]= value.light;
    String Lightvalue;
    serializeJson(Lightjson,Lightvalue);
    Serial.print(value.light);
    Serial.println(" lux");

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
                  client.publish(topic.c_str(), Lightvalue.c_str());
                  lastReport = millis();
                  Serial.println(Lightvalue);
                  Serial.println("data published to server");
                  delay(500);
            }
        }
         else
        {

            Serial.println("Client not connected ....");
            client.connect(clientid.c_str(), mqttUser.c_str(), mqttPassword.c_str());
            delay(2500);                                                                    // You can change the Server connection waiting time
        }
    } 
     else
    
    {
       Serial.println("wifi connecting....");
       delay(100);
    }


}