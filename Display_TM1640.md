# TM1640 LED Display Modules #

The purpose of this article is to demonstrate the use of an interesting LED display module I discovered on the dealextreme website, for example:
![http://i1.wp.com/tronixstuff.com/wp-content/uploads/2012/04/tm1640display.jpg](http://i1.wp.com/tronixstuff.com/wp-content/uploads/2012/04/tm1640display.jpg)

[... http://tronixstuff.com/2012/04/09/arduino-and-tm1640-led-display-modules/...]


# Hardware Required #

XMC1100 Boot Kit board and TM1640 Display: ![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640.jpg)

# Circuit #

Connect the TM1640 display as:
  * Vcc to XMC +5V
  * GND to XMC GND
  * DIN to Arduino XMC Pin7
  * SCLK to Arduino XMC Pin 8

# Code #
## TM1640 Library ##
On the contrary of the ufficial Arduino TM1640 library, the XMC1100 version is a pure C-code version. I had to port it from C++ in order to save memory size. Anyhow the original library features has been kept. The major definition are:
  * 'TM1640 module(7, 8);' must be replaced with 'TM1640\_Init(7, 8);'
  * 'module.clearDisplay();' must be replaced with 'TM1640\_clearDisplay();'
  * 'module.setDisplayDigit(...);' must be replaced with 'TM1640\_setDisplayDigit(..)'
  * 'module.setDisplayToString(...);' must be replaced with 'TM1640\_setDisplayToString(..)'

## Example 1 ##
Simple program to scroll a digit across the 16 display digits:
```
/*
 * Main.c
 *
 */

#define ARDUINO_MAIN
#include "Arduino.h"

#include <XMC1100.h>		//SFR declarations of the selected device
#include <DAVE3.h>

int main(void)
{

	 /*
	  *  Periferals Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();
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
#include "TM1640.h"

void setup()
{
	// Init Display: define a module on data pin 7, clock pin 8
	TM1640_Init(7, 8);
	pinMode(LED2, OUTPUT);
}

void loop()
{
	  int i;

	  for (i=0; i<16; i++)
	  {
	    delay(500);
	    TM1640_clearDisplay();
	    TM1640_setDisplayDigit(i, i, false);
	  }
	  delay(60);
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
The above example generate something like:
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640_Simpler.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640_Simpler.jpg)
(I could't take a video).



## Example 2 ##
Simple program to blink LED2 and print 'HA110 XMC1100':
```
/*
 * Main.c
 *
 */

#define ARDUINO_MAIN
#include "Arduino.h"

#include <XMC1100.h>		//SFR declarations of the selected device
#include <DAVE3.h>

int main(void)
{

	 /*
	  *  Periferals Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();
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
#include "TM1640.h"

int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)


void setup()
{
	// Init Display: define a module on data pin 7, clock pin 8
	TM1640_Init(7, 8);
	pinMode(LED2, OUTPUT);
}

void loop()
{
	// check to see if it's time to blink the LED; that is, if the
	// difference between the current time and last time you blinked
	// the LED is bigger than the interval at which you want to
	// blink the LED.
	unsigned long currentMillis = millis();

	if(currentMillis - previousMillis > interval)
	{
		// save the last time you blinked the LED
		previousMillis = currentMillis;

		// if the LED is off turn it on and vice-versa:
		if (ledState == LOW)
			ledState = HIGH;
		else
			ledState = LOW;

		// set the LED with the ledState of the variable:
		digitalWrite(LED2, ledState);

		// Print on Display TM1640 ...
		TM1640_setDisplayToString("HALL0 XMC1100",0,0);
	}}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
The above example generate something like:
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640_Hallo.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640_Hallo.jpg)





## Example 3 ##
Simple program to print counter on Display:
```
/*
 * Main.c
 *
 */

#define ARDUINO_MAIN
#include "Arduino.h"

#include <XMC1100.h>		//SFR declarations of the selected device
#include <DAVE3.h>

int main(void)
{

	 /*
	  *  Periferals Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();
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
#include "TM1640.h"
#include <stdio.h>

void setup()
{
	// Init Display: define a module on data pin 7, clock pin 8
	TM1640_Init(7, 8);
	pinMode(LED2, OUTPUT);
}

void loop()
{
 char text[17];
 int z;

   for (z=0; z<5; z++)
   {
     int a=32767;
     sprintf(text, "INTEGER %i",a);
     TM1640_setDisplayToString(text,0,0);
     delay(1000);
     TM1640_clearDisplay(); unsigned int ui=65535;
     sprintf(text, "UNSIGNED %u",ui);
     TM1640_setDisplayToString(text,0,0);
     delay(1000);
     TM1640_clearDisplay();
   }

   for (z=0; z<32767; z++)
   {
     sprintf(text, "COUNTING %i",z);
     TM1640_setDisplayToString(text,0,0);
     delay(10);
   }

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
The above example generate something like:
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640_Counting.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_TM1640_Counting.jpg)