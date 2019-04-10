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

int MDD = 300;
int FDD = 50;
int LDD = 25;
int RDD = 25;
int scanDelay = 10;
byte speed = 255;

Servo servo;
NewPing sonar(triggerPin, echoPin, MDD); 

void setup() {
  Serial.begin(9600);
  servo.attach(servoDataPin);
  servo.write(75); //20 75 150
  wait(1);
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  Serial.begin( 9600 );
}

void loop() {
  lookOnlyAtFront();
  if((front_distance > FDD) && (front_distance >= 0)) {
    go_front();
    wait(0.5);
  } else {
    stop_vehicle();
    scanForObstacles();
    driver();
  }
  Serial.println("front: " + String(front_distance) + " // left:" + String(left_distance) + " // right:" + String(right_distance));
}

void driver() {
  if((front_distance < FDD) && (front_distance > 0)) {
    go_back();
    wait(1);
    stop_vehicle();
    wait(0.5);
    if(left_distance < right_distance) {
      turn_right();
      wait(0.5);
      stop_vehicle();
      wait(0.5);
    } else {
      turn_left();
      wait(0.5);
      stop_vehicle();
      wait(0.5);
    }
  }
  if(left_distance < LDD) {
    turn_right();
    wait(0.5);
    stop_vehicle();
    wait(0.5);
  }
  if(right_distance < RDD) {
    turn_left();
    wait(0.5);
    stop_vehicle();
    wait(0.5);
  }
}

void wait(double secs) {
  delay(secs * 1000);
}

void scanForObstacles() {
  leftDetection();
  delay(scanDelay);
  rightDetection();
  delay(scanDelay);
}

void lookOnlyAtFront() {
  frontDetection();
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

void turn_left() {
  digitalWrite(AIA,speed);
  digitalWrite(AIB,LOW);  
}
void turn_right() {
  digitalWrite(BIA,LOW);
  digitalWrite(BIB,speed); 
}
void go_front() {
  digitalWrite(AIA,speed);
  digitalWrite(AIB,LOW);
  digitalWrite(BIA,LOW);
  digitalWrite(BIB,speed);
}
void go_back() {
  digitalWrite(BIA,speed);
  digitalWrite(BIB,LOW);
  digitalWrite(AIA,LOW);
  digitalWrite(AIB,speed); 
}
void stop_vehicle() {
  digitalWrite(BIA,LOW);
  digitalWrite(BIB,LOW);
  digitalWrite(AIA,LOW);
  digitalWrite(AIB,LOW);
}
