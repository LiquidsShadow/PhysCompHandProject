#include <Servo.h>

#ifndef VexMotor_H
#define VexMotor_H

// gradual servo movement -> think this would prevent "drift"
void moveByStepTo(Servo aServo, long destination) {
  int curr = aServo.read(); 
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
    aServo.write(curr);
    delay(10);
    
    Serial.print(curr);
    Serial.print("->");
    Serial.print(destination);
    Serial.print("\n");
  } 
}

class VexMotor {
  Servo servo;
  public:
    VexMotor(int pin) {
      servo.attach(pin);
    }
    ~VexMotor() {
      servo.detach();
      Serial.print("VexMotor object deleted.");
    }
    void moveTo(long dest) {
      servo.write(map(dest, -255, 255, 1000, 2000));
    }
};

#endif 

