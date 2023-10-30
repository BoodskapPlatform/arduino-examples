

#define BUZZER PA8

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin BUZZER as an output.
  pinMode(BUZZER, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(BUZZER, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(BUZZER, LOW);    // turn the BUZZER off by making the voltage LOW
  delay(1000);                       // wait for a second
}
