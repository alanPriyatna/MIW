/* EarthQuake Detector 
 * This codes works to detect earthquake.
 * Requires the device to set at a fixed point and switched on.
 * This example code is in the public domain.
 * Modified 09-Sept-2016 
 * By
 * Sanket Nainani
*/
#include "CurieIMU.h"
#define LED 11            //Pin for the LED to indicate working device
#define SWITCH 12         //Switch normally high, Starts to initialize and detect once it goes LOW
#define BUZZER 13

boolean blinkState = false;          // State of the LED
boolean detection = false;


void setup() {
  /* Serial to Debug on Serial monitor */
  //Serial.begin(9600);

  /* Setting pins to use as output */
  pinMode(LED,OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SWITCH,INPUT_PULLUP);

  /* Loop to place the device in a fixed position before initializing  */
  //while(digitalRead(SWITCH)){}
  
  /* Initialise the IMU and attaching interupt to monitor Shock */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Enable Shock Detection */
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1500);  // 1.5g = 1500 mg
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 50);     // 50ms
  CurieIMU.interrupts(CURIE_IMU_SHOCK);                   //Attaching interupt

  //Serial.println("IMU initialisation complete, waiting for events...");
}

void loop() {
  digitalWrite(LED, blinkState);  
  blinkState = !blinkState;                   //blinking LED to indicate detection state
  delay(1000);
  if(detection == true)
  {
    //Serial.println("Detection");
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);
    detection = false;
  }
}

/* Function called every time a shock is detected and indicates the direction of shock */ 
static void eventCallback(void)
{
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    if (CurieIMU.shockDetected(X_AXIS, POSITIVE))
    {
      detection = true;
      //Serial.println("Shock detected on X-axis");
    }
    if (CurieIMU.shockDetected(X_AXIS, NEGATIVE))
    {
      detection = true;
      //Serial.println("Shock detected on X-axis");
    }
    if (CurieIMU.shockDetected(Y_AXIS, POSITIVE))
     {
      detection = true;
      //Serial.println("Shock detected on Y-axis");
     }
    if (CurieIMU.shockDetected(Y_AXIS, NEGATIVE))
      {
        detection = true;
      //Serial.println("Shock detected on Y-axis");
      }
    if (CurieIMU.shockDetected(Z_AXIS, POSITIVE))
      {
        detection = true;
      //Serial.println("Shock detected on Z-axis");
      }
    if (CurieIMU.shockDetected(Z_AXIS, NEGATIVE))
     {
      detection = true;
      //Serial.println("Shock detected on Z-axis");
     }
  }
}
