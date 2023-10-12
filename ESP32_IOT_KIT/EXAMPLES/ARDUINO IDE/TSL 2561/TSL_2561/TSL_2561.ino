#include <PubSubClient.h >
#include <ArduinoJson.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>



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
            client.connect(clientid.c_str());
            delay(2500);                                                                    // You can change the Server connection waiting time
        }
    } 
     else
    
    {
       Serial.println("wifi connecting....");
       delay(100);
    }


}
