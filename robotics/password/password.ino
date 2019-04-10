#include <LiquidCrystal.h>
#include <Keypad.h>

const byte numRows= 4;
const byte numCols = 4;
char keymap[numRows][numCols]= { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[numRows] = {13, 12, 11, 10};
byte colPins[numCols]= {9, 8, 7, 6};

String password = "";
const String chars = "";
const String lastkey = "";

LiquidCrystal lcd(5, 4, 3, 2, 1, 0);
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  lcd.begin(16, 2);
  lcd.noBlink();
}

void loop() {
  delay(100);
  lcd.clear();
  char keypressed = myKeypad.getKey();

  if (keypressed != NO_KEY) {lastkey = keypressed;}

  if(lastkey == "*") {
    password = "";
    chars = "";
    lastkey = "";
    delay(500);
    lcd.print("################");
    lcd.setCursor(0, 2);
    lcd.print("################");
    delay(500);
    
  } else if(lastkey == "warn") {
    password = "";
    chars = "";
    lastkey = "";
    lcd.print("That password is");
    lcd.setCursor(0, 2);
    lcd.print("too long(Max 16)");
    delay(3500);
    
  } else {
    if(password == "") {
      if(lastkey == "C") {
        lcd.print("Password saved!");
        password = chars;
        delay(1500);
        chars = "";
        lastkey = "";
      } else if(lastkey == "D") {
        chars = "";
        lastkey = "";
      } else {
        lcd.print("Type a pass:");
        if (keypressed != NO_KEY) {
          if(chars.length() >= 16) {
            lastkey = "warn";
          } else {
            chars = chars + keypressed;
          }
        }
        lcd.setCursor(0, 2);
        lcd.print(chars);
      }
    } else {
      if(lastkey == "C") {
        if((chars != "") && (chars != password)) {
          lcd.print("Wrong password!");
        } else if((chars != "") && (chars == password)) {
          lcd.print("Welcome!");
        }
      } else if(lastkey == "D") {
        chars = "";
        lastkey = "";
      } else {
        lcd.print("Password:");
        if (keypressed != NO_KEY) {
          chars = chars + keypressed;
        }
        lcd.setCursor(0, 2);
        lcd.print(chars);
      }
    }
  }
}
