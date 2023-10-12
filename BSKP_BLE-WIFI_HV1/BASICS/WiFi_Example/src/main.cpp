
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "Enter Your MQTT Server" /* Enter Your MQTT Server */
#define MQTT_PORT 1883                       /**/ Enter Your MQTT PORT

#define SSID "Testing"      // Enter Your WIFI Name
#define PASSWORD "12345678" // Enter Your WIFI Password

#define DEVICE_TOKEN "Boodskap Platform token" // Enter Your Boodskap Platform token

#define MSG_ID 10000 // Enter Your Message ID

#define WIFI_LED 19
#define INTERNET_LED 18

String clientid = DEVICE_TOKEN; // Enter your Token

// MQTT Topic
String topic = "/" + String(DEVICE_TOKEN) + "/pub/" + String(MSG_ID); // topic = "/YOUR_DEVICE_TOKEN/pub/YOUR MESSSAGE ID"

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 15;

void setup()
{
    pinMode(WIFI_LED, OUTPUT);
    pinMode(INTERNET_LED, OUTPUT);

    Serial.begin(9600);
    Serial2.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    client.setServer(MQTT_SERVER, MQTT_PORT);
}
void loop()
{
    String senddata;

    if (Serial2.available() > 0)
    {
        senddata = Serial2.readString();
        if (client.connected() == 1)
        {
            client.publish(topic.c_str(), senddata.c_str());
            Serial.println("data published to server");
            Serial.println(senddata);
            delay(2000);
        }
    }

    delay(10);

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("wifi connected");
        if (client.connected() == 1)
        {
            Serial.println(" MQTT CONNECTED");
            digitalWrite(WIFI_LED, HIGH);
            digitalWrite(INTERNET_LED, HIGH);
            delay(100);
        }
        else
        {
            digitalWrite(WIFI_LED, HIGH);
            digitalWrite(INTERNET_LED, LOW);
            Serial.println("Client not connected ....");
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            client.connect(clientid.c_str());
            delay(10000); // You can change the Server connection waiting time
        }
    }
    else
    {
        digitalWrite(WIFI_LED, LOW);
        digitalWrite(INTERNET_LED, LOW);
        Serial.println("wifi connecting....");
        Serial.println("Failed, wc=");
        Serial.println(WiFi.status());
        if (WiFi.status() == WL_DISCONNECTED)
        {
            // WiFi.disconnect();
            WiFi.begin(SSID, PASSWORD);
        }
        delay(1000);
    }
}
