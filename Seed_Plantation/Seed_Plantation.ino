/**
 * Robot to Seed
 * Connect Blynk App and drive robot Forword,Backword,Right,Left and Rotate Servo for Seed planting.
 * This example code is in the public domain.
 * modified April-2017 by 
 * Raj Shah
*/
#include <Servo.h>

///////////      MOTOR DRIVER   /////
//Motor 1
int ENA = 2; //Connect on Arduino, Pin 2
int IN1 = 3; //Connect on Arduino, Pin 3
int IN2 = 4; //Connect on Arduino, Pin 4

//Motor2
int ENB = 5; //Connect on Arduino, Pin 5
int IN3 = 6; //Connect on Arduino, Pin 6
int IN4 = 7; //Connect on Arduino, Pin 7

//Servo
const int servoPin = 9;
const int servoDeg = 180;
Servo myservoA;

void setup() {
  /////    MOTOR DRIVER  ///
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  Serial.println("Setting speed for motor");
  analogWrite(ENA, 200); // Activer moteur A
  analogWrite(ENB, 200); // Activer moteur B

  Serial.println("Attaching Servo Motor");
  myservoA.attach(servoPin);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:
  driveForward();
  delay(1000);
  
  driveBackword();
  delay(1000);
  
  driveLeft();
  delay(1000);
  
  driveRight();
  delay(1000);
  
  driveStop();
  delay(1000);

  openServo();
}

void driveForward() {
  digitalWrite(IN1, LOW); //Forward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}

void driveStop() {
  digitalWrite(IN1, HIGH); //Stop
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

}

void driveBackword() {
  digitalWrite(IN1, HIGH); //Backword
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void driveLeft() {
  digitalWrite(IN1, HIGH); //Left
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}

void driveRight() {
  digitalWrite(IN1, LOW); //Right
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

}

void openServo(){
   myservoA.write(servoDeg);
   delay(1000);
   myservoA.write(0);  
}

//Blynk --- Code
//V1 - Forword
//V2 - Backword
//V3 - Left
//V4 - Right
//V5 - Servo
