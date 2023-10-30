#include "Adafruit_VL53L0X.h"                    // include header file of sensor library           
#include <ArduinoJson.h>
#include <SPI.h>                                 // for communicating with one or more peripheral devices quickly over short distances



uint32_t lastReport = 0;
uint32_t REPORTING_INTERVAL = (8*1000);


Adafruit_VL53L0X lox = Adafruit_VL53L0X();      //we define an object of a structure-function of Adafruit_VL53L0X() Because we can use the same library to read distance measurement data from multiple VL53L0X modules.


void setup() 
{
  Serial.begin(9600);
 
  millis();
  if (!lox.begin()) //condition checks either you made a connection with the sensor correctly or not.
    {
      //Serial.println(F("Failed to boot VL53L0X")); // checks if the module is ready to operate. If not, “Failed to boot VL53L0X” message will display on serial print.
      while(1);
    }
} 

void loop() 
{
        int range ;
        VL53L0X_RangingMeasurementData_t measure;    
        lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
        if (measure.RangeStatus != 4) 
        {  
            delay(500);
            range = measure.RangeMilliMeter;
        } 
        else 
        {
           range = 0;
        }   
        delay(100);
        StaticJsonDocument < 256 > lidardata;
        lidardata["distance"] = range;
        String Jsonvalue;
        serializeJson(lidardata, Jsonvalue);

        if ((millis() - lastReport >= REPORTING_INTERVAL) || (range < 100)&&(range > 0))
        {
                    lastReport = millis();
                    Serial.println(Jsonvalue);
                    delay(2000);
        }   
}  

        
