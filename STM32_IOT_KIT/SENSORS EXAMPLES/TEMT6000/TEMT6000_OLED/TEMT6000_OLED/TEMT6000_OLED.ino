#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//TEMT6000 sensor

#define light_pin        PB1                                   // Enter the GPIO pin 



uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 15;


/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***********************************************************************************************/

void setup()
{
    oledInit();                                     // Initialize the OLED display.

  Serial.begin(9600);
  pinMode(light_pin, INPUT);
  millis();
}
void loop()
{

  float Light = analogRead(light_pin) * 3.3 / 4096;           //  Read the volts from the temt 6000
  float Amps  = Light / 10000;                                // across 10,000 Ohms 10K ONBOARD RESISTANCE ON TEMT6000
  float Microamps = Amps * 1000000;                           // one ampere (A) is equal to 1,000,000 microamperes (uA).
  float Lux = Microamps * 2.0;                                // The datasheet for the TEMT6000 specifies a proportional correlation between current and illuminance
 
                                                              //  Every 2 µA of current correlates to 1 lx in the illuminance.                                                           //  micro amps to lux convertion
  StaticJsonDocument <256> Lightvalue;
  Lightvalue["light"] = Lux;
  String Lightdata;
  serializeJson(Lightvalue, Lightdata);
  display.clearDisplay();                           // Clear the OLED display.
  
  oledDisplayHeaderShow("DATA");   // Display a header on the OLED screen.
  oledScreenData(2, 0, 30, String(Lux));        //2 - font size , 0 - column, 30 - row
  oledScreenData(2, 50, 30, String(" Lux"));
  
  delay(500);
  if ((millis() - lastReport) >= Reporting_Interval)
  {
    lastReport = millis();
    Serial.println(Lightdata);
    delay(2000);
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
