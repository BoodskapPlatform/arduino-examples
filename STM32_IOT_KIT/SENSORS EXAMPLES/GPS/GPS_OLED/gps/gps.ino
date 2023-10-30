#include <ArduinoJson.h>                      // Include the ArduinoJson library for JSON serialization.
#include <HardwareSerial.h>                   // Include the HardwareSerial library.

#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

HardwareSerial Serial3(USART3); // PB11 (RX)  PB10   (TX)  Initialize the serial communication for USART3.


float lat_long_calculation(char *gps_location_lat_lon);
String GPS_GPRMC();


char inputString[100];             //a string to hold incomming data
bool stringComplete = false;       //whether string is complete


unsigned char condition_check_variable;
unsigned int i = 0;
unsigned int k = 0;
unsigned int z = 0;

char timee[10];
char gps_fix;
char lattitude[15];
char lat_dir;
char longitude[15];
char lon_dir;
char date[11];
char GPS_information[100];
char final_lattitude[15];
char final_longitude[15];
unsigned int split_variable; //',' splitted
unsigned int Gps_infomation_variable = 0;
int Gps_infomation_variable1;
unsigned int seconds;
unsigned int  minits;
unsigned int hours;
char indian_time_gps[9];
unsigned int lattitude_length;
unsigned int longitude_length;
char gps_degree[4];
char gps_minutes[15];
float decimal_lattitude;
float decimal_longitude;
int dot_length;
String G;



uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 5;

