#include <Servo.h>




Servo highX;
Servo highY;
Servo lowX;
Servo lowY;

void setup() {
  Serial1.begin(14400);
  Serial.begin(9600);
  highX.attach(2);
  highY.attach(3);
  lowX.attach(4);
  lowY.attach(5);
  delay(1000);
  highX.write(35);
  highY.write(35);
  lowX.write(35);
  lowY.write(35);
  Serial.println("initialized servos");
}

void loop(){
  int highXVal, highYVal, lowXVal, lowYVal;
  highXVal = 35;
  highYVal = 35;
  lowXVal = 35;
  lowYVal = 35;
  highX.write(highXVal);
  highY.write(highYVal);
  lowX.write(lowXVal);
  lowY.write(lowYVal);
  delay(5000);
  
  while(highXVal < 80){
    highXVal += 10;
    highYVal += 10;
    lowXVal += 10;
    lowYVal += 10;
    highX.write(highXVal);
    highY.write(highYVal);
    lowX.write(lowXVal);
    lowY.write(lowYVal);
    delay(5000);
  }
  
}
