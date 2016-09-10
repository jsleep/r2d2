/**
 * \file MP3Shield_Library_Demo.ino
 *
 * \brief Example sketch of using the MP3Shield Arduino driver
 * \remarks comments are implemented with Doxygen Markdown format
 *
 * \author Bill Porter
 * \author Michael P. Flaga
 *
 * This sketch listens for commands from a serial terminal (like the Serial
 * Monitor in the Arduino IDE). If it sees 1-9 it will try to play an MP3 file
 * named track00x.mp3 where x is a number from 1 to 9. For eaxmple, pressing
 * 2 will play 'track002.mp3'. A lowe case 's' will stop playing the mp3.
 * 'f' will play an MP3 by calling it by it's filename as opposed to a track
 * number.
 *
 * Sketch assumes you have MP3 files with filenames like "track001.mp3",
 * "track002.mp3", etc on an SD card loaded into the shield.
 */

#include <SPI.h>
#include <SoftwareSerial.h>
//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

// Below is not needed if interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
  #include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
  #include <SimpleTimer.h>
#endif

/**
 * \brief Object instancing the SdFat library.
 *
 * principal object for handling all SdCard functions.
 */
SdFat sd;

/**
 * \brief Object instancing the SFEMP3Shield library.
 *
 * principal object for handling all the attributes, members and functions for the library.
 */
SFEMP3Shield MP3player;

//------------------------------------------------------------------------------
/**
 * \brief Setup the Arduino Chip's feature for our use.
 *
 * After Arduino's kernel has booted initialize basic features for this
 * application, such as Serial port and MP3player objects with .begin.
 * Along with displaying the Help Menu.
 *
 * \note returned Error codes are typically passed up from MP3player.
 * Whicn in turns creates and initializes the SdCard objects.
 *
 * \see
 * \ref Error_Codes
 */
 
 int BTTx = 11;
 int BTRx = 10;
 SoftwareSerial BT(BTTx, BTRx);
 
 int DMTx = 62;
 int DMRx = 63;
 SoftwareSerial DM(DMRx, DMTx);
 
 long previousMillis = 0;
 long interval = 0;
void setup()
{

  uint8_t result; //result code from some function as to be tested at later time.

  Serial.begin(9600);
  BT.begin(9600);
  DM.begin(14400);
  // Setup Bluetooth for WP8


  Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
  Serial.print(FreeRam(), DEC);  // FreeRam() is provided by SdFatUtil.h
  Serial.println(F(" Should be a base line of 1095, on ATmega328 when using INTx"));


  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  //Initialize the MP3 Player Shield
  result = MP3player.begin();
  //check result, see readme for error codes.
  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if( result == 6 ) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
      Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
    }
  }
  randomSeed(analogRead(31));
#if (0)
  // Typically not used by most shields, hence commented out.
  Serial.println(F("Applying ADMixer patch."));
  if(MP3player.ADMixerLoad("admxster.053") == 0) {
    Serial.println(F("Setting ADMixer Volume."));
    MP3player.ADMixerVol(-3);
  }
#endif


}

//------------------------------------------------------------------------------
/**
 * \brief Main Loop the Arduino Chip
 *
 * This is called at the end of Arduino kernel's main loop before recycling.
 * And is where the user's serial input of bytes are read and analyzed by
 * parsed_menu.
 *
 * Additionally, if the means of refilling is not interrupt based then the
 * MP3player object is serviced with the availaible function.
 *
 * \note Actual examples of the libraries public functions are implemented in
 * the parse_menu() function.
 */
