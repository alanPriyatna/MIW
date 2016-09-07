/*WATER QAULITY ANALYSER
  Displays quality of water on 16x2 LCD shield in propotion to reading of ph sensor.

  connections:

  breakout board  |  genuino 101
  -------------------------------
        5V        |   5V
        GND1      |   GND
        GND2      |   GND
        Po        |   A0
  -------------------------------

  modified 27-aug-2016 by
  Akshay Chawla
*/

// include the library for LCD shield:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int pHpin = A0;    // Connect the sensor's Po output to analog pin 0.

// Variables:-
float Po;

void setup()
{
  pinMode(pHpin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" WATER QUALITY");
}

void loop()
{
  Po = 1023 - analogRead(pHpin); // Read and reverse the analogue input value from the pH sensor.

  Po = Po / 1023 * 14; // Map the '0 to 1023' result to '0 to 14'.

  if (Po < 6.5 || Po > 7.5) //check if the water quality is good or bad.
  {
    lcd.setCursor(0, 1);
    lcd.print("    NOT GOOD    ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("      GOOD      ");
  }

  delay(1000);                    // Take 1 reading per second.
}
