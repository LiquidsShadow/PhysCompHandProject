#include <Servo.h>
#include "Nunchuck.h"
#include "Hand.h"

Hand hand; // fingers 9 thumb 10
Servo test;
void nunChuckLoop()
{
  if (nunchuk_read()) {

  // map nunchuk data to a servo data point -> use for moving the arm 
//    int x_axis = map(nunchuk_data[0], 23, 222, 180, 0);
//    int y_axis = map(nunchuk_data[1], 32, 231, 0, 180);
  
    if (nunchuk_buttonC()) {
      hand.openHand();
    }
    else if (nunchuk_buttonZ()) {
      hand.closeHand();      
    }
  // un-comment next line to print data to serial monitor  
   //nunchuk_print();          
   }
}

void setup() {
    Serial.println("Initiated set-up...\n");
    Serial.begin(9600);
    Wire.begin();
    //hand.setUp(9, 10);
    test.attach(9);
    nunchuk_init();
    nunchuk_read();// get rid of c being pushed at start
    Serial.println("\nSet-up complete...\n");
}
void loop() {
  //nunChuckLoop();
//  hand.openHand();
//  delay(1000);
//  hand.closeHand();
//  delay(1000);
    test.write(115);
    delay(1200);
    Serial.println(test.read());
    test.write(25);
    delay(1200);
    Serial.println(test.read());
// Nunchuck debug stuff 
//  if (nunchuk_read()) 
//    nunchuk_print();
//  delay(10);
  
}
