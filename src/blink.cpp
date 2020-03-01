#include <Arduino.h>

// int MY_PIN = LED_BUILTIN; // Built-in LED
// int MY_PIN = 12; // Specified external LED
int MY_PIN = LED_BUILTIN;
int MY_DELAY = 100; // Delay in ms
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(MY_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(MY_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(MY_DELAY);                       // wait for a second
  digitalWrite(MY_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(MY_DELAY);                       // wait for a second
}