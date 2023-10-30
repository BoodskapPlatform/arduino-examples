#include <ArduinoJson.h>                                                // Include the ArduinoJson library for handling JSON data
#include <Wire.h>                                                       // Include the Wire library for I2C communication
#include <Adafruit_Sensor.h>                                            // Include the Adafruit Sensor library for sensor-related operations
#include <Adafruit_TSL2561_U.h>                                         // Include the Adafruit TSL2561 library for the TSL2561 light sensor

uint32_t lastReport = 0;                                                // Variable to hold the time of the last report
uint32_t Reporting_Interval = 1000 * 15;                                // Set the reporting interval to 15 seconds

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT);  // Initialize the TSL2561 sensor with a unique ID for the Adafruit Sensor API

void setup()
{
  Serial.begin(9600);                                                  // Start the serial communication at 9600 bits per second
  tsl.begin();                                                         // Start the TSL2561 sensor
  tsl.enableAutoRange(true);                                           // Enable auto-gain to switch automatically between 1x and 16x
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);                // Set the integration time for the TSL2561 light sensor to 13MS for fast but low-resolution measurements
  millis();  // Initialize the timer
}

void loop()
{
  sensors_event_t value;                                              // Create a sensor event variable
  tsl.getEvent(&value);                                               // Get a new sensor event from the TSL2561 sensor

  StaticJsonDocument <256> Lightjson;                                 // Create a JSON document with the capacity of 256 bytes
  Lightjson["light"] = value.light;                                     // Add the light value to the JSON document
  String Lightvalue;                                                  // Create a String to hold the JSON data
  serializeJson(Lightjson, Lightvalue);                               // Serialize the JSON document to the String

  if ((millis() - lastReport) >= Reporting_Interval)                 // Check if the reporting interval has passed
  {
    lastReport = millis();                                           // Update the lastReport time to the current time
    Serial.println(Lightvalue);                                      // Print the JSON data to the Serial Monitor
    delay(500);                                                      // 500-millisecond delay
  }
}
