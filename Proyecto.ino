//Including Libraries
#include <SPI.h>      //SPI Library
#include <Wire.h>     //Include the Wire Library
#include <MFRC522.h>  //Library of the RFID Module
#include <Stepper.h>  //Library for the Stepper Motor
//Pins used by the RFID Module
#define SS_PIN 10
#define RST_PIN 9
//LED pins
int ledr = 6;
int ledg = 7;
MFRC522 mfrc522(SS_PIN, RST_PIN);    //Creates an object "mfrc522", the RFID Module
Stepper myStepper(500, 2, 4, 3, 5);  //Creates an object "myStepper", the Stepper motor
void setup() {
  myStepper.setSpeed(60);  //Sets Stepper motor speed
  SPI.begin();             //Starts the SPI Library
  mfrc522.PCD_Init();      //Starts the RFID Module
  Wire.begin();            //Starts the Wire library
  //Defining LEDs as output
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);
}
void loop() {
  digitalWrite(ledr, HIGH);                //Red LED is on
  if (!mfrc522.PICC_IsNewCardPresent()) {  //RFID module searches for new TAGs
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {  //Reads the TAG
    return;
  }
  //Decoding the TAG code
  String content = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();  //Converts the text to upper case
  //The locker system
  if (content.substring(1) == "13 C4 4C A6") {  //Change here by the code of your TAG
    digitalWrite(ledr, LOW);
    digitalWrite(ledg, HIGH);  //Green LED turns on
    myStepper.step(-512);      //Stepper motor moves
    delay(5000);
    digitalWrite(ledr, HIGH);  //Red LED turns on again
    digitalWrite(ledg, LOW);
    myStepper.step(512);  //Stepper motor moves
  }
  //Acess denied
  else if (content.substring(1) != "13 C4 4C A6") {  //Change here too
  }
}
