//download libraries from blynk's official site.

//#define BLYNK_USE_DIRECT_CONNECT

#define BLYNK_PRINT Serial

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "66d601408f1641fabda10524db00587c";

BLEPeripheral  blePeripheral;

int led[3][3] = {
    {3,4,5},
    {6,7,8},
    {9,10,11}
  };
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() {
  //declare LEDs as OUTPUT
  
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      pinMode(led[i][j], OUTPUT);
    }
  }
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);

   blePeripheral.setLocalName("Smart_Lighting_xxx");
   blePeripheral.setDeviceName("Smart_Lighting_xxx");
   blePeripheral.setAppearance(384);
   Serial.println("ble will start now start");
   Blynk.begin(auth, blePeripheral);
   blePeripheral.begin();
}

void loop(){
  Blynk.run();
  blePeripheral.poll();

  //detectMotion();
  //rowByRow(); 
  //delay(1000);
  //oneByOne();
  //delay(1000);
  //corners();
  //delay(1000);
  //colByCol();
  //delay(1000);
}


void detectMotion(){

   val = digitalRead(inputPin);  // read input value
   if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      pirState = HIGH;
      allLEDs(HIGH);
      delay(500);
    }
  } else {
      if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      pirState = LOW;
      allLEDs(LOW);
      delay(500);
    }
  }

}

void allLEDs(int output){

  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      digitalWrite(led[i][j], output);
    }
  }
}

void rowByRow(){
  for(int k=0;k<3;k++){
    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
        digitalWrite(led[i][j], HIGH);
      }
      delay(200);
    }
    //delay(1000);
    for(int i=2;i>=0;i--){
      for(int j=0;j<3;j++){
        digitalWrite(led[i][j], LOW);
      }
     delay(200);
    }  
  }
}

void colByCol(){
  for(int k=0;k<3;k++){
    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
        digitalWrite(led[j][i], HIGH);
      }
      delay(200);
      for(int j=0;j<3;j++){
        digitalWrite(led[j][i], LOW);
      }
    }
  }
}


void oneByOne(){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      digitalWrite(led[j][i], HIGH);
      delay(200);
    }
  }
  delay(1000);
  for(int i=2;i>=0;i--){
    for(int j=2;j>=0;j--){
      digitalWrite(led[j][i], LOW);
      delay(200);
    }
  }
}


void corners(){

  for(int i=0;i<3;i++){
    digitalWrite(led[0][0], HIGH);
    digitalWrite(led[0][2], HIGH);
    digitalWrite(led[1][1], HIGH);
    digitalWrite(led[2][0], HIGH);
    digitalWrite(led[2][2], HIGH);
    delay(250);
    digitalWrite(led[0][0], LOW);
    digitalWrite(led[0][2], LOW);
    digitalWrite(led[1][1], LOW);
    digitalWrite(led[2][0], LOW);
    digitalWrite(led[2][2], LOW);

    digitalWrite(led[0][1], HIGH);
    digitalWrite(led[1][0], HIGH);
    digitalWrite(led[1][2], HIGH);
    digitalWrite(led[2][1], HIGH);
    delay(250);
    digitalWrite(led[0][1], LOW);
    digitalWrite(led[1][0], LOW);
    digitalWrite(led[1][2], LOW);
    digitalWrite(led[2][1], LOW);
  }
}

BLYNK_WRITE(V1) 
{
  int ledMode = param.asInt();
  Serial.println("PINMODE : " + ledMode);
  if(ledMode == 0)
    detectMotion();
  else if(ledMode == 1)
    rowByRow();
  else if(ledMode == 2)
    oneByOne();
  else if(ledMode == 3)
    corners();
  else if(ledMode == 4)
    colByCol(); 
}

BLYNK_WRITE(V0) 
{
  int ledMode = param.asInt();
  Serial.println("PINMODE : " + ledMode);
}

/**
BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  int ledMode = param.asInt();
  if(ledMode = 1)
    allLEDs(HIGH);
  else
    allLEDs(LOW);
   
}
*/

