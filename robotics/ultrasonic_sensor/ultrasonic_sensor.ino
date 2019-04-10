#include <NewPing.h>

const int TriggerPin = 11;
const int EchoPin = 12;

NewPing sonar(TriggerPin, EchoPin, 100);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int cm = sonar.ping_cm();
  Serial.println(cm);
  delay(250);
}
