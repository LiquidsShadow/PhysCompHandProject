#include <Servo.h>

#include "ButtonAndLED.h"
#include "Nunchuck.h"

// *NOTE* these are servos for the device being operated by the nunchuck (i.e. the hand)
// servos for the Pixy are controlled in ServoLoop using setServos() function Pixy class
Servo fingersServo;
Servo thumbServo;

const short FINGERS_SERVO_PORT = 9;
const short THUMB_SERVO_PORT = 10;

int calcOutput(int curr, int dest) {
  if (curr > dest) {
    if (curr < dest + 10)
      return curr - 1;
    return curr - 2;
  }
  else {
    if (curr > dest - 10) 
      return curr + 1;
    return curr + 2;
  }
}

// gradual servo movement -> think this would prevent "drift"
void moveHand(long destFingers, long destThumb, int delayTime = 10) {
  int fingersPos = fingersServo.read(); 
  int thumbPos = thumbServo.read();
  while ((fingersPos < destFingers || fingersPos > destFingers) || (thumbPos < destThumb || thumbPos > destThumb)) {
    fingersPos = calcOutput(fingersPos, destFingers);
    thumbPos = calcOutput(thumbPos, destThumb);
    fingersServo.write(fingersPos);
    thumbServo.write(thumbPos);
    delay(delayTime);

    Serial.print("--- Fingers ---");
    Serial.print(fingersPos);
    Serial.print("->");
    Serial.print(destFingers);
    Serial.print("\n");
    Serial.print("--- Thumb ---");
    Serial.print(thumbPos);
    Serial.print("->");
    Serial.print(destThumb);
    Serial.print("\n\n");
  } 
}

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
  moveHand(180, 90);
}

/*
 * function to grab
 */
void grab() {
  Serial.print("Closing hand..");
  moveHand(0, 0);
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
    fingersServo.attach(FINGERS_SERVO_PORT);
    thumbServo.attach(THUMB_SERVO_PORT);
    setUpBtnAndLED();
    nunchuk_init();
    nunchuk_read();// get rid of c being pushed at start
    Serial.print("\nSet-up complete...\n");
}
void loop() {
  nunChuckLoop();
//  if (nunchuk_read()) 
//    nunchuk_print();
//  delay(10);
  
}
