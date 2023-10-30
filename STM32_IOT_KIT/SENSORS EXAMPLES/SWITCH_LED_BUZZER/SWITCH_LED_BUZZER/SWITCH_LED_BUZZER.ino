#define LED     PB15      // Define the pin for the LED
#define BUZZER  PA8       // Define the pin for the BUZZER
#define SWITCH  PA11      // Define the pin for the SWITCH

void setup()
{
  pinMode(BUZZER, OUTPUT);   // Set the BUZZER pin as an output
  pinMode(LED, OUTPUT);      // Set the LED pin as an output
  pinMode(SWITCH, INPUT);    // Set the SWITCH pin as an input
}

void loop()
{
  if (digitalRead(SWITCH) == 0) // If the SWITCH is in the LOW state
  {
    digitalWrite(BUZZER, HIGH);   // Turn the BUZZER on (HIGH voltage level)
    digitalWrite(LED, HIGH);      // Turn the LED on (HIGH voltage level)
  }
  else  // If the SWITCH is not in the LOW state
  {
    digitalWrite(BUZZER, LOW);    // Turn the BUZZER off by setting the voltage to LOW
    digitalWrite(LED, LOW);       // Turn the LED off by setting the voltage to LOW
  }
}
