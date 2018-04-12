#include <Servo.h>

#ifndef VexMotor_H
#define VexMotor_H

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

