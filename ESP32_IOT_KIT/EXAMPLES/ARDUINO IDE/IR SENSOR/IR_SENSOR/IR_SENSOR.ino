#include <PubSubClient.h >
#include<WiFi.h>
#include <ArduinoJson.h>


# define IR_PIN          33                        // Enter the GPIO pin



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
    pinMode(IR_PIN, INPUT);
    WiFi.begin(SSID, PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    millis();    
}
void loop() 
{  
   String IR_status;

   int IR_value = digitalRead(IR_PIN);


   if ((IR_value) == 0 )               // if the value is 0 object detect // if the value is 1 NO object
   {
      Serial.println("object detected");
      IR_status ="Object Detected";
   }
   else
   {
      Serial.println("no object");
      IR_status = "No Object";
   }

   StaticJsonDocument <256> IR_json;
   IR_json["ir"]=IR_status;
   String IR_data;
   serializeJson(IR_json, IR_data);
   Serial.println(IR_status);
  
   if(WiFi.status()==WL_CONNECTED)
    {
          Serial.println("wifi connected");
          delay(100);      
        if (client.connected()== 1)
        {
            Serial.println(" MQTT CONNECTED");
            delay(100);

           if(((millis()-lastReport)>= Reporting_Interval) || (IR_value == 0))              // every 15 sec data pushed to platform . 
            {                                                                               // if object detected immedietly data send to platform
                  client.publish(topic.c_str(), IR_data.c_str());
                  lastReport = millis();
                  Serial.println("data published to server");
                  Serial.println(IR_data);
                  delay(2000);
            }
        }
         else
        {
            Serial.println("Client not connected ....");
            client.connect(clientid.c_str());
            delay(10000);                                                                   // You can change the Server connection waiting time
        }
    } 
     else
    {
       Serial.println("wifi connecting....");
       delay(100);
    }

}
