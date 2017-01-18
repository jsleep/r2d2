#include <Wire.h>
#include <Servo.h>

volatile byte command = 0;
volatile boolean reset = false;

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
const int L1 = 40;
const int M1 = 50;
const int H2 = 120;
const int L2 = 42;
const int M2 = 53;
const int H3 = 130;
const int L3 = 58;
const int M3 = 68;
const int H4 = 95;
const int L4 = 39;
const int M4 = 52;
const int H5 = 95;
const int L5 = 35;
const int M5 = 52;
const int H6 = 160;
const int L6 = 85;
const int M6 = 100;
const int H7 = 162;
const int L7 = 85;
const int M7 = 110;
const int H8 = 127;
const int L8 = 60;
const int M8 = 78;
const int H9 = 135;
const int L9 = 77;
const int M9 = 92;
const int H10 = 140;
const int L10 = 72;
const int M10 = 94;

int pos = 0;    // variable to store the servo position

void setup (void)
{

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Serial1.begin(9600);
  

  Serial.println("I have started");
  servo1.attach(A0);
  servo2.attach(A1);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  servo8.attach(9);
  servo9.attach(10);
  servo10.attach(11);  

  delay(1000);
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
  delay(1000);
  servo1.write(M1);
  servo2.write(M2);
  servo3.write(M3);
  servo4.write(M4);
  servo5.write(M5);
  servo6.write(M6);
  servo7.write(M7);
  servo8.write(M8);
  servo9.write(M9);
  servo10.write(M10);
  delay(1000);
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
  delay(1000);

}  // end of setup

