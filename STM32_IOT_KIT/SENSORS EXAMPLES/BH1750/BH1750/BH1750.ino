
#include <hp_BH1750.h>                                                 /* Include the library for the BH1750 light sensor.*/
#include <ArduinoJson.h>

hp_BH1750 BH1750;                                                     


uint32_t lastReport = 0;                                               /* Variables to control reporting intervals.*/
uint32_t REPORTING_INTERVAL = (15 * 1000);                             /* 15 seconds in milliseconds.*/

void setup()
{
  millis();                                                                 

  Serial.begin(9600);                                                 /* Initialize the serial communication */

  bool avail = BH1750.begin(BH1750_TO_GROUND);
                                                                      /* Initialize the BH1750 sensor with the address pin connected to ground.*/
                                                                      /*The "avail" variable will be "true" if the sensor is found, "false" otherwise.*/

  if (!avail) 
  {
    Serial.println("No BH1750 sensor found!");                        /* If the sensor is not found, print an error message and enter an infinite loop.*/
   
    while (true) {};
  }
}

void loop() 
{
  BH1750.start();                                                      /* Start a measurement with the BH1750 sensor.*/

  float lux = BH1750.getLux();
                                                                       /* Wait until a conversion is finished, and then read the lux value from the sensor.*/

                                                                       /* Create a JSON document to store the light data.*/
  StaticJsonDocument<256> lightdata;
  lightdata["light"] = lux;                                            /* Store the lux value in the JSON document.*/

  String Jsonvalue;                                                    /* Create a String variable to hold the JSON data.*/
  serializeJson(lightdata, Jsonvalue);                                 /* Serialize the JSON document to a String.*/

  if ((millis() - lastReport >= REPORTING_INTERVAL))
  {
                                                                       /* Check if it's time to report the data based on the reporting interval.*/
    lastReport = millis();                                             /* Update the last reporting time.*/

    Serial.println(Jsonvalue);                                         /* Print the JSON data to the serial monitor.*/

    delay(2000);                                                       /* Delay for 2 seconds before the next report.*/
  }
}
