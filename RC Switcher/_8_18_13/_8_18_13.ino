

// MultiChannels
//
// rcarduino.blogspot.com
//
// A simple approach for reading three RC Channels using pin change interrupts
//
// See related posts -
// http://rcarduino.blogspot.co.uk/2012/01/how-to-read-rc-receiver-with.html
// http://rcarduino.blogspot.co.uk/2012/03/need-more-interrupts-to-read-more.html
// http://rcarduino.blogspot.co.uk/2012/01/can-i-control-more-than-x-servos-with.html
//
// rcarduino.blogspot.com
//

// include the pinchangeint library - see the links in the related topics section above for details

#include <PinChangeInt.h>
#include <Servo.h>

// Assign your channel in pins
#define AILE_IN_PIN 8
#define ELEV_IN_PIN 9
#define RUDD_IN_PIN 10
#define GEAR_IN_PIN 3
#define AUX_IN_PIN 2

// Assign your channel out pins
#define AILE_OUT_PIN 5
#define ELEV_OUT_PIN 6
#define RUDD_OUT_PIN 7
#define DMLR_OUT_PIN 11
#define DMUD_OUT_PIN 12

// Servo objects generate the signals expected by Electronic Speed Controllers and Servos
// We will use the objects to output the signals we read in
// this example code provides a straight pass through of the signal with no custom processing
Servo servoAILE;
Servo servoELEV;
Servo servoRUDD;
Servo servoDMLR;
Servo servoDMUD;


// These bit flags are set in bUpdateFlagsShared to indicate which
// channels have new signals
#define AILE_FLAG 1
#define ELEV_FLAG 1
#define RUDD_FLAG 4
#define GEAR_FLAG 8
#define AUX_FLAG 16


// holds the update flags defined above
volatile uint8_t bUpdateFlagsShared;

// shared variables are updated by the ISR and read by loop.
// In loop we immediatley take local copies so that the ISR can keep ownership of the
// shared ones. To access these in loop
// we first turn interrupts off with noInterrupts
// we take a copy to use in loop and the turn interrupts back on
// as quickly as possible, this ensures that we are always able to receive new signals
volatile uint16_t unAILEInShared;
volatile uint16_t unELEVInShared;
volatile uint16_t unRUDDInShared;
volatile uint16_t unGEARInShared;
volatile uint16_t unAUXInShared;

// These are used to record the rising edge of a pulse in the calcInput functions
// They do not need to be volatile as they are only used in the ISR. If we wanted
// to refer to these in loop and the ISR then they would need to be declared volatile
uint32_t ulAILEStart;
uint32_t ulELEVStart;
uint32_t ulRUDDStart;
uint32_t ulGEARStart;
uint32_t ulAUXStart;


void setup()
{
  Serial.begin(9600);

  Serial.println("multiChannels");

  // attach servo objects, these will generate the correct
  // pulses for driving Electronic speed controllers, servos or other devices
  // designed to interface directly with RC Receivers 
  servoAILE.attach(AILE_OUT_PIN);
  servoELEV.attach(ELEV_OUT_PIN);
  servoRUDD.attach(RUDD_OUT_PIN);
 // servoDMLR.attach(DMLR_OUT_PIN);

  // using the PinChangeInt library, attach the interrupts
  // used to read the channels
  PCintPort::attachInterrupt(AILE_IN_PIN, calcAILE,CHANGE);
  PCintPort::attachInterrupt(ELEV_IN_PIN, calcELEV,CHANGE);
  PCintPort::attachInterrupt(RUDD_IN_PIN, calcRUDD,CHANGE);
  attachInterrupt(0, calcGEAR, CHANGE);
  attachInterrupt(1, calcAUX, CHANGE);

}

