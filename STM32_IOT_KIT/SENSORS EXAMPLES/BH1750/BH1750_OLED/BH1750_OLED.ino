#include <hp_BH1750.h>        // Include the library for the BH1750 light sensor.
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int i = 0;                     // Initialize an integer variable 'i'.
int fontsize = 1;              // Initialize an integer variable 'fontsize'.

/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
hp_BH1750 BH1750;
/***********************************************************************************************/


uint32_t lastReport = 0;                          // Initialize a variable to keep track of the last reporting time.
uint32_t REPORTING_INTERVAL = (15 * 1000);        // Set the reporting interval to 15 seconds in milliseconds.

void setup() {
  Serial.begin(9600);                              // Start serial communication at 9600 baud.

  oledInit();                                     // Initialize the OLED display.

  bool avail = BH1750.begin(BH1750_TO_GROUND);    // Initialize the BH1750 sensor with the address pin connected to ground.
  if (!avail)                                     // The "avail" variable will be "true" if the sensor is found, "false" otherwise.
  {
    Serial.println("No BH1750 sensor found!");     // If the sensor is not found, print an error message and enter an infinite loop.

    while (true) {};
  }
}

void loop() {
  display.clearDisplay();             // Clear the OLED display.
  oledDisplayHeaderShow("BH-Data");   // Display a header on the OLED screen.

  BH1750.start();                     // Start a measurement with the BH1750 sensor.
  float lux = BH1750.getLux();        // Wait until a conversion is finished, and then read the lux value from the sensor.

  oledScreenData(2, 0, 30, String(lux));        // Display the lux value on the OLED screen.
  oledScreenData(2, 90, 30, String("Lux"));

  StaticJsonDocument<256> lightdata;            // Create a JSON document to store the light data.
  lightdata["light"] = lux;                     // Store the lux value in the JSON document.
  String Jsonvalue;                             // Create a String variable to hold the JSON data.
  serializeJson(lightdata, Jsonvalue);          // Serialize the JSON document to a String.

  if ((millis() - lastReport >= REPORTING_INTERVAL))      // Check if it's time to report the data based on the reporting interval.

  {
    lastReport = millis();                     // Update the last reporting time.
    Serial.println(Jsonvalue);                 // Print the JSON data to the serial monitor.
    delay(2000);                               // Delay for 2 seconds before the next report.
  }
  delay(500);                                   // Add a short delay to control the loop frequency.
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
