#include <ArduinoJson.h>                                /* include the ArduinoJson library which allows easy handling of JSON data */
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define motion_pin  PB5                                 // Enter the GPIO pin for the motion sensor

uint32_t lastReport = 0;                                // Variable to hold the time of the last report
uint32_t Reporting_Interval = 1000 * 15;                // Set the reporting interval to 15 seconds

/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***************************************************************************************************************************************/

void setup()
{
  oledInit();                                           // Initialize the OLED display.
  Serial.begin(9600);                                   // Start the serial communication at 9600 bits per second
  pinMode(motion_pin, INPUT);                           // Set the pin mode of the motion sensor pin as input
  millis();                                             // Initialize the timer
}

void loop()
{
  
    int Motion = digitalRead(motion_pin);                 // Read the state of the motion sensor

    display.clearDisplay();             // Clear the OLED display.
    oledDisplayHeaderShow("info");   // Display a header on the OLED screen.
    oledScreenData(2, 0, 30, String("Motion"));        // Display the lux value on the OLED screen.
  
    StaticJsonDocument <256> motionstate;                 // Create a JSON document with the capacity of 256 bytes
    motionstate["motion"] = Motion;                       // Add the motion state to the JSON document
    String jsonstate;                                     // Create a String to hold the JSON data
    serializeJson(motionstate, jsonstate);                // Serialize the JSON document to the String
    
    if ( ((millis() - lastReport) >= Reporting_Interval) || (Motion == 1) )
    {
      oledScreenData(2, 0, 50, String("detected!"));
      Serial.println(jsonstate);                          // Print the JSON data to the Serial Monitor
      lastReport = millis();                              // Update the lastReport time to the current time
      delay(2000);                                        // 2-second delay
    }
    if(Motion == 0)
    {
          oledScreenData(2, 0, 50, String("stopped!"));
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
