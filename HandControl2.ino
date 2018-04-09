#include <Servo.h>

#include "ButtonAndLED.h"
#include "Nunchuck.h"

// *NOTE* these are servos for the device being operated by the nunchuck (i.e. the hand)
// servos for the Pixy are controlled in ServoLoop using setServos() function Pixy class
Servo servoFB; // forward backward
Servo servoLR; // left right
Servo servoOC; // open close

const int SERVO_OC_PORT = 9;

void nunChuckLoop()
{
  if (nunchuk_read()) {

  // map nunchuk data to a servo data point
    int x_axis = map(nunchuk_data[0], 23, 222, 180, 0);
    int y_axis = map(nunchuk_data[1], 32, 231, 0, 180);
  
    if (nunchuk_buttonC()) {
      openHand();
    }
    else if (nunchuk_buttonZ()) {
      grab();
    }
  // un-comment next line to print data to serial monitor  
   //nunchuk_print();          
   }
}

// gradual servo movement -> think this would prevent "drift"
void moveByStepTo(Servo servo, int destination) {
  int curr = servo.read(); 
  while (curr < destination || curr > destination) {
    if (curr > destination)
      if (curr < destination + 10)
        curr -= 1;
      else
        curr -= 2;
    else 
      if (curr > destination - 10)
        curr += 1;
      else
        curr += 2;
    servo.write(curr);
    delay(10);
    
    Serial.print(curr);
    Serial.print("->");
    Serial.print(destination);
    Serial.print("\n");
  }
}

/*
 * function to open hand 
 */
void openHand() {
  Serial.print("Opening hand..");
  moveByStepTo(servoOC, 180);
  
}

/*
 * function to grab
 */
void grab() {
  Serial.print("Closing hand..");
  moveByStepTo(servoOC, 0);
}

void runAutonomous() { // use global variable "color" & use pantilt demo 
  Serial.print("Running Autonomous on color: ");
  Serial.print("Exiting Autonomous, handing back to nunChuckCycle()");
}

void setup() {
    //pixy.init();
    Serial.begin(9600);
    Serial.print("TEST");
    Wire.begin();
    //lcd.begin(16, 2);
    //servoOC.attach(9);
    servoOC.attach(SERVO_OC_PORT);
    setUpBtnAndLED();
    // nunchuk_init_power(); // A1 and A2 is power supply
    nunchuk_init();
    nunchuk_read();// get rid of c being pushed
    Serial.print("Set-up complete...\n");
}
void loop() {
  nunChuckLoop();
//  if (nunchuk_read()) 
//    nunchuk_print();
//  delay(10);
}
