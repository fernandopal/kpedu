#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long elapsedSecconds = 0;
long elapsedMinutes = 0;
long elapsedHours = 0;

double timeMultiplier = 1; // Normal speed = 1 // x2 speed = 0.5 (0.xx values are faster)
int screenRefreshDelay = 60;

long oneSeccond = (1000 * timeMultiplier);
long oneMinute = (60000 * timeMultiplier);
long oneHour = (3600000 * timeMultiplier);

long rSecs = 0;
long rMins = 0;
long rHours = 0;

long currentTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.noBlink();
}

void loop() {
  currentTime = millis();
  delay(screenRefreshDelay);

  elapsedSecconds = currentTime / oneSeccond;

  if(elapsedSecconds >= 60) {
    rSecs = elapsedSecconds % 60;
  } else {
    rSecs = elapsedSecconds;
  }

  elapsedMinutes = currentTime / oneMinute;

  if(elapsedMinutes >= 60) {
    rMins = elapsedMinutes % 60;
  } else {
    rMins = elapsedMinutes;
  }

  elapsedHours = currentTime / oneHour;

  if(elapsedHours >= 24) {
    rHours = elapsedHours % 24;
  } else {
    rHours = elapsedHours;
  }
  
  lcd.clear();
  lcd.print("Elapsed: " + String(currentTime));
  lcd.setCursor(0, 2);
  
  lcd.print(String(rHours) + "h, " + String(rMins) + "m, " + String(rSecs) + "s");
}