void loop()
{
  // create local variables to hold a local copies of the channel inputs
  // these are declared static so that thier values will be retained
  // between calls to loop.
  static uint16_t unAILEIn;
  static uint16_t unELEVIn;
  static uint16_t unRUDDIn;
  static uint16_t unGEARIn;
  static uint16_t unAUXIn;
  
  // local copy of update flags
  static uint8_t bUpdateFlags;

  // check shared update flags to see if any channels have a new signal
  if(bUpdateFlagsShared)
  {
    noInterrupts(); // turn interrupts off quickly while we take local copies of the shared variables

      // take a local copy of which channels were updated in case we need to use this in the rest of loop
    bUpdateFlags = bUpdateFlagsShared;

    // in the current code, the shared values are always populated
    // so we could copy them without testing the flags
    // however in the future this could change, so lets
    // only copy when the flags tell us we can.

    if(bUpdateFlags & AILE_FLAG)
    {
      unAILEIn = unAILEInShared;
    }

    if(bUpdateFlags & ELEV_FLAG)
    {
      unELEVIn = unELEVInShared;
    }

    if(bUpdateFlags & RUDD_FLAG)
    {
      unRUDDIn = unRUDDInShared;
    }
    
    if(bUpdateFlags & GEAR_FLAG)
    {
      unGEARIn = unGEARInShared;
    }
    
    if(bUpdateFlags & AUX_FLAG)
    {
      unAUXIn = unAUXInShared;
    }

    // clear shared copy of updated flags as we have already taken the updates
    // we still have a local copy if we need to use it in bUpdateFlags
    bUpdateFlagsShared = 0;

    interrupts(); // we have local copies of the inputs, so now we can turn interrupts back on
    // as soon as interrupts are back on, we can no longer use the shared copies, the interrupt
    // service routines own these and could update them at any time. During the update, the
    // shared copies may contain junk. Luckily we have our local copies to work with :-)
  }

  // do any processing from here onwards
  // only use the local values unRUDDIn, unAILEIn and unELEVIn, the shared
  // variables unRUDDInShared, unAILEInShared, unELEVInShared are always owned by
  // the interrupt routines and should not be used in loop

  // the following code provides simple pass through
  // this is a good initial test, the Arduino will pass through
  // receiver input as if the Arduino is not there.
  // This should be used to confirm the circuit and power
  // before attempting any custom processing in a project.

  // we are checking to see if the channel value has changed, this is indicated 
  // by the flags. For the simple pass through we don't really need this check,
  // but for a more complex project where a new signal requires significant processing
  // this allows us to only calculate new values when we have new inputs, rather than
  // on every cycle.
  if(bUpdateFlags & AILE_FLAG & (unGEARIn < 1500))
  {
    if(servoAILE.readMicroseconds() != unAILEIn)
    {
      servoAILE.attach(AILE_OUT_PIN);  
      servoDMLR.detach();    
      servoAILE.writeMicroseconds(unAILEIn);

    }
  }
  else if (bUpdateFlags & AILE_FLAG & (unGEARIn > 1500))
  {
    servoDMLR.attach(DMLR_OUT_PIN);
    servoAILE.detach();
    servoDMLR.writeMicroseconds(unAILEIn);
  }  

  if(bUpdateFlags & ELEV_FLAG & (unGEARIn < 1500))
  {
    if(servoELEV.readMicroseconds() != unELEVIn)
    {
      servoELEV.attach(ELEV_OUT_PIN);
      servoDMUD.detach();
      servoELEV.writeMicroseconds(unELEVIn);
    }
  }  
  else if(bUpdateFlags & ELEV_FLAG & (unGEARIn > 1500))
  {
    servoDMUD.attach(DMUD_OUT_PIN);
    servoELEV.detach();
    servoDMUD.writeMicroseconds(unELEVIn);
  } 

  if(bUpdateFlags & RUDD_FLAG)
  {
    if(servoRUDD.readMicroseconds() != unRUDDIn)
    {
      servoRUDD.writeMicroseconds(unRUDDIn);
    }
  }
  
//  Serial.println(unAILEIn);
//  Serial.println(unELEVIn);
//  Serial.println(unRUDDIn);
  Serial.println(unGEARIn);
//  Serial.println(unAUXIn);
//  Serial.println("niggers");
  

  bUpdateFlags = 0;
}


// simple interrupt service routine
void calcAILE()
{
  // if the pin is high, its a rising edge of the signal pulse, so lets record its value
  if(digitalRead(AILE_IN_PIN) == HIGH)
  {
    ulAILEStart = micros();
  }
  else
  {
    // else it must be a falling edge, so lets get the time and subtract the time of the rising edge
    // this gives use the time between the rising and falling edges i.e. the pulse duration.
    unAILEInShared = (uint16_t)(micros() - ulAILEStart);
    // use set the AILE flag to indicate that a new AILE signal has been received
    bUpdateFlagsShared |= AILE_FLAG;
  }
}

void calcELEV()
{
  if(digitalRead(ELEV_IN_PIN) == HIGH)
  {
    ulELEVStart = micros();
  }
  else
  {
    unELEVInShared = (uint16_t)(micros() - ulELEVStart);
    bUpdateFlagsShared |= ELEV_FLAG;
  }
}

void calcRUDD()
{
  if(digitalRead(RUDD_IN_PIN) == HIGH)
  {
    ulRUDDStart = micros();
  }
  else
  {
    unRUDDInShared = (uint16_t)(micros() - ulRUDDStart);
    bUpdateFlagsShared |= RUDD_FLAG;
  }
}

void calcGEAR()
{
  if(digitalRead(GEAR_IN_PIN) == HIGH)
  {
    ulGEARStart = micros();
  }
  else
  {
    unGEARInShared = (uint16_t)(micros() - ulGEARStart);
    bUpdateFlagsShared |= GEAR_FLAG;
  }
}

void calcAUX()
{
  if(digitalRead(AUX_IN_PIN) == HIGH)
  {
    ulAUXStart = micros();
  }
  else
  {
    unAUXInShared = (uint16_t)(micros() - ulAUXStart);
    bUpdateFlagsShared |= AUX_FLAG;
  }
}


