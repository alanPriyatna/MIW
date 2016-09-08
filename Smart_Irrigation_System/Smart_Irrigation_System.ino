/* Smart Irrigation
 * Controlling a Pump via a mobile app
 * Requires the bluetooth to be connected and set.
 * This example code is in the public domain.
 * Modified 09-Sept-2016
 * By
 * Sanket Nainani
 */
#include <CurieBLE.h>

char inData[20]={};         //Character array for storing and checking command recieved

const int ledPin = 13; // set ledPin to use on-board LED

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)

/*create Nordic Semiconductor UART service. This contains the Serial for communication with the app*/
BLEService uartService = BLEService("6E400001B5A3F393E0A9E50E24DCCA9E");
/* create characteristics channels for transmission of data */
BLECharacteristic rxCharacteristic = BLECharacteristic("6E400002B5A3F393E0A9E50E24DCCA9E", BLEWriteWithoutResponse, 20);  // == TX on central (android app)
BLECharacteristic txCharacteristic = BLECharacteristic("6E400003B5A3F393E0A9E50E24DCCA9E", BLENotify , 20); // == RX on central (android app)

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // use the LED on pin 13 as an output

  // set advertised local name and service UUID: The name displayed inside the App
  blePeripheral.setLocalName("Smart Irrigation System");
  blePeripheral.setAdvertisedServiceUuid(uartService.uuid());

  // add service, rx and tx characteristics:
  blePeripheral.addAttribute(uartService);
  blePeripheral.addAttribute(rxCharacteristic);
  blePeripheral.addAttribute(txCharacteristic);

  // assign event handlers for connected, disconnected to peripheral
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handler for characteristic
  rxCharacteristic.setEventHandler(BLEWritten, rxCharacteristicWritten);

  // advertise the service
  blePeripheral.begin();
}

void loop() {
  // poll ble peripheral
  blePeripheral.poll();  
}

void blePeripheralConnectHandler(BLECentral& central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
  Serial.println("LED on");
  digitalWrite(ledPin, HIGH);
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
  Serial.println("LED off");
  digitalWrite(ledPin, LOW);
}

void rxCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic)  {
     Serial.print("Handler -- rxCharactersiticWritten. Length: ");

     int len = characteristic.valueLength();               // Reads the length of data sent from central
     Serial.println(len);
     int i; 
     if (len != 0) {
      
        //Storing the Command recieved in the array
        for (i=0; i < len; i=i+1){
          inData[i] = characteristic[i];
          }
          
        i = len + 1 ;                                        // Add newline to make inData a string
        Serial.println(inData);                              // Printing the Command recieved to serial monitor
        
        //Checking the command recieved and taking actions
        if(String(inData)=="ON")
        {
          digitalWrite(ledPin, HIGH);
          Serial.print("Pump Turning ON");
        }
        if(String(inData)=="OFF")
        {
          digitalWrite(ledPin, LOW);
          Serial.print("Pump Turning OFF");
        }
      }
      
      // Flushing any buffers
      for(int i=0;i<len;i++)
      {
        inData[i]='\0';
      }
}