/***************************************************************************************************************************************/
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
/***********************************************************************************************/
void setup()
{
  oledInit();                                     // Initialize the OLED display.

  millis();
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop()
{

  display.clearDisplay();             // Clear the OLED display.
  oledDisplayHeaderShow("GPS");   // Display a header on the OLED screen.
 
  
  if (stringComplete)
  {

    String location_json = GPS_GPRMC();

    if ((millis() - lastReport) >= Reporting_Interval)       // Check if the reporting interval has elapsed.

    {
      lastReport = millis();
      Serial.println(location_json);
      delay(500);
    }

    stringComplete = false;

  }

  while (Serial3.available())
  {

    char inChar = (char)Serial3.read();

    if (inChar != '\n')
    {

      if ( inChar == '$')
      {
        i = 0;
        inputString[0] = inChar;

      }
      else if (inputString[0] == '$')
      {
        i++;
        inputString[i] = inChar;
      }


    }

    else if (inChar == '\n')
    {

      stringComplete = true;

      i = 0;
      break;

    }
  }

}

String GPS_GPRMC()
{

  Gps_infomation_variable = 0;
  GPS_information[0] = '$';
  GPS_information[1] = 'G';
  GPS_information[2] = 'P';
  GPS_information[3] = 'S';

  if (  (inputString[0] == '$') && (inputString[1] == 'G') && (inputString[2] == 'P') && (inputString[3] == 'R')  && (inputString[4] == 'M') && (inputString[5] == 'C'))
  {

    k = 0;
    i = 0;
    split_variable = 0;

    Gps_infomation_variable = 4;

    //Serial.println("******");

    //*********************************** split time,lat,lon,date using ',' character *********************************************************

    while (inputString[i] != '\0')
    {

      if (inputString[i] == ',')

      {

        split_variable++;
        z = 0;
        //i++;

      }


      switch (split_variable)
      {

        case 1:

          timee[z] = inputString[i];
          z++;
          break;

        case 2:

          gps_fix = inputString[i];

          GPS_information[Gps_infomation_variable] = gps_fix ;

          Gps_infomation_variable++;

          break;

        case 3:


          lattitude[z] = inputString[i];

          GPS_information[Gps_infomation_variable] = lattitude[z];

          Gps_infomation_variable++;
          z++;

          break;

        case 4:

          lat_dir = inputString[i];

          GPS_information[Gps_infomation_variable] = lat_dir ;

          Gps_infomation_variable++;

          break;

        case 5:

          longitude[z] = inputString[i];

          GPS_information[Gps_infomation_variable] = longitude[z];

          Gps_infomation_variable++;

          longitude_length = z;

          z++;

          break;

        case 6:

          lon_dir = inputString[i];

          GPS_information[Gps_infomation_variable] = lon_dir ;

          Gps_infomation_variable++;

          break;

        case 9:

          date[z] = inputString[i];

          GPS_information[Gps_infomation_variable] = date[z] ;

          Gps_infomation_variable++;

          z++;

          break;

        case 11:
          z = 0;


      }

      i++;
    }


    hours = (((timee[1] - 48) * 10) + (timee[2] - 48)) + 5;

    if (hours >= 24 )
    {
      hours = hours - 24;
    }

    minits = (((timee[3] - 48) * 10) + (timee[4] - 48)) + 30;

    if (minits >= 60)
    {
      minits = minits - 60;

      hours = hours + 1;
    }

    seconds = ((timee[5] - 48) * 10) + (timee[6] - 48);


    indian_time_gps[0] = (hours / 10) + 48;
    indian_time_gps[1] = (hours % 10) + 48;
    indian_time_gps[2] = ':';

    indian_time_gps[3] = (minits / 10) + 48;
    indian_time_gps[4] = (minits % 10) + 48;
    indian_time_gps[5] = ':';

    indian_time_gps[6] = (seconds / 10) + 48;
    indian_time_gps[7] = (seconds % 10) + 48;


    GPS_information[Gps_infomation_variable] = ',';
    Gps_infomation_variable++;

    for (i = 0; indian_time_gps[i] != '\0'; i++)
    {
      GPS_information[Gps_infomation_variable] = indian_time_gps[i];
      Gps_infomation_variable++;

    }


    if (gps_fix == 'V')
    {

      Gps_infomation_variable1 = 0;

      while ( GPS_information[Gps_infomation_variable1] != '\0')
      {
        if (Gps_infomation_variable1 < Gps_infomation_variable)
        {
          //                Serial.print( GPS_information[Gps_infomation_variable1]);
          Gps_infomation_variable1++;
        }
        else
        {
          //                Serial.print( GPS_information[Gps_infomation_variable1] = '\0');
          Gps_infomation_variable1++;
        }

      }

      StaticJsonDocument <256> gps;
      gps["lat"] = 0;
      gps["lon"] = 0;

      oledScreenData(2, 0, 20, String(0.00));        // Display the  value on the OLED screen.
     
      oledScreenData(2, 0, 40, String(0.00));        // Display the  value on the OLED screen.
      
      String location;
      serializeJson(gps, location);
      delay(1000);
      return (location);

    }
    else if (gps_fix == 'A')
    {

      lat_long_calculation(lattitude);
      lat_long_calculation(longitude);

      float decimal_lattitude = lat_long_calculation(lattitude);
      float decimal_longitude = lat_long_calculation(longitude);

      String lat = String(decimal_lattitude);
      String lon = String(decimal_longitude);
      
      oledScreenData(1, 0, 20, String(lat));        // Display the  value on the OLED screen.
     
      oledScreenData(1, 0, 40, String(lon));        // Display the  value on the OLED screen.
    
    
  
      StaticJsonDocument <256> gps;
      gps["lat"] = decimal_lattitude;
      gps["lon"] = decimal_longitude;
      String location;
      serializeJson(gps, location);
      delay(1000);
      return (location);

    }

  }

  for (i = 0; inputString[i] != '\0'; i++)
  {
    inputString[i] = '\0';
  }

  return ("0");
}


float lat_long_calculation(char *gps_location_lat_lon)
{

  int z, l, total_length;
  int dot_length;
  char decimal_gps[15];

  for (z = 0; gps_location_lat_lon[z] != '\0'; z++)
  {

    decimal_gps[z] = gps_location_lat_lon[z];

    if (gps_location_lat_lon[z] == '.')
    {

      dot_length = z;

    }

    total_length = z;

  }

  l = 0;

  for (z = 1; z < (dot_length - 2); z++)
  {

    gps_degree[l] = decimal_gps[z];

    l++;

  }

  l = 0;

  for (z = (dot_length - 2); z <= total_length; z++)
  {
    gps_minutes[l] = decimal_gps[z];

    l++;
  }

  float pi = atof(gps_degree);
  float pi1 = atof( gps_minutes);
  float pi3 = pi + (pi1 / 60);

  for (z = 0; gps_degree[z] != '\0'; z++)
  {

    gps_degree[z] = '\0';
  }

  return (pi3);
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
