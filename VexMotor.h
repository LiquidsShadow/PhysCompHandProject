#ifndef VexMotor_H
#define VexMotor_h

class VexMotor {
  int pin;
  public:
    VexMotor(int p) {
      pinMode(pin, INPUT);
    }
    void startMotor() {
      digitalWrite(pin, HIGH); 
    }
    void stopMotor() {
      digitalWrite(pin, LOW);
    }
};

#endif 

