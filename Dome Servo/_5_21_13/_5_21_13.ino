#include <Servo.h>



#include <Servo.h>
 
Servo servo1;  // create servo object to control a servo
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;// a maximum of eight servo objects can be created

const int H1 = 110;
const int L1 = 33;
const int H2 = 120;
const int L2 = 39;
const int H3 = 130;
const int L3 = 60;
const int H4 = 95;
const int L4 = 42;
const int H5 = 95;
const int L5 = 42;
const int H6 = 70;
const int L6 = 30;
const int H7 = 70;
const int L7 = 30;
const int H8 = 70;
const int L8 = 30;
const int H9 = 70;
const int L9 = 30;
const int H10 = 70;
const int L10 = 30;

int pos = 0;    // variable to store the servo position
 
void setup()
{
  Serial1.begin(14400);
  Serial.begin(9600);
  while(!Serial1){;}
  Serial.println("I have started");
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  servo8.attach(9);
  servo9.attach(10);
  servo10.attach(11);  

  servo1.write(L1);
  servo2.write(L2);
  servo3.write(L3);
  servo4.write(L4);
  servo5.write(L5);
  servo6.write(L6);
  servo7.write(L7);
  servo8.write(L8);
  servo9.write(L9);
  servo10.write(L10);
  delay(3000);
}
 
 
void loop()
{
  int command;
  command=20;
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();
  servo5.detach();
  servo6.detach();
  servo7.detach();
  servo8.detach();
  servo9.detach();
  servo10.detach();
  while(command>11 || command<1){
  command = Serial1.read();
  Serial.println(command);
  Serial.println("proper");
  }
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  servo8.attach(9);
  servo9.attach(10);
  servo10.attach(11); 
  Serial.println("I'm here");

  Serial.println(command);
  if(command==3){
    servo1.write(H1);
    servo2.write(H2);
    servo3.write(H3);
    servo4.write(H4);
    servo5.write(H5);
    servo6.write(H6);
    servo7.write(H7);
    servo8.write(H8);
    servo9.write(H9);
    servo10.write(H10);  
  }
  else if(command==1){
    servo1.write(L1);
    servo2.write(L2);
    servo3.write(L3);
    servo4.write(L4);
    servo5.write(L5);
    servo6.write(L6);
    servo7.write(L7);
    servo8.write(L8);
    servo9.write(L9);
    servo10.write(L10); 
  }
  else if(command==2){
    delay(130);
    servo1.write(H1);
    delay(180);
    servo1.write(L1);
    servo2.write(H2);
    delay(250);
    servo1.write(H1);
    servo2.write(L2);
    servo3.write(H3);
    delay(260);
    servo2.write(H2);
    servo3.write(L3);
    servo4.write(H4);
    delay(280);
    servo3.write(H3);
    servo4.write(L4);
    servo6.write(H6);
    delay(100);
    servo4.write(H4);
    servo6.write(L6);    
    servo7.write(H7);
    delay(300);
    servo6.write(H6);    
    servo7.write(L7);
    servo8.write(H8);
    delay(300);
    servo7.write(H7);
    servo8.write(L8);
    servo9.write(H9);
    delay(100);
    servo8.write(H8);
    servo9.write(L9);
    servo10.write(H10);
    delay(400);
    ALL_PANELS_CLOSE();
    delay(200);
    ALL_PANELS_OPEN();
    delay(800);
    ALL_PANELS_CLOSE();
    
  }
  else if(command==4){
  }
  else if(command==5){
  }
  else if(command==6){
  }
  else if(command==7){
  }
  else if(command==8){
  }
  else if(command==9){
  }
  else if(command==10){
  }
  delay(1000);
  
//  servo6.write(20);
//  delay(5000);
//  servo6.write(90);
//  delay(5000);
//  for(pos = 20; pos < 110; pos += 1)  // goes from 0 degrees to 180 degrees
//  {                                  // in steps of 1 degree
//    servo6.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for(pos = 110; pos>=20; pos-=1)     // goes from 180 degrees to 0 degrees
//  {                                
//    servo6.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}

void ALL_PANELS_OPEN(){
    servo1.write(H1);
    servo2.write(H2);
    servo3.write(H3);
    servo4.write(H4);
    servo5.write(H5);
    servo6.write(H6);
    servo7.write(H7);
    servo8.write(H8);
    servo9.write(H9);
    servo10.write(H10);
}

void ALL_PANELS_CLOSE(){
    servo1.write(L1);
    servo2.write(L2);
    servo3.write(L3);
    servo4.write(L4);
    servo5.write(L5);
    servo6.write(L6);
    servo7.write(L7);
    servo8.write(L8);
    servo9.write(L9);
    servo10.write(L10);
}

