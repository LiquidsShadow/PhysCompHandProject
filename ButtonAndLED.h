String colors[] = {"blue","green","red","exit"};
String color = "red";

const int BUTTON_PIN = 13;
const int BLUE_PIN = 4;
const int RED_PIN = 6;
const int GREEN_PIN = 5;

const int HOLD_TIME_S = 3; 

void setUpBtnAndLED() {
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void waitForButtonPress() {
  while (digitalRead(BUTTON_PIN) != HIGH) {delay(5);}
}

void ledToClr() {
  if (color == "red") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
  else if (color == "blue") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
  }
  else if (color == "green") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
  }
  else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
}

void flashLED() {
  for (int i = 0; i < 10; i++) {
    if (color != "exit") {
      ledToClr();
      delay(100);
    }
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    delay(100);
  }
  ledToClr();
}

//https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-3-driving-an-rgb-led

// not in final -> meant for debugging purposes 
void buttonClrCycle() {
//  lcd.setCursor(1, 0);
//  lcd.print("Click to cycle");
//  lcd.setCursor(1, 1);
//  lcd.print("Hold to choose");
  ledToClr();
  Serial.begin(19200);
  int clrIdx = 0; 
  bool done = false;
  while (!done) {
    waitForButtonPress(); 
    int secondsHeld = 0;
    while (digitalRead(BUTTON_PIN) == HIGH && secondsHeld < HOLD_TIME_S) {
      delay(1000);
      secondsHeld++; 
    }
    done = secondsHeld == HOLD_TIME_S;
    if (!done) {
      if (clrIdx == 3)
        clrIdx = 0;
      else
        clrIdx++;
      color = colors[clrIdx];
      ledToClr();
    }
    else {
      flashLED();
    }
  }
}
