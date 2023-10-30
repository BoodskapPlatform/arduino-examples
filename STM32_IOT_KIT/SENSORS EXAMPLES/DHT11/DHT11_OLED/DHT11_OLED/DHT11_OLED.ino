#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>                           // Adafruit sensor library by Adafruit
#include <DHT.h>     




#define DHT_PIN          PC13                          // Enter the DHT pin
#define DHT_TYPE         DHT11

DHT dht(DHT_PIN, DHT_TYPE);                            // Initialize the DHT sensor with the specified pin and type

uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 8;                // Reporting interval in milliseconds (8 seconds)



int i = 0;                     // Initialize an integer variable 'i'.
int fontsize = 1;              // Initialize an integer variable 'fontsize'.

/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***********************************************************************************************/


void setup() 
{
 

  oledInit();                                          // Initialize the OLED display.
  Serial.begin(9600);                                  // Initialize serial communication at 9600 baud
  dht.begin();                                         // Initialize the DHT sensor
  millis();                                            // This call to millis() doesn't do anything; it's not necessary.
 
}

void loop() 
{

    display.clearDisplay();             // Clear the OLED display.
    oledDisplayHeaderShow("DHT-Data");   // Display a header on the OLED screen.
  
    float T_data = dht.readTemperature();  // Read temperature data from the DHT sensor
    float H_data = dht.readHumidity();     // Read humidity data from the DHT sensor

    oledScreenData(2, 0, 20, String("T:"));        // Display the  value on the OLED screen.
    oledScreenData(2, 25, 20, String(T_data));        
    oledScreenData(2, 90, 20, String("*C"));

    oledScreenData(2, 0, 40, String("H:"));        // Display the  value on the OLED screen.
    oledScreenData(2, 25, 40, String(H_data));        
    oledScreenData(2, 90, 40, String("%"));
    
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
