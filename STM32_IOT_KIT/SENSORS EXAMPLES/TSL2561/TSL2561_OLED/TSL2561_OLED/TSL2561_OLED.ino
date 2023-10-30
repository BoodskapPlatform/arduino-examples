#include <ArduinoJson.h>                                                // Include the ArduinoJson library for handling JSON data
#include <Wire.h>                                                       // Include the Wire library for I2C communication
#include <Adafruit_Sensor.h>                                            // Include the Adafruit Sensor library for sensor-related operations
#include <Adafruit_TSL2561_U.h>                                         // Include the Adafruit TSL2561 library for the TSL2561 light sensor


#include <Adafruit_GFX.h>                                               // oled gfx library
#include <Adafruit_SSD1306.h>


uint32_t lastReport = 0;                                                // Variable to hold the time of the last report
uint32_t Reporting_Interval = 1000 * 15;                                // Set the reporting interval to 15 seconds

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT);  // Initialize the TSL2561 sensor with a unique ID for the Adafruit Sensor API

/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***************************************************************************************************************************************/

void setup()
{
    Serial.begin(9600);                                                  // Start the serial communication at 9600 bits per second
    tsl.begin();                                                         // Start the TSL2561 sensor
    tsl.enableAutoRange(true);                                           // Enable auto-gain to switch automatically between 1x and 16x
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);                // Set the integration time for the TSL2561 light sensor to 13MS for fast but low-resolution measurements
    millis();  // Initialize the timer
    oledInit();                                                          // Initialize the OLED display.
}

void loop()
{

    display.clearDisplay();                                             // Clear the OLED display.
    oledDisplayHeaderShow("TSL-Data");                                  // Display a header on the OLED screen.
   
    sensors_event_t value;                                              // Create a sensor event variable
    tsl.getEvent(&value);                                               // Get a new sensor event from the TSL2561 sensor
  
    oledScreenData(2, 0, 30, String(value.light));                      // Display the lux value on the OLED screen.
    oledScreenData(2, 90, 30, String("Lux"));
    
    StaticJsonDocument <256> Lightjson;                                 // Create a JSON document with the capacity of 256 bytes
    Lightjson["light"] = value.light;                                   // Add the light value to the JSON document
    String Lightvalue;                                                  // Create a String to hold the JSON data
    serializeJson(Lightjson, Lightvalue);                               // Serialize the JSON document to the String
  
    if ((millis() - lastReport) >= Reporting_Interval)                  // Check if the reporting interval has passed
    {
      lastReport = millis();                                            // Update the lastReport time to the current time
      Serial.println(Lightvalue);                                       // Print the JSON data to the Serial Monitor
      delay(500);                                                       // 500-millisecond delay
    }
    delay(500);
  
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
