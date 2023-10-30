#include <ArduinoJson.h>                                /* include the ArduinoJson library which allows easy handling of JSON data */

#define motion_pin  PB5                                 // Enter the GPIO pin for the motion sensor

uint32_t lastReport = 0;                                // Variable to hold the time of the last report
uint32_t Reporting_Interval = 1000 * 15;                // Set the reporting interval to 15 seconds

void setup()
{
  Serial.begin(9600);                                   // Start the serial communication at 9600 bits per second
  pinMode(motion_pin, INPUT);                           // Set the pin mode of the motion sensor pin as input
  millis();                                             // Initialize the timer
}

void loop()
{
  
    int Motion = digitalRead(motion_pin);                 // Read the state of the motion sensor
  
    StaticJsonDocument <256> motionstate;                 // Create a JSON document with the capacity of 256 bytes
    motionstate["motion"] = Motion;                       // Add the motion state to the JSON document
    String jsonstate;                                     // Create a String to hold the JSON data
    serializeJson(motionstate, jsonstate);                // Serialize the JSON document to the String
    
    if ( ((millis() - lastReport) >= Reporting_Interval) || (Motion == 1) )
    {
      Serial.println(jsonstate);                          // Print the JSON data to the Serial Monitor
      lastReport = millis();                              // Update the lastReport time to the current time
      delay(2000);                                        // 2-second delay
    }
  
}
