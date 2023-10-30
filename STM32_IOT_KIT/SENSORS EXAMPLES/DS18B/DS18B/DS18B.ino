#include <ArduinoJson.h>                                  // Include the ArduinoJson library for working with JSON data
#include <OneWire.h>                                      // Include the OneWire library for communication with 1-wire devices
#include <DallasTemperature.h>                            // Include the DallasTemperature library for interfacing with DS18B20 temperature sensors

#define SENSOR_PIN PB4                                    // Define the digital pin where the DS18B20 temperature sensor is connected

uint32_t lastReport = 0;                                  // Initialize a variable to keep track of the last time a temperature reading was reported
uint32_t REPORTING_INTERVAL = (8 * 1000);                 // Set the reporting interval to 8 seconds (8,000 milliseconds)

OneWire oneWire(SENSOR_PIN);                              // Setup a OneWire instance with the specified pin
DallasTemperature tempSensor(&oneWire);                   // Initialize the DallasTemperature library with the OneWire instance

float tempCelsius;                                        // Declare a variable to store the temperature in Celsius
float tempFahrenheit;                                     // Declare a variable to store the temperature in Fahrenheit

void setup()
{
  Serial.begin(9600);                                     // Initialize serial communication at a baud rate of 9600 for sending messages to the serial monitor
  tempSensor.begin();                                     // Initialize communication with the DS18B20 sensor
  millis();                                               // Initialize the millisecond counter (not needed here)
}

void loop()
{
  tempSensor.requestTemperatures();                       // Send the command to the DS18B20 sensor to get temperature readings
  tempCelsius = tempSensor.getTempCByIndex(0);            // Read the temperature in Celsius from the sensor
  tempFahrenheit = tempCelsius * 9 / 5 + 32;              // Convert the temperature from Celsius to Fahrenheit

  delay(500);                                             // Introduce a 500-millisecond (0.5-second) delay before the next iteration

  StaticJsonDocument<256> temperatureData;                // Create a JSON document with a capacity of 256 bytes
  temperatureData["temperature"] = tempCelsius;           // Store the temperature in Celsius in the JSON document
  // temperatureData["f"] = tempFahrenheit;               // Uncomment this line if you want to store the temperature in Fahrenheit
  String JsonValue;                                       // Declare a string variable to store the JSON data as a string
  serializeJson(temperatureData, JsonValue);              // Serialize the JSON document into a string

  if (millis() - lastReport >= REPORTING_INTERVAL)        // Check if the time elapsed since the last report is greater than or equal to the reporting interval
  {
    lastReport = millis();                                // Update the lastReport variable with the current time
    Serial.println(JsonValue);                            // Print the JSON temperature data to the serial monitor
    delay(2000);                                          // Introduce a 2-second delay before the next reading is taken
  }
}
