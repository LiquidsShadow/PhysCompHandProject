#include <Servo.h>
#include "Nunchuck.h"

Servo fingersServo;
Servo thumbServo;

const short FINGERS_SERVO_PORT = 9;
const short THUMB_SERVO_PORT = 10;

// helper method to determine step used by moveHand() and functions like it if need be 
int calcStep(int curr, int dest) {
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

// gradual servo movement -> think this would prevent "drift", anyways it's what people seem to do
void moveHand(long destFingers, long destThumb, int delayTime = 10) {
  int fingersPos = fingersServo.read(); 
  int thumbPos = thumbServo.read();
  while ((fingersPos < destFingers || fingersPos > destFingers) || (thumbPos < destThumb || thumbPos > destThumb)) {
    fingersPos = calcStep(fingersPos, destFingers);
    thumbPos = calcStep(thumbPos, destThumb);
    fingersServo.write(fingersPos);
    thumbServo.write(thumbPos);
    delay(delayTime);

    // Servo debug stuff 
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

  // map nunchuk data to a servo data point -> use for moving the arm 
//    int x_axis = map(nunchuk_data[0], 23, 222, 180, 0);
//    int y_axis = map(nunchuk_data[1], 32, 231, 0, 180);
  
    if (nunchuk_buttonC()) {
      Serial.print("Opening hand..");
      moveHand(180, 90);
    }
    else if (nunchuk_buttonZ()) {
      Serial.print("Closing hand..");
      moveHand(0, 0);
    }
  // un-comment next line to print data to serial monitor  
   //nunchuk_print();          
   }
}

void setup() {
    Serial.print("Initiated set-up...\n");
    Serial.begin(9600);
    Wire.begin();
    fingersServo.attach(FINGERS_SERVO_PORT);
    thumbServo.attach(THUMB_SERVO_PORT);
    nunchuk_init();
    nunchuk_read();// get rid of c being pushed at start
    Serial.print("\nSet-up complete...\n");
}
void loop() {
  nunChuckLoop();
// Nunchuck debug stuff 
//  if (nunchuk_read()) 
//    nunchuk_print();
//  delay(10);
  
}
