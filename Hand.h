#include <Servo.h>

#ifndef Hand_H
#define Hand_H

// purple tower pro mg91 digital max = 170, min = 15

class Hand {
private:
  Servo fingersServo;
  Servo thumbServo;
  static int calcStep(int, int, int, int, int);
  static void moveServo(Servo, long, int);
public:
  Hand();
  ~Hand();
  void setUp(int, int);
  void moveHand(long, long, int);
  void moveFingers(long, int);
  void moveThumb(long, int);
  void openHand(int);
  void closeHand(int);
};

// helper method to determine step used by moveHand() and functions like it if need be 
int Hand::calcStep(int curr, int dest, int buf = 10, int smallStep = 1, int largeStep = 2) {
  if (curr > dest) {
    if (curr < dest + buf)
      return curr - smallStep;
    return curr - largeStep;
  }
  else {
    if (curr > dest - buf) 
      return curr + smallStep;
    return curr + largeStep;
  }
}

Hand::Hand() {
  Serial.println("Hand created");
}

Hand::~Hand() {
  Serial.println("Hand destroyed");
}

void Hand::setUp(int portFingers, int portThumb) {
  Serial.print("Attempting to attach servos.. ");
  fingersServo.attach(portFingers);
  thumbServo.attach(portThumb);
  Serial.println("Done");
}

void Hand::moveHand(long destFingers, long destThumb, int delayTime) {
  int fingersPos = fingersServo.read(); 
  int thumbPos = thumbServo.read();
  while (fingersPos != destFingers || thumbPos != destThumb) {
    fingersPos = calcStep(fingersPos, destFingers);
    thumbPos = calcStep(thumbPos, destThumb);
    fingersServo.write(fingersPos);
    thumbServo.write(thumbPos);
    delay(delayTime);

    // Servo debug stuff 
    Serial.println("\n--- Fingers ---");
    Serial.print(fingersPos);
    Serial.print("->");
    Serial.print(destFingers);
    Serial.println("\n--- Thumb ---");
    Serial.print(thumbPos);
    Serial.print("->");
    Serial.println(destThumb);
  } 
}

void Hand::moveServo(Servo servo, long dest, int tDelay) {
  int pos = servo.read();
  while (pos != dest) {
    pos = calcStep(pos, dest);
    servo.write(pos);
    delay(tDelay);

    Serial.print(pos);
    Serial.print("->");
    Serial.println(dest);
  }
}

void Hand::moveFingers(long dest, int tDelay = 10) {
  Serial.print("Attemping to move fingers.. ");
  moveServo(fingersServo, dest, tDelay);
  Serial.println("Done");
}

void Hand::moveThumb(long dest, int tDelay = 10) {
  Serial.print("Attempting to move thumb.. ");
  moveServo(thumbServo, dest, tDelay);
  Serial.println("Done");
}

void Hand::openHand(int tDelay = 10) {
  Serial.print("Attempting to open hand.. ");
  moveHand(170, 90, tDelay);
  Serial.println("Done");
}

void Hand::closeHand(int tDelay = 10) {
  Serial.print("Attempting to close hand.. ");
  moveHand(15, 20, tDelay);
  Serial.println("Done");
}

#endif 
