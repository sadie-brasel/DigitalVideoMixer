//Digital Glitch Mixer V2 
//Uses HC-SR04 ultrasonic sensor to control digital potentiometer MCP4131
//by Sadie Brasel
//August 16th 2025

#include <SPI.h>

int csPin  = 53;  // pin for chip select on MCP for SPI comm.
const int trigPin = 9; // pin for HC-SR04 trigger
const int echoPin = 10; // pin for HC-SR04 echo
float duration, distance;
int maxDist = 50;
int distanceInt;
int potVal;

void setup() {
  // initialize input/ouputs:
  SPI.begin();
  Serial.begin(9600);

  pinMode(csPin,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(csPin,LOW); //set chip select to low

//initialize mixer to zero state
  SPI.transfer(0); //send a zero first for suum reason (0-256)
  SPI.transfer(0); //send value

  }

void loop() {
  //determine distance val from the HC-SR04 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  distanceInt = (int)distance;
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //delay(100);

  if (distanceInt > 50)
  {
    potVal = 0;
  }
  else
  {
    potVal = map(distanceInt,0,50,256,0);
  }

   SPI.transfer(0); //send a zero first for suum reason (0-256)
   SPI.transfer(potVal); //send value
   Serial.print("Pot Value: ");
   Serial.println(potVal);
   delay(100);
}