void loop (void)
{
  reset = false;
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
  bool delay_bool = false;
  Serial.println(command);
  if(command >= 1 && command <= 16) {
    servo1.attach(A0);
    servo2.attach(A1);
    servo3.attach(4);
    servo4.attach(5);
    servo5.attach(6);
    servo6.attach(7);
    servo7.attach(8);
    servo8.attach(9);
    servo9.attach(10);
    servo10.attach(11);
    delay_bool = true;  
  }
  if(command==1){
    delay(130);
    servo1.write(H1);
    delay(180);
    servo1.write(M1);
    servo2.write(H2);
    delay(250);
    servo1.write(H1);
    servo2.write(M2);
    servo3.write(H3);
    delay(260);
    servo2.write(H2);
    servo3.write(M3);
    servo4.write(H4);
    delay(280);
    servo3.write(H3);
    servo4.write(M4);
    servo6.write(H6);
    delay(100);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    servo4.write(H4);
    servo6.write(M6);    
    servo7.write(H7);
    delay(300);
    servo6.write(H6);    
    servo7.write(M7);
    servo8.write(H8);
    delay(300);
    servo7.write(H7);
    servo8.write(M8);
    servo9.write(H9);
    delay(100);
    servo8.write(H8);
    servo9.write(M9);
    servo10.write(H10);
    delay(400);
    ALL_PANELS_MINIMUM();
    delay(200);
    ALL_PANELS_OPEN();
    delay(800);
    ALL_PANELS_MINIMUM();
    delay(250);
    ALL_PANELS_CLOSE();
  }
  else if(command==2){
    ALL_PANELS_OPEN();
    delay(600);
    ALL_PANELS_MINIMUM();
    delay(340);
    CLOCKWISE_OPENCLOSE(50);
    delay(60);
    servo10.write(M10);
    CLOCKWISE_OPEN(50);
    delay(200);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    ODD_PANELS_CLOSE();
    delay(250);
    EVEN_PANELS_CLOSE();
    delay(250);
    ALL_PANELS_CLOSE();
  }
  else if(command==3){
    servo2.write(H2);
    servo10.write(H10);
    delay(600);
    servo2.write(M2);
    servo4.write(H4);
    delay(400);
    servo7.write(H7);
    servo4.write(M4);
    delay(800);
    servo10.write(M10);
    servo9.write(H9);
    delay(500);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    servo3.write(H3);
    delay(350);
    servo3.write(M3);
    servo9.write(M9);
    delay(400);
    servo8.write(H8);
    delay(550);
    ALL_PANELS_MINIMUM();
    delay(450);
    ALL_PANELS_RAMP();
    delay(100);
    
    ALL_PANELS_CLOSE();
  }
  else if(command==4){
    CLOCKWISE_OPENCLOSE(10);
    CLOCKWISE_OPENCLOSE(20);
    CLOCKWISE_OPENCLOSE(30);
    CLOCKWISE_OPENCLOSE(50);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    EVEN_PANELS_OPEN();
    delay(5000);
    ALL_PANELS_MINIMUM();
    delay(250);
    ALL_PANELS_CLOSE();
  }
  else if(command==5){
    ODD_PANELS_OPEN();
    delay(1200);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    ODD_PANELS_CLOSE();
    delay(250);
    ALL_PANELS_CLOSE();
  }
  else if(command==6){
    BOTTOM_PANELS_OPEN();
    delay(300);
    TOP_PANELS_OPEN();
    delay(3500);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    ALL_PANELS_MINIMUM();
    delay(250);
    ALL_PANELS_CLOSE();
  }
  else if(command==7){
    ALL_PANELS_RAMP();
    delay(250);
    ALL_PANELS_CLOSE();
  }
  else if(command==8){
    Serial1.print("0T4\r");
    CLOCKWISE_OPEN(80);
    delay(250);
    ALL_PANELS_MINIMUM();
    delay(400);
    ALL_PANELS_RAMP();
    delay(350);
    BOTTOM_PANELS_OPEN();
    delay(600);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    BOTTOM_PANELS_CLOSE();
    TOP_PANELS_OPEN();
    delay(900);
    servo1.write(H1);
    delay(130);
    servo2.write(H2);
    delay(150);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    servo3.write(H3);
    delay(150);
    servo4.write(H4);
    delay(200);
    ALL_PANELS_MINIMUM();
    delay(500);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    CLOCKWISE_OPENCLOSE(70);
    CLOCKWISE_OPENCLOSE(60);
    CLOCKWISE_OPENCLOSE(50);
    CLOCKWISE_OPENCLOSE(40);
    CLOCKWISE_OPENCLOSE(30);
    CLOCKWISE_OPENCLOSE(20);
    CLOCKWISE_OPENCLOSE(20);
    CLOCKWISE_OPENCLOSE(10);
    ODD_PANELS_OPEN();
    delay(3000);
    safeClose();
    
    
  }
  else if(command==9){
    //alarm command
    //send alarm to 
    Serial1.print("0T3\r");
    CLOCKWISE_OPEN(80);
    delay(350);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    ALL_PANELS_MINIMUM();
    delay(200);
    ALL_PANELS_CLOSE();
  }
  else if(command==10){
    delay(350);
    ODD_PANELS_OPEN();
    delay(250);
    ODD_PANELS_CLOSE();
    EVEN_PANELS_OPEN();
    delay(200);
    if(reset == true) {
        safeClose();
        delay(1000);
        return;
    }
    ALL_PANELS_MINIMUM();
    delay(200);
    CLOCKWISE_OPENCLOSE(50);
    delay(30);
    ALL_PANELS_MINIMUM();
    delay(100);
    ALL_PANELS_CLOSE();
  }
  else if(command==11){
    Serial1.print("0T6\r");
  }
  else if(command==14){
    delay(100);
    Serial1.print("0T11\r");
  }
  else if(command==15){
    ALL_PANELS_OPEN();
  }
  
  else if (command==16){
    Serial1.print("RESET\r");
    safeClose();
  }
  
  if (delay_bool == true) {
    delay(1000);
  }
  command = 0;
  
}  // end of loop

// I2C interrupt routine
/*void receiveHandler(int numBytes)
{
    Serial.println("Received Handler hit");
    Serial.print("numBytes");
    Serial.println(numBytes,DEC);
    command = (byte)Wire.parseInt();
    while(Wire.available()) {
        Wire.read();
    }
    Serial.print("Got command ");
    Serial.println(command,DEC);
}  

void requestHandler() 
{
    Serial.println("Request Handler hit");
    Wire.write(command);
}*/

