//#write your ble client code in this file . all the received data must send via Serialport2

#include <Arduino.h>
#include "ArduinoJson.h"

void dataCollector();

void setup() 
{
    Serial.begin(9600);
    Serial2.begin(9600);

}

void loop() 
{
    dataCollector();
    delay(5000);
}

void dataCollector()
{
       StaticJsonDocument<256> sensor_data;
       sensor_data["skintemp"] = 30; //field integer
       String Send_data_json;
       serializeJson(sensor_data, Send_data_json);
       Serial.println(Send_data_json);
       Serial2.println(Send_data_json);
}

