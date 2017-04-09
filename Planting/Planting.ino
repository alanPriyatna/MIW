/*Smart irrigation-planting system
  Gives water automatically to the plant as and when required.


  This example code is in the public domain.

  modified March-2017 by
  Raj Shah
*/
int ledPin=13;
int moiPin=A1;
int motorSwitch=8;

const boolean DEBUG = true;
boolean isMotorON = false;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(moiPin,INPUT);
  pinMode(motorSwitch,OUTPUT);
  //make sure motor is turned off initially.

  digitalWrite(motorSwitch,LOW);
  isMotorON = false;
}

void loop()
{
  static int count;
  float moi = soilMoisture();   //read soil moisture data
  
  if(moi<4.0)
  {    
    //this is case when soil moisture is ok
    //but still we will give water to plant for 10 seconds, for stability.
    
    count++;
    if(count<6)   
    {      
      //if motor is not turned on yet,Turn ON
      if( !isMotorON ){
        digitalWrite(motorSwitch,LOW);
        isMotorON = true;
      } 
      digitalWrite(ledPin,HIGH);
      if(DEBUG){
        Serial.println("Thank You!...");
      }
      delay(1000);
      digitalWrite(ledPin,LOW);
      delay(1000);
    }
    else if(count==6)
    {
      digitalWrite(ledPin,HIGH);
      if(DEBUG){
        Serial.println("Water is stopped now,plant has enough water...");
      }
      delay(5000);
      digitalWrite(ledPin,LOW);

      //turn motor off now
      if( isMotorON ){
        digitalWrite(motorSwitch,HIGH);
        isMotorON = false;
      }
    }
    else{
     //do nothing 
    }
  }
  else
  {
    //this is the case when olant needs water

    
    //if motor is not turned on yet,Turn ON
    if( !isMotorON ){
      digitalWrite(motorSwitch,LOW);
      isMotorON = true;
    }
    count=0;
    digitalWrite(ledPin,HIGH);
    delay(int(moi*100));    
    digitalWrite(ledPin,LOW);
    delay(int(moi*100));
    digitalWrite(ledPin,HIGH);
    delay(int(moi*100));    
    digitalWrite(ledPin,LOW);
    delay(int(moi*100));
    if(DEBUG){
      Serial.println("********************");
      Serial.println("    Plant needs water ...   ");  
    }
  }
}


float soilMoisture(){
  int readedValue=analogRead(moiPin);
  float voltage=float(readedValue*(float(5.0/1023.0)));        //To Count Voltage

  if(DEBUG){
      Serial.print("Sensor Reading :\t");
      Serial.println(readedValue);
      Serial.print("Voltage :\t");
      Serial.println(voltage);
    
  }
  
  return voltage;
}


