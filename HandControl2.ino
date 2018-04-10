#include <Servo.h>

#include "ButtonAndLED.h"
#include "Nunchuck.h"
#include "VexMotor.h"

// *NOTE* these are servos for the device being operated by the nunchuck (i.e. the hand)
// servos for the Pixy are controlled in ServoLoop using setServos() function Pixy class
Servo servoOC; // open close

const int SERVO_OC_PORT = 9;
const int VEX_FB_PORT = 10;
VexMotor forwardBackward(VEX_FB_PORT);

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
    Serial.print("Initiated set-up...\n");
    Serial.begin(9600);
    Wire.begin();
    servoOC.attach(SERVO_OC_PORT);
    setUpBtnAndLED();
    nunchuk_init();
    nunchuk_read();// get rid of c being pushed at start
    Serial.print("\nSet-up complete...\n");
}
void loop() {
   forwardBackward.moveTo(0);
   delay(3000);
   forwardBackward.moveTo(180);
   delay(3000);
  //nunChuckLoop();
//  if (nunchuk_read()) 
//    nunchuk_print();
//  delay(10);
  
}