void safeClose() {
    ALL_PANELS_MINIMUM();
    delay(200);
    ALL_PANELS_CLOSE();
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    //Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer
  command = x;
  if (command == 255) {
    Serial1.print("0T1\r");
    reset = true;
  }
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
 void ALL_PANELS_MINIMUM() {
    servo1.write(M1);
    servo2.write(M2);
    servo3.write(M3);
    servo4.write(M4);
    servo5.write(M5);
    servo6.write(M6);
    servo7.write(M7);
    servo8.write(M8);
    servo9.write(M9);
    servo10.write(M10);
 }
 
 void CLOCKWISE_OPENCLOSE(int time) {
   servo1.write(H1);
   delay(time);
   servo10.write(M10);
   servo2.write(H2);
   delay(time);
   servo1.write(M1);
   servo3.write(H3);
   delay(time);
   servo2.write(M2);
   servo4.write(H4);
   delay(time);
   servo3.write(M3);
   servo5.write(H5);
   delay(time);
   servo4.write(M4);
   servo6.write(H6);
   delay(time);
   servo5.write(M5);
   servo7.write(H7);
   delay(time);
   servo6.write(M6);
   servo8.write(H8);
   delay(time);
   servo7.write(M7);
   servo9.write(H9);
   delay(time);
   servo8.write(M8);
   servo10.write(H10);
   delay(time);
   servo9.write(M9);
 }
 
void CLOCKWISE_OPEN(int time) {
    servo1.write(H1);
    delay(time);
    servo2.write(H2);
    delay(time);
    servo3.write(H3);
    delay(time);
    servo4.write(H4);
    delay(time);
    servo5.write(H5);
    delay(time);
    servo6.write(H6);
    delay(time);
    servo7.write(H7);
    delay(time);
    servo8.write(H8);
    delay(time);
    servo9.write(H9);
    delay(time);
    servo10.write(H10);
 }

void COUNTERCLOCKWISE_OPEN(int time) {
  servo10.write(H10);
  delay(time);
  servo9.write(H9);
  delay(time);
  servo8.write(H8);
  delay(time);
  servo7.write(H7);
  delay(time);
  servo6.write(H6);
  delay(time);
  servo5.write(H5);
  delay(time);
  servo4.write(H4);
  delay(time);
  servo3.write(H3);
  delay(time);
  servo2.write(H2);
  delay(time);
  servo1.write(H1);
}

void ODD_PANELS_OPEN() {
  servo1.write(H1);
  servo3.write(H3);
  servo5.write(H5);
  servo7.write(H7);
  servo9.write(H9);
}

void ODD_PANELS_CLOSE() {
  servo1.write(M1);
  servo3.write(M3);
  servo5.write(M5);
  servo7.write(M7);
  servo9.write(M9);
}

void EVEN_PANELS_OPEN() {
  servo2.write(H2);
  servo4.write(H4);
  servo6.write(H6);
  servo8.write(H8);
  servo10.write(H10);
}

void EVEN_PANELS_CLOSE() {
  servo2.write(M2);
  servo4.write(M4);
  servo6.write(M6);
  servo8.write(M8);
  servo10.write(M10);
}

void TOP_PANELS_OPEN() {
  servo6.write(H6);
  servo7.write(H7);
  servo8.write(H8);
  servo9.write(H9);
  servo10.write(H10);
}

void TOP_PANELS_CLOSE() {
  servo6.write(M6);
  servo7.write(M7);
  servo8.write(M8);
  servo9.write(M9);
  servo10.write(M10);
}

void BOTTOM_PANELS_OPEN() {
  servo1.write(H1);
  servo2.write(H2);
  servo3.write(H3);
  servo4.write(H4);
  servo5.write(H5);
}

void BOTTOM_PANELS_CLOSE() {
  servo1.write(M1);
  servo2.write(M2);
  servo3.write(M3);
  servo4.write(M4);
  servo5.write(M5);
}

void ALL_PANELS_RAMP() {
  int i;
  for(i=30; i < 100; i++) {
    servo1.write(i);
    servo2.write(i);
    servo3.write(i+10);
    servo4.write(i);
    servo5.write(i);
    servo6.write(i+15);
    servo7.write(i+15);
    servo8.write(i-5);
    servo9.write(i+5);
    servo10.write(i+5);
    delay(5);
  }
  for(i=100; i > 30; i--) {
    servo1.write(i);
    servo2.write(i);
    servo3.write(i+10);
    servo4.write(i);
    servo5.write(i);
    servo6.write(i+15);
    servo7.write(i+15);
    servo8.write(i-5);
    servo9.write(i+5);
    servo10.write(i+5);
    delay(5);
  }
}