void loop() {
  char trackName[] = "track003.mp3";
  byte key_command, option, mood, stop_track, song[3], string_filter;
  int digit1, digit2, digit3, digit4, rand=0, newRand=0;

  BT.listen();
  while(BT.available()==0)  {}
  string_filter = BT.read();
  
  if(string_filter == '<')
  {
  // print prompt after key stroke has been processed.
  Serial.println(F("Enter command (s, -, +, p, r, R, or f"));
  
  while(BT.available()==0)  {}
    key_command= BT.read();
  
  if(key_command=='s' || key_command=='-' || key_command=='+' || key_command=='p' || key_command=='r' || key_command=='R') {
    parse_menu(key_command);
  }  //Everything but playing a song is sent to parsemenu with this statement
  
  //this if statement sends information to the mp3 shield itself about what track to play
  else if(key_command=='f') {
    Serial.println(F("Enter sound option (a/b)"));
    while(BT.available()==0) {}
      option= BT.read();

    //mood selection
    if(option=='a') { 
      Serial.println(F("Enter mood"));
      while(BT.available()==0) {}
      mood= BT.read();
      if(mood=='a') {
        Serial.println(F("Happy"));
        MP3player.playTrack(1);
        stop_track='n';
        interval = random(5000,30000);
        while(stop_track=='n') {
          unsigned long currentMillis = millis();
          string_filter = BT.read();
          if(string_filter == '<'){
            stop_track=BT.read();
            Serial.println(stop_track);
            Serial.println(string_filter);
          }
          if(currentMillis - previousMillis > interval) {
          while(newRand==rand){
            newRand=random(1,40);
          }
          rand=newRand;
          MP3player.playTrack(rand);
          interval = random(5000,30000);
          previousMillis = currentMillis;
          }
        }
        MP3player.playTrack(1);
      }
      else if(mood=='b') {
        Serial.println(F("Mad"));
        MP3player.playTrack(51);
        stop_track='n';
        interval = random(5000,30000);
        while(stop_track=='n') {
          unsigned long currentMillis = millis();
          string_filter = BT.read();
          if(string_filter == '<'){
            stop_track=BT.read();
            Serial.println(stop_track);
            Serial.println(string_filter);
          }
          if(currentMillis - previousMillis > interval) {
          while(newRand==rand){
            newRand=random(51,76);
          }
          rand=newRand;
          MP3player.playTrack(rand);
          interval = random(5000,30000);
          previousMillis = currentMillis;
          }
        }
        MP3player.playTrack(51);
      }
      else if(mood=='c') {
        Serial.println(F("Sad"));
        MP3player.playTrack(101);
        stop_track='n';
        interval = random(5000,30000);
        while(stop_track=='n') {
          unsigned long currentMillis = millis();
          string_filter = BT.read();
          if(string_filter == '<'){
            stop_track=BT.read();
            Serial.println(stop_track);
            Serial.println(string_filter);
          }
          if(currentMillis - previousMillis > interval) {
          while(newRand==rand){
            newRand=random(101,130);
          }
          rand=newRand;
          MP3player.playTrack(rand);
          interval = random(5000,30000);
          previousMillis = currentMillis;
          }
        }
        MP3player.playTrack(101);
      }
      else if(mood=='d') {
        Serial.println(F("Famous"));
        MP3player.playTrack(151);
        stop_track='n';
        interval = random(5000,30000);
        while(stop_track=='n') {
          unsigned long currentMillis = millis();
          string_filter = BT.read();
          if(string_filter == '<'){
            stop_track=BT.read();
            Serial.println(stop_track);
            Serial.println(string_filter);
          }
          if(currentMillis - previousMillis > interval) {
          while(newRand==rand){
            newRand=random(151,158);
          }
          rand=newRand;
          MP3player.playTrack(rand);
          interval = random(5000,30000);
          previousMillis = currentMillis;
          }
        }
        MP3player.playTrack(151);
      }
    }
//this plays an individual track. I figured it would be easiest to send a 3 digit integer to the 'duino from my phone
//so i have to have 3 read byte statements to get the track number and then call MP3 player
    else {
       while(BT.available()==0) {}
       BT.read(); //this is to get rid of the initial character sent from the phone
       while(BT.available()==0) {}
       digit1=BT.read();
       while(BT.available()==0) {}
       digit2=BT.read();
       while(BT.available()==0) {}
       digit3=BT.read();
       digit4=((100*digit1)+(10*digit2)+digit3)-5328;
       Serial.println(digit4);
       if(BT.available()==0) {}
       digit1=BT.read();
       if(BT.available()==0) {}
       digit2=BT.read();
       digit3=((10*digit1)+digit2)-528;
       Serial.println(digit3);
      MP3player.playTrack(digit4);
      if(digit3 >-1 && digit3 < 17){
        DM.listen();
        DM.write(digit3);
      }
      }
  }  
  
  
// Below is only needed if not interrupt driven. Safe to remove if not using.
//#if defined(USE_MP3_REFILL_MEANS) \
//    && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
//    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

//  MP3player.available();
//#endif

//  if(Serial.available()) {
//    parse_menu(Serial.read()); // get command from serial input
//  }
  }
  delay(100);
  
}

