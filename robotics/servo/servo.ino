#include <Servo.h>
#include <NewPing.h>

int pos = 0;
const int triggerPin = 11; 
const int echoPin = 12;
int servoDataPin = 9;

const int AIA = 10;
const int AIB = 3;
const int BIA = 6;
const int BIB = 5;

int front_distance = 0;
int left_distance = 0;
int right_distance = 0;

int scanDelay = 100;
byte speed = 200;

Servo servo;
NewPing sonar(triggerPin, echoPin, 100); 

void setup() {
  Serial.begin(9600);
  servo.attach(servoDataPin);
  servo.write(75); //20 75 150
  pinMode(AIA, OUTPUT); // set pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  Serial.begin( 9600 );
}

void loop() {
  delay(250);
  go_back();
  //scanForObstacles();
  //driver();
}

void driver() {
  if((front_distance <= right_distance) && (front_distance <= left_distance)) {
    go_front();
  } else if((right_distance <= left_distance) && (right_distance <= front_distance)) {
    turn_right();
  } else if((left_distance <= right_distance) && (left_distance <= front_distance)) {
    turn_left();
  } else {
    go_back();
  }
}

void scanForObstacles() {
  leftDetection();
  Serial.println("left: " + String(left_distance));
  delay(scanDelay);
  frontDetection();
  Serial.println("front: " + String(front_distance));
  delay(scanDelay);
  rightDetection();
  Serial.println("right: " + String(right_distance));
  delay(scanDelay);
}

void frontDetection() {
  for(int i=0;i<=5;i++){
    servo.write(75);
  }
  delay(300);
  front_distance = sonar.ping_cm();
}

void leftDetection() {
  for(int i=0;i<=15;i++) {
    servo.write(150);
  }
  delay(300);
  left_distance = sonar.ping_cm();
}

void rightDetection() {
  for(int i=0;i<=15;i++) {
    servo.write(20);
  }
  delay(300);
  right_distance = sonar.ping_cm();
}

void turn_left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void turn_right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void go_front()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void go_back()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void stop_vehicle()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  delay (2000);
}
