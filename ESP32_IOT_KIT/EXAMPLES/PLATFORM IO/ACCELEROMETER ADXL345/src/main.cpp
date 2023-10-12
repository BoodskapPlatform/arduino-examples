#include <Arduino.h>
#include <PubSubClient.h >
#include <Wire.h>                                  // To begin Serial comunication
#include <WiFi.h>
#include <ArduinoJson.h>



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


int adxl345 = 0x53;                                 // The ADXL345 sensor I2C address
float X_out, Y_out, Z_out;                          // Outputs
signed int X,Y,Z;

void setup()
{     
      Serial.begin(9600);                         
      Wire.begin();                                 // Initiate the Wire library
      Wire.beginTransmission(adxl345);              // Start communicating with the device 
      Wire.write(0x2D);
      Wire.write(8);                                // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
      Wire.endTransmission();
      WiFi.begin(SSID, PASSWORD);
      client.setServer(MQTT_SERVER, MQTT_PORT);
      millis();     

}
void loop ()
{      

      Wire.beginTransmission(adxl345);
      Wire.write(0x32);                            // Start with register 0x32 (ACCEL_XOUT_H)
      Wire.endTransmission(false);
      Wire.requestFrom(adxl345, 6, 1);             // Read 6 registers total, each axis value is stored in 2 registers,  and  "1" is considered as boolean value (True)
       
      X_out = ( Wire.read()| Wire.read() << 8);    // X-axis value
      X_out = (X_out/256)*100;                     // For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
      Y_out = ( Wire.read()| Wire.read() << 8);    // Y-axis value
      Y_out = (Y_out/256)*100;
      Z_out = ( Wire.read()| Wire.read() << 8);    // Z-axis value
      Z_out = (Z_out/256)*100;

      X = X_out;
      Y = Y_out;
      Z = Z_out;                                   
      /* 
      Serial.print("X: ");                         // if you want to print the  three axis value = X, Y, Z  you can use this commanted codes
      Serial.println(X);
      Serial.print('\n');              
      Serial.print("Y: "); 
      Serial.println(Y);
      Serial.print('\n');
      Serial.print("Z: ");
      Serial.println(Z);
      Serial.print('\n');
      delay(200); */

      String Position;
      String posture_data;

      if((X > 10 && X < 20) && (Y > 90 && Y < 100 ) && ( Z > 1000 && Z < 25600))            // The patient position is considered as sitting or standing  
     
      {     
           
            Position="Sitting";
            delay(500);
      }

      else if((X > 0 && X < 10) && (Y > 1000 && Y < 25600 ) && ( Z > 1000 && Z < 25600))    // The patient position is considered as Lying dowe the  face is towards the ceiling
     
      {     
            
            Position="LYING DOWN";
            delay(500);
      }
      
      else if((X > 4 && X < 18) && (Y > 1000 && Y < 25600 ) && ( Z > 89 && Z < 97))         // The patient position is considered as Lying dowe the face or face towards to bed 
      
      {     
            
            Position="LYING FACE DOWN";
            delay(500);
      }

      else if((X > 1000 && X < 25600) && (Y > 9 && Y < 13 ) && ( Z > 1000 && Z < 25600))    // The patient position is considered as fall to the Right side 
        
      {     
          
            Position="FALL TO RIGHT";
            delay(500);
      }
      
      else if((X > 100 && X < 110) && (Y > 1000 && Y < 25600 ) && ( Z > 1000 && Z < 25600)) // The patient position is considered as fall to the Left side 
      
      {     
           
            Position="FALL TO LEFT";
            delay(500);
      }

      StaticJsonDocument <256> position_json;
      position_json["posture"]=Position;
      serializeJson(position_json, posture_data);
      Serial.println(Position);
      Serial.print('\n');

      if(WiFi.status()==WL_CONNECTED)
      {
            Serial.println("wifi connected");
            Serial.print('\n');
            delay(100);      
         if (client.connected()== 1)
           {
                  Serial.println("MQTT CONNECTED");
                  Serial.print('\n');
                  delay(100);
           
                  if((millis()-lastReport)>= Reporting_Interval)                                   // every 15 sec data pushed to platform . 
                  {                                                                               
                        client.publish(topic.c_str(), posture_data.c_str());
                        lastReport = millis();
                        Serial.println("data published to server");
                        Serial.println(posture_data);
                        delay(2000);
                  } 
           }   
         else
            {
                  Serial.println("Client not connected ....");
                  client.connect(clientid.c_str());
                  delay(5000);                                                                   // You can change the Server connection waiting time
            }
      } 
     else
     {
       Serial.println("wifi connecting....");
       delay(100);
     } 
}