#include <ArduinoJson.h>

// TEMT6000 sensor

#define light_pin PB1 // Enter the GPIO pin

uint32_t lastReport = 0;
uint32_t Reporting_Interval = 1000 * 15;

void setup()
{
  Serial.begin(9600);
  pinMode(light_pin, INPUT);
  millis();
}
void loop()
{

  float Light = analogRead(light_pin) * 3.3 / 4096; //  Read the volts from the temt 6000
  float Amps = Light / 10000;                       // across 10,000 Ohms 10K ONBOARD RESISTANCE ON TEMT6000
  float Microamps = Amps * 1000000;                 // one ampere (A) is equal to 1,000,000 microamperes (uA).
  float Lux = Microamps * 2.0;                      // The datasheet for the TEMT6000 specifies a proportional correlation between current and illuminance
                                                    //  Every 2 µA of current correlates to 1 lx in the illuminance.                                                           //  micro amps to lux convertion
  StaticJsonDocument<256> Lightvalue;
  Lightvalue["light"] = Lux;
  String Lightdata;
  serializeJson(Lightvalue, Lightdata);

  if ((millis() - lastReport) >= Reporting_Interval)
  {
    lastReport = millis();
    Serial.println(Lightdata);
    delay(2000);
  }
}
