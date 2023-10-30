#include<Wire.h>
#include <ArduinoJson.h>                                                // Include the ArduinoJson library for handling JSON data

 
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;

uint32_t lastReport = 0;                                                // Variable to hold the time of the last report
uint32_t Reporting_Interval = 1000 * 15;                                // Set the reporting interval to 15 seconds

void setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(9600);
    delay(3000);
}
void loop()
{
      Wire.beginTransmission(MPU_addr);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU_addr,14,true);
      
      AcX=Wire.read()<<8|Wire.read();
      AcY=Wire.read()<<8|Wire.read();
      AcZ=Wire.read()<<8|Wire.read();
      
      int xAng = map(AcX,minVal,maxVal,-90,90);
      int yAng = map(AcY,minVal,maxVal,-90,90);
      int zAng = map(AcZ,minVal,maxVal,-90,90);
      
      x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
      y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
      z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

      StaticJsonDocument <256> posjson;                                 // Create a JSON document with the capacity of 256 bytes
      posjson["pos"] = "x:"+String(x)+",y="+String(y)+",z="+String(z);                                     // Add the light value to the JSON document
      String posvalue;                                                  // Create a String to hold the JSON data
      serializeJson(posjson, posvalue);                               // Serialize the JSON document to the String
  
      if ((millis() - lastReport) >= Reporting_Interval)                 // Check if the reporting interval has passed
      {
        lastReport = millis();                                           // Update the lastReport time to the current time
        Serial.println(posvalue);                                      // Print the JSON data to the Serial Monitor
        delay(500);                                                      // 500-millisecond delay
      }

      delay(1000);
}
