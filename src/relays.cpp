#include <Arduino.h>
#define ON 0 // The relay actually turns ON with 0
#define OFF 1
#define SECOND 1000
// #define SECOND 10 // DEV!!

const long int MINUTE = SECOND * 60L;
// const long int MINUTE = SECOND * 2; // DEV!!

// const int MINUTE = SECOND * 10;
const long int TIME_WARMUP = 5;
const long int TIME_PUMP = 6;
const long int TIME_FAN = 60;
// const int TIME_FAN = MINUTE * 10;
const long int CYCLETIME = 60 * 4;
// const int CYCLETIME = MINUTE * 15;

void init_relays();
void print5();

// int MY_PIN = LED_BUILTIN; // Built-in LED
// int MY_PIN = 12; // Specified external LED
int MY_PIN = LED_BUILTIN;

int PIN_R1 = 3;
int PIN_R2 = 4;
int PIN_R3 = 5;
int PIN_R4 = 6;

int DEV_FAN = PIN_R1;
int DEV_LIGHT = PIN_R2;
int DEV_PUMP = PIN_R3;

// int MY_DELAY = 500; // Delay in ms
int MY_DELAY = 1000; // Delay in ms
// int RELAY_DELAY = 1000;
int RELAY_DELAY = 1;
// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(MY_PIN, OUTPUT);
  init_relays();
  Serial.begin(9600);
  Serial.print("START!\n");
}

void init_relays()
{
  //set all the relays OUTPUT
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);
  pinMode(PIN_R3, OUTPUT);
  pinMode(PIN_R4, OUTPUT);

  digitalWrite(PIN_R1, OFF);
  digitalWrite(PIN_R2, OFF);
  digitalWrite(PIN_R3, OFF);
  digitalWrite(PIN_R4, OFF);
}

// the loop function runs over and over again forever
int cnt_seconds = 0;
int cnt_minutes = 0;
int cnt_cyles = 0;
char data[100];

void loop()
{
  sprintf(data, "Minutes: %i   Cycle: %i\n", cnt_minutes, cnt_cyles);
  Serial.print(data);

  if (cnt_minutes == TIME_WARMUP)
  { // Start this 4 hour cycle
    sprintf(data, "Turning fan ON for %i minutes\n", TIME_FAN);
    Serial.print(data);
    digitalWrite(DEV_FAN, ON);
    sprintf(data, "Turning pump ON for %i minutes\n", TIME_PUMP);
    Serial.print(data);
    digitalWrite(DEV_PUMP, ON);
  }
  else if (cnt_minutes == TIME_WARMUP + TIME_PUMP) // PUMP OFF
  {
    Serial.print("Turning off pump\n");
    digitalWrite(DEV_PUMP, OFF);
  }
  else if (cnt_minutes == TIME_WARMUP + TIME_FAN)
  {
    Serial.print("Turning off fan\n");
    digitalWrite(DEV_FAN, OFF);
  }
  else if (cnt_minutes == CYCLETIME)
  {
    sprintf(data, "Cycle %i complete. Reset minutes.\n", cnt_cyles);
    cnt_minutes = 0;

    if (cnt_cyles == 5)
    {
      cnt_cyles = 0;
    }
    cnt_cyles += 1;
  }

  if (cnt_cyles == 5)
  {
    // Light is OFF for the 6th cycle
    // Reset the cycle counter
    digitalWrite(DEV_LIGHT, OFF);
  }
  else
  {
    digitalWrite(DEV_LIGHT, ON);
  }

  delay(MINUTE);
  cnt_minutes += 1;

  // cnt_seconds += 1;
  // if (cnt_seconds == 5) {
  // print5();
  // cnt_seconds = 0;
  // }

  // if (cnt_seconds == 30) {
  //   Serial.print("30!\n");
  //   cnt_seconds = 0;
  // }
}

void print5()
{
  Serial.print("5SECS!\n");
}

void extra()
{
  digitalWrite(MY_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
  digitalWrite(PIN_R1, HIGH);
  // delay(RELAY_DELAY);
  digitalWrite(PIN_R2, HIGH);
  // delay(RELAY_DELAY);
  digitalWrite(PIN_R3, HIGH);
  // delay(RELAY_DELAY);
  digitalWrite(PIN_R4, HIGH);
  Serial.print("ON");
  delay(MY_DELAY);           // wait for a second
  digitalWrite(MY_PIN, LOW); // turn the LED off by making the voltage LOW
  digitalWrite(PIN_R1, LOW);
  digitalWrite(PIN_R2, LOW);
  digitalWrite(PIN_R3, LOW);
  digitalWrite(PIN_R4, LOW);
  Serial.print("OFF");
  delay(MY_DELAY); // wait for a second
}