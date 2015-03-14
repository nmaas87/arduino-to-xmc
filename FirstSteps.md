# First Steps to get Arduino code running on XMC1100 #
You need:
  * The board: Infineon XMC1100 Boot Kit or Infineon XMC1300 Boot Kit
  * Environment: DAVE™ – Free Development Platform for Code Generation (DAVE™ 3.1.8 or later)


# Do it by yourself #

If you like to create the Arduino-to-XMC project by yourself, just follow this two tutorials:
  1. [How to create Low Level Driver](http://code.google.com/p/arduino-to-xmc/wiki/HowToCreateLowLevelDriver_XMC1300)
  1. [How to create Arduino\_to\_XMC1100](http://code.google.com/p/arduino-to-xmc/wiki/HowToCreateArduino_to_XMC1100)


## Arduino to XMC Library ##

Arduino Wiring language is available in the Arduino/hardware/xx/core folder (where xxx is the Arduino board name). To keep the same software layout, I decided to put the porting to XMC into [XMC1100](https://code.google.com/p/arduino-to-xmc/source/browse/trunk/hardware/xmc/cores/).

Download [Arduino\_xmc\_cores.zip](http://code.google.com/p/arduino-to-xmc/source/browse/tags/Arduino_xmc_cores.zip) and unzip in the DAVE 'ws' (e.g. 'C:\UserData\Projects\DAVE3\_workspace\ws') or stay tuner to the latest code changes via the Sub Version System (get  howto by reading [svn](https://code.google.com/p/arduino-to-xmc/source/checkout)).

## Arduino to XMC Project for DAVE™ 3.1.8 ##

Arduino-to-XMC porting is based on DAvE software layers. For such reason I prepared a DAvE CE project so to configure the XMC1100 peripherals and low level drivers.

Download [Arduino\_XMC1100\_BootKit.zip](http://code.google.com/p/arduino-to-xmc/source/browse/tags/Arduino_XMC1100_BootKit.zip) and unzip in the DAVE 'ws' (e.g. 'C:\UserData\Projects\DAVE3\_workspace\ws') or stay tuner to the latest code changes via the Sub Version System (get  howto by reading [svn](https://code.google.com/p/arduino-to-xmc/source/checkout)).

## Set-Up the Project Space ##

Once the source files are in the DAVE Workspace, you will see something like this:
![https://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_DAvE.jpg](https://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_DAvE.jpg)

Where:
  1. this is the linked 'Arduino\_examples' folder
> 2 this is the linked 'Arduino\_xmc\_cores' folder
> 3 this is the selected example under compilation (use 'Properties -> Exclude resource from build)

## Code ##

The setup() function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc. The setup function will only run once, after each powerup or reset of the Arduino board.

After creating a setup() function, the loop() function does precisely what its name suggests, and loops consecutively, allowing your program to change and respond as it runs. Code in the loop() section of your sketch is used to actively control the Arduino board. [... see
http://arduino.cc/en/Tutorial/BareMinimum for more details].

### main.c ###

I was too lazy to split the main.c into the real 'main()' function part and the Arduino compatible sketch, so I merged both in one file. Here as for example
```
/*
 * Main.c
 *
 */

#define ARDUINO
#define ARDUINO_MAIN
#include "Arduino.h"

#include <XMC1100.h>		//SFR declarations of the selected device
#include <DAVE3.h>

// #include Arduino HEADER FILES.
#include "pins_arduino.h"
#include "wiring_digital.h"
#include "wiring_time.h"
#include "wiring_clock.h"

int main(void)
{

	/*
	  *  Wiring Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();

	 /*
	  *  Periferals Initialization
	  */
	DAVE_Init();

	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		//yield();
	}
}

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

/*
  ...

  This example code is in the public domain.
 */


void setup() {
   // put your setup code here, to run once:

}

void loop() {
   // put your main code here, to run repeatedly: 
   
}
//****************************************************************************
// 							       END OF FILE
//****************************************************************************


```