//------------------------------------------------------------------------------
/**
 * \brief Decode the Menu.
 *
 * Parses through the characters of the users input, executing corresponding
 * MP3player library functions and features then displaying a brief menu and
 * prompting for next input command.
 */
void parse_menu(byte key_command) {

  uint8_t result; // result code from some function as to be tested at later time.


  Serial.print(F("Received command: "));
  Serial.write(key_command);
  Serial.println(F(" "));

  //if s, stop the current track
  if(key_command == 's') {
    Serial.println(F("Stopping"));
    MP3player.stopTrack();

  //if 1-9, play corresponding track
  } else if(key_command >= '1' && key_command <= '9') {
    //convert ascii numbers to real numbers
    key_command = key_command - 48;

#if USE_MULTIPLE_CARDS
    sd.chvol(); // assign desired sdcard's volume.
#endif
    //tell the MP3 Shield to play a track
    result = MP3player.playTrack(key_command);

    //check result, see readme for error codes.
    if(result != 0) {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to play track"));
    } 
  
  //if +/- to change volume
  } else if((key_command == '-') || (key_command == '+')) {
    union twobyte mp3_vol; // create key_command existing variable that can be both word and double byte of left and right.
    mp3_vol.word = MP3player.getVolume(); // returns a double uint8_t of Left and Right packed into int16_t

    if(key_command == '-') { // note dB is negative
      // assume equal balance and use byte[1] for math
      if(mp3_vol.byte[1] >= 254) { // range check
        mp3_vol.byte[1] = 254;
      } else {
        mp3_vol.byte[1] += 2; // keep it simpler with whole dB's
      }
    } else {
      if(mp3_vol.byte[1] <= 2) { // range check
        mp3_vol.byte[1] = 2;
      } else {
        mp3_vol.byte[1] -= 2;
      }
    }
    // push byte[1] into both left and right assuming equal balance.
    MP3player.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
    Serial.print(F("Volume changed to -"));
    Serial.print(mp3_vol.byte[1]>>1, 1);
    Serial.println(F("[dB]"));


  /* Alterativly, you could call a track by it's file name by using playMP3(filename);
  But you must stick to 8.1 filenames, only 8 characters long, and 3 for the extension */
  } else if(key_command == 'f' || key_command == 'F') {
    uint32_t offset = 0;
    if (key_command == 'F') {
      offset = 2000;
    }

    //create a string with the filename
    Serial.println(F("Enter song choice"));
    char trackName[] = "track003.mp3";
    while(Serial.available()==0) {}
    Serial.readBytes(trackName, 12);
    
#if USE_MULTIPLE_CARDS
    sd.chvol(); // assign desired sdcard's volume.
#endif
    //tell the MP3 Shield to play that file
    result = MP3player.playMP3(trackName, offset);
    //check result, see readme for error codes.
    if(result != 0) {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to play track"));
    }

  }  else if(key_command == 'p') {
    if( MP3player.getState() == playback) {
      MP3player.pauseMusic();
      Serial.println(F("Pausing"));
    } else if( MP3player.getState() == paused_playback) {
      MP3player.resumeMusic();
      Serial.println(F("Resuming"));
    } else {
      Serial.println(F("Not Playing!"));
    }

  } else if(key_command == 'r') {
    MP3player.resumeMusic(2000);

  } else if(key_command == 'R') {
    MP3player.stopTrack();
    MP3player.vs_init();
    Serial.println(F("Reseting VS10xx chip"));

 

  } 


}


