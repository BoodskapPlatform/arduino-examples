#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "MQTT Server"                  /* Enter Your MQTT Server */
#define MQTT_PORT 1883                             /* Enter Your MQTT PORT */

const char* ssid = "Testing";                      /* Enter Your WiFi username */
const char* password = "12345678";                 /* Enter Your WiFi password */

#define DEVICE_TOKEN "token"                       /* Enter Your Boodskap Platform token */

#define MSG_ID 10000                               /* Enter Your Message ID*/

#define WIFI_INTERNET_LED 2

String clientid = String(DEVICE_TOKEN);            /* Enter your Token */

// MQTT Topic
String topic = "/" + String(DEVICE_TOKEN) + "/pub/" + String(MSG_ID);   /* topic = "/YOUR_DEVICE_TOKEN/pub/YOUR MESSSAGE ID"*/

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 15;

void setup()
{
    Serial.begin(9600);
    WiFi.begin(ssid, password);                     /* Initialize and connect to Wi-Fi network*/
    pinMode(WIFI_INTERNET_LED, OUTPUT);             /* Set the WiFi indicator LED pin as an output*/
    client.setServer(MQTT_SERVER, MQTT_PORT);       /* Set the MQTT server and port*/
}

void loop()
{
    String senddata;
    if (Serial.available() > 0)                             /* Check if there is data available on the Serial port*/
    {
        senddata = Serial.readString();                     /* Read the data from the Serial port*/
        Serial.println(senddata);
        if (client.connected() == 1)                        /* Check if the MQTT client is connected*/
        {
          digitalWrite(WIFI_INTERNET_LED, HIGH);             /* Turn on the WiFi indicator LED*/
          delay(100);                                       /* Delay for 0.1 seconds*/
          client.publish(topic.c_str(), senddata.c_str());  /* Publish the data to the MQTT server*/
          digitalWrite(WIFI_INTERNET_LED, LOW);             /* Turn oFF the WiFi indicator LED*/
        }
    }
    
    delay(10);
  
    if (WiFi.status() == WL_CONNECTED)              /* Check if the Wi-Fi is connected*/
    {
        digitalWrite(WIFI_INTERNET_LED, LOW);         /* Turn ON the WiFi indicator LED*/
        if (client.connected() == 1)                  /* Check if the MQTT client is connected*/
        {
            delay(100);
        }
        else
        {
            client.connect(clientid.c_str());                 /* Connect the MQTT client to the server*/
            uint8_t i=0;
            while(i<10)
            {
                digitalWrite(WIFI_INTERNET_LED, HIGH);        /* Turn on the WiFi indicator LED*/
                delay(500);                                   /* Delay for 0.5 seconds*/
                digitalWrite(WIFI_INTERNET_LED, LOW);         /* Turn off the WiFi indicator LED*/
                delay(500);                                   /* Delay for 0.5 seconds*/
                i++;
            }
        }
    }
    else
    {
        digitalWrite(WIFI_INTERNET_LED, HIGH);        /* Turn on the WiFi indicator LED*/
        delay(100);                                   /* Delay for 0.1 seconds*/
        digitalWrite(WIFI_INTERNET_LED, LOW);         /* Turn off the WiFi indicator LED*/
        delay(100);                                   /* Delay for 0.1 seconds*/
    }
}
