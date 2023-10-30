#include <ArduinoJson.h>                                  // Include the ArduinoJson library for working with JSON data
#include <OneWire.h>                                      // Include the OneWire library for communication with 1-wire devices
#include <DallasTemperature.h>                            // Include the DallasTemperature library for interfacing with DS18B20 temperature sensors

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SENSOR_PIN PB4                                    // Define the digital pin where the DS18B20 temperature sensor is connected

uint32_t lastReport = 0;                                  // Initialize a variable to keep track of the last time a temperature reading was reported
uint32_t REPORTING_INTERVAL = (8 * 1000);                 // Set the reporting interval to 8 seconds (8,000 milliseconds)

OneWire oneWire(SENSOR_PIN);                              // Setup a OneWire instance with the specified pin
DallasTemperature tempSensor(&oneWire);                   // Initialize the DallasTemperature library with the OneWire instance

float tempCelsius;                                        // Declare a variable to store the temperature in Celsius
float tempFahrenheit;                                     // Declare a variable to store the temperature in Fahrenheit

/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***********************************************************************************************/

void setup()
{
  
  oledInit();                                             // Initialize the OLED display.
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
  
  display.clearDisplay();                                 // Clear the OLED display.
  oledDisplayHeaderShow("DS-Data");                       // Display a header on the OLED screen.
  oledScreenData(2, 0, 30, String(tempCelsius));          // Display the lux value on the OLED screen.
  oledScreenData(2, 90, 30, String("*C"));

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

void oledInit()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);    // Initialize the OLED display with specified settings.
  display.clearDisplay();                       // Clear the display.
  delay(2000);                                  // Wait for 2 seconds.
  display.clearDisplay();                       // Clear the display again.
  display.invertDisplay(false);                 // Set display inversion to false (normal mode).
}

void oledDisplayHeaderShow(String Header_Data)
{
  display.setTextSize(2);                      // Set the text size.
  display.setTextColor(WHITE);                 // Set the text color to white.
  display.setCursor(0, 0);                     // Set the cursor position.
  display.print(Header_Data);                  // Print the provided header text.
  display.display();                           // Display the text on the OLED screen.
}

void oledScreenData(int size, int x, int y, String get_screen_data)
{
  display.setTextSize(size);                    // Set the text size.
  display.setTextColor(WHITE);                   // Set the text color to white.
  display.setCursor(x, y);                       // Set the cursor position.
  display.print(get_screen_data);                // Print the provided screen data.
  display.display();                             // Display the data on the OLED screen.
}
