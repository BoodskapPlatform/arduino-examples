#include "Adafruit_VL53L0X.h"                    // include header file of sensor library           
#include <SPI.h>                                 // for communicating with one or more peripheral devices quickly over short distances
#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>


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

String topic =
"/" + String(DOMAIN_KEY) + "/device/" + String(DEVICE_ID) + "/msgs/" + String(DEVICE_MODEL) + "/" + String(FIRMWARE_VER) + "/" + String(MSG_ID);

uint32_t lastReport = 0;
uint32_t REPORTING_INTERVAL = (15*1000);

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();      //we define an object of a structure-function of Adafruit_VL53L0X() Because we can use the same library to read distance measurement data from multiple VL53L0X modules.


void setup() 
{
  Serial.begin(9600);
  WiFi.begin(SSID ,PASSWORD);
  client.setServer(MQTT_SERVER, MQTT_PORT);
  millis();
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) //condition checks either you made a connection with the sensor correctly or not.
    {
      Serial.println(F("Failed to boot VL53L0X")); // checks if the module is ready to operate. If not, “Failed to boot VL53L0X” message will display on serial print.
      while(1);
    }
    // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
} 

void loop() 
{
        int range ;
        VL53L0X_RangingMeasurementData_t measure;    
        //Serial.print("Reading a measurement... ");
        lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
        Serial.println(measure.RangeStatus);
        if (measure.RangeStatus != 4) 
        {  // phase failures have incorrect data
           //Serial.print("Distance (mm): ");
           // delay(100);
            Serial.println(measure.RangeMilliMeter);
            delay(500);
            range = measure.RangeMilliMeter;
        } 
        else 
        {
           Serial.println(" out of range ");
           range = 0;
        }   
        delay(100);
        StaticJsonDocument < 256 > lidardata;
        lidardata["lidar"] = range;
        String Jsonvalue;
        serializeJson(lidardata, Jsonvalue);
          if (WiFi.status() == WL_CONNECTED) 
            {
              Serial.println("WiFi Connected");
              delay(100);
             if (client.connected()== 1)
               {
                 Serial.println("mqtt connected");
                 delay(100);
                if ((millis() - lastReport >= REPORTING_INTERVAL) || (range < 100))
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

        
