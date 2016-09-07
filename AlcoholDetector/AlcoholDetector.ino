/*Alcohol Detector
  Turns on LEDs in propotion to reading of alcohol sensor MQ3.


  This example code is in the public domain.

  modified 27-aug-2016 by
  Akshay Chawla
*/
int LED_1 = 6;
int LED_2 = 7;
int LED_3 = 8;
int LED_4 = 9;
int LED_5 = 10;

int alcohol = A0;

int value = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 1b as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);

  pinMode(alcohol, INPUT);
}

// the loop function runs over and over again forever
void loop() {

  value = analogRead(alcohol);

  if (value < 200)
  {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
  }

  else if (value < 400)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
  }

  else if (value < 500)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
  }

  else if (value < 600)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
  }

  else if (value < 800)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, LOW);
  }

  else
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
  }
}
