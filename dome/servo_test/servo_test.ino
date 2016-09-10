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

void loop() {
  int highXVal, highYVal, lowXVal, lowYVal;
  byte inChar;
  highXVal = 50;
  highYVal = 50;
  lowXVal = 50;
  lowYVal = 50;
  highX.write(highXVal);
  highY.write(highYVal);
  lowX.write(lowXVal);
  lowY.write(lowYVal);
  // check for incoming serial data:
  
  while(true){
    while (Serial.available() == 0) {}
    Serial.println("I'm here for you");
    // read incoming serial data:
    inChar = Serial.read();
    if(inChar == 'a'){
        Serial.println("You pressed a, sexy man");
        highXVal += 10;
        Serial.print("highXVal: ");
        Serial.println(highXVal);
        highX.write(highXVal);
        Serial.println("fuck yeah!");
    }
  
    else if(inChar == 'z'){
        highXVal -= 10;
        Serial.print("highXVal: ");
        Serial.println(highXVal);
        highX.write(highXVal);
        Serial.println("fuck yeah!");
      }
    else if(inChar == 'q'){
        highXVal = 50;
        Serial.print("highXVal: ");
        Serial.println(highXVal);
        highX.write(highXVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 's'){
        highYVal += 5;
        Serial.print("highYVal: ");
        Serial.println(highYVal);
        highY.write(highYVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'x'){
        highYVal -= 5;
        highY.write(highYVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'w'){
        highYVal = 0;
        highY.write(highYVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'd'){
        lowXVal += 10;
        Serial.print("lowXVal: ");
        Serial.println(lowXVal);
        lowX.write(lowXVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'c'){
        lowXVal -= 10;
        Serial.print("lowXVal: ");
        Serial.println(lowXVal);
        lowX.write(lowXVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'e'){
        lowXVal = 50;
        Serial.print("lowXVal: ");
        Serial.println(lowXVal);
        lowX.write(lowXVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'f'){
        lowYVal += 20;
        lowY.write(lowYVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'v'){
        lowYVal -= 20;
        lowY.write(lowYVal);
        Serial.println("fuck yeah!");
    }
    else if(inChar == 'r'){
        lowYVal = 20;
        lowY.write(lowYVal);
        Serial.println("fuck yeah!");
    }
  
  
    delay(1000);
  }
 
}
