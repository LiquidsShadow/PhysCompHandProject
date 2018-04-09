#include <LiquidCrystal.h>

#ifndef LCD_H
#define LCD_H

// ports for lcd 
const int REGISTER_SELECT = 7;
const int ENABLE = 8;
const int DATA4 = 3;
const int DATA5 = 10;
const int DATA6 = 11;
const int DATA7 = 12;

string color = "";

LiquidCrystal lcd(REGISTER_SELECT, ENABLE, DATA4, DATA5, DATA6, DATA7);

enum Mode {
  UserControl,
  Autonomous,
  None
};

Mode selected = None;

void printClr(int colInRow1 = 6) {
  lcd.setCursor(colInRow1, 1);
  lcd.print(color);
}

// MAY NEED TO EDIT DELAY HERE OR ADD ANOTHER? 
void nunchuckCycle() {
  if (nunchuk_read()) {
    if (nunchuk_buttonC()) {
      if (color == "red") {
        color = "blue";
        printClr();
      }
      else if (color == "blue") {
        color = "green";
        printClr(5);
      }
      else {
        color = "red";
        printClr();
      }
      delay(1000);
    }
    else if (nunchuk_buttonZ) {
      runAutonomous();
    }
  }
}

void nunchuckClrCycle() {
  int clrIdx = 0; 
  bool done = false; 
  Serial.print("Initiated Nunchuck Color Cycle..\n");
  while (!done) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Next[C] Enter[Z]");
    printClr();
    waitForNunchuckPress();
    if (nunchuk_buttonC() == 1) {
      waitForNunchuckRelease(); 
      if (clrIdx == 3)
        clrIdx = 0;
      else
        clrIdx++;
      color = colors[clrIdx];
     }
     else if (nunchuk_buttonZ() == 1) {
        waitForNunchuckRelease();
        if (color == "exit") {
          done = true;
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Exited color");
          lcd.setCursor(3,1);
          lcd.print("selection!");
          delay(2000);
        }
        else { 
          runAutonomous(); 
          delay(2000);
        }
     }
     
  }
}


void runSelectionMode() {
    Serial.print("Initiated Selection Mode..\n");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Select Mode:");
    lcd.setCursor(0, 1);
    lcd.print("User[C] Auton[Z]");
    waitForNunchuckPress(); 
    if (nunchuk_buttonC() == 1){
      waitForNunchuckRelease(); 
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Selected:");
      lcd.setCursor(2, 1);
      lcd.print("User Control");
      selected = UserControl;
    }
    else if (nunchuk_buttonZ() == 1) {
      waitForNunchuckRelease(); 
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Selected:");
      lcd.setCursor(3, 1);
      lcd.print("Autonomous");
      selected = Autonomous;
      delay(2500);
      lcd.clear();
      //nunchuckClrCycle();
      buttonClrCycle();
    }

  lcd.clear(); 
  Serial.print("Completed Selection Mode..\n");
}

#endif
