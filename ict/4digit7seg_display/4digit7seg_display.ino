#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object

int i;
unsigned long time_now = 0;

int DELAY_MILLIS = 30;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}

void loop() {
    time_now = millis();
    
   if(i%4 > 999) {
      sevseg.setNumber(i, i%4);
    } else {
      sevseg.setNumber(i);
    }
      
    while(millis() < time_now + DELAY_MILLIS) {
      sevseg.refreshDisplay();
    }
    
    if(i < 10000) {
      i++;
    } else {
      i = 0;
    }
}
