#include <NewPing.h> 

const int TriggerPin = 12; 
const int EchoPin = 13; 

const int AIA = 10; 
const int AIB = 6;
const int BIA = 11;
const int BIB = 5;

byte speed = 150;  // change this (0-255) to control the speed of the motors

NewPing sonar(TriggerPin, EchoPin, 100); 

void setup() {
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  Serial.begin( 9600 );
}

void loop() {
 delay(200);
 int cm = sonar.ping_cm();
 Serial.println(cm);
 if(cm <= 10) {
  backward();
  Serial.println("back");
 }
}

void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void STOP()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  delay (2000);
}
