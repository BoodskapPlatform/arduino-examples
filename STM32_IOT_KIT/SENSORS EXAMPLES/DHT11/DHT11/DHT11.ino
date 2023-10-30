#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>                           // Adafruit sensor library by Adafruit
#include <DHT.h>                                       // DHT sensor library by Adafruit

#define DHT_PIN          PC13                          // Enter the DHT pin
#define DHT_TYPE         DHT11

DHT dht(DHT_PIN, DHT_TYPE);                            // Initialize the DHT sensor with the specified pin and type

uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 8;                // Reporting interval in milliseconds (8 seconds)

void setup()
{
  Serial.begin(9600);                                  // Initialize serial communication at 9600 baud
  dht.begin();                                         // Initialize the DHT sensor
  millis();                                            // This call to millis() doesn't do anything; it's not necessary.
}

void loop()
{
  float T_data = dht.readTemperature();  // Read temperature data from the DHT sensor
  float H_data = dht.readHumidity();     // Read humidity data from the DHT sensor

  if (isnan(H_data) || isnan(T_data))
  {
    // Check if the sensor data is invalid (NaN), and if so, return without doing anything.
    return;
  }

  StaticJsonDocument<256> DHT11json;  // Create a JSON document with a capacity of 256 bytes
  DHT11json["temperature"] = T_data;  // Add temperature data to the JSON document
  DHT11json["humidity"] = H_data;     // Add humidity data to the JSON document
  String DHT11data;                   // Create a string to store the serialized JSON

  serializeJson(DHT11json, DHT11data);  // Serialize the JSON document to a string

  if ((millis() - lastReport) >= Reporting_Interval)
  {
    lastReport = millis();        // Update the last report time
    Serial.println(DHT11data);    // Print the JSON data to the serial monitor
    delay(2000);                  // Wait for 2 seconds before the next report
  }
}
