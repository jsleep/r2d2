# r2d2
Source code for the Windows Phone Application and multiple Arduinos in Alec Bialek's lifesize R2D2 robot.

## hardware conrolled (that jon knows of)
* 1 Arduino Mega2560
* 3 Arduino micros for controlling flaps, lights, and the holoprojectors
* 1 other arduino for receving RC commands for the motors from a RC controller
* 1 windows phone
* 10 servos
* 3 holoprojects, 1 controlled through RC
* 1 spinning dome controlled through RC
* 2 motors controlled through RC
* CuriousMarc's R2D2 light kit
* mp3 shield

## Arduino sketches

### mega
Source code for the Mega2560 that is communicated to by the windows phone via bluetooth.
It now communicates to one of the dome arduino micro's via I2C to reliably send servo/light animation commands.
Once recieving command from the phone, it sends a commmand to the dome and plays a sound.

### dome
* flaps - controls flaps and recieves i2c commands, send serials to teecees for lights control
* Teeces_CuriousMarc_v1_3 - controls lights from CuriousMarc's R2D2 lights kit
* holoprojectors - randomly moves the holo projectors

## modified arduino ide
a modified version of the ide is required to upload to the mega2560 with the mp3 shield.
this was originally hosted but it is too large of a file for git
it is available here: https://www.dropbox.com/s/3hzcfauwz8871kr/modified%20arduino%20ide.rar?dl=0