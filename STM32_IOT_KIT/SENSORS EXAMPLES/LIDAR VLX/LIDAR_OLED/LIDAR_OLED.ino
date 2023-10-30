#include "Adafruit_VL53L0X.h"                    // include header file of sensor library           
#include <ArduinoJson.h>
#include <SPI.h>                                 // for communicating with one or more peripheral devices quickly over short distances
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


uint32_t lastReport = 0;
uint32_t REPORTING_INTERVAL = (8*1000);


Adafruit_VL53L0X lox = Adafruit_VL53L0X();      //we define an object of a structure-function of Adafruit_VL53L0X() Because we can use the same library to read distance measurement data from multiple VL53L0X modules.


/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***********************************************************************************************/


void setup() 
{
  
  Serial.begin(9600);
  oledInit();                                     // Initialize the OLED display.
  millis();
  if (!lox.begin()) //condition checks either you made a connection with the sensor correctly or not.
    {
      //Serial.println(F("Failed to boot VL53L0X")); // checks if the module is ready to operate. If not, “Failed to boot VL53L0X” message will display on serial print.
      while(1);
    }

} 

void loop() 
{

        display.clearDisplay();             // Clear the OLED display.
        oledDisplayHeaderShow("BH-Data");   // Display a header on the OLED screen.
       
        int range ;
        VL53L0X_RangingMeasurementData_t measure;    
        lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
        if (measure.RangeStatus != 4) 
        {  
            delay(500);
            range = measure.RangeMilliMeter;
        } 
        else 
        {
           range = 0;
        }   

        oledScreenData(2, 0, 30, String(range));        // Display the lux value on the OLED screen.
        oledScreenData(2, 90, 30, String("MM"));
        
        StaticJsonDocument < 256 > lidardata;
        lidardata["distance"] = range;
        String Jsonvalue;
        serializeJson(lidardata, Jsonvalue);

        if ((millis() - lastReport >= REPORTING_INTERVAL) || (range < 100)&&(range > 0))
        {
                    lastReport = millis();
                    Serial.println(Jsonvalue);
                    delay(2000);
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
    
