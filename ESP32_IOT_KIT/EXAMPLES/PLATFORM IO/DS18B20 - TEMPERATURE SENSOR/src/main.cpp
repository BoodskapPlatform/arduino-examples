#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <PubSubClient.h >
#include <ArduinoJson.h>

#define SENSOR_PIN  13


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

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library

float tempCelsius;    // temperature in Celsius
float tempFahrenheit; // temperature in Fahrenheit

void setup()
{
  Serial.begin(9600); // initialize serial
  tempSensor.begin();    // initialize the sensor
  WiFi.begin(SSID ,PASSWORD);
  client.setServer(MQTT_SERVER, MQTT_PORT);
  millis();
}
void loop()
{ 
  
  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  tempFahrenheit = tempCelsius * 9 / 5 + 32; // convert Celsius to Fahrenheit

  Serial.print("Temperature: ");
  Serial.print(tempCelsius);    // print the temperature in Celsius
  Serial.print("°C");
  Serial.print("  ~  ");        // separator between Celsius and Fahrenheit
  Serial.print(tempFahrenheit); // print the temperature in Fahrenheit
  Serial.println("°F");

  delay(500);
  StaticJsonDocument < 256 > tempraturedata;
  tempraturedata["c"] = tempCelsius;
  tempraturedata["f"] = tempFahrenheit;
  String Jsonvalue;
  serializeJson(tempraturedata, Jsonvalue);
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