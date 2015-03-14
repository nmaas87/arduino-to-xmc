# Array of LEDs #

This variation on the For Loop example shows how to use an array. An array is a variable with multiple parts. If you think of a variable as a cup that holds values, you might think of an array as an ice cube tray. It's like a series of linked cups, all of which can hold the same maximum value.


The For Loop example shows you how to light up a series of LEDs available in the extended area (not Arduino area). Those leds are: LED2, LED3, LED4, LED5, LED6 and LED7.

This example shows you how you can turn on a sequence of pins whose numbers are neither contiguous nor necessarily sequential. To do this is, you can put the pin numbers in an array and then use for loops to iterate over the array.

This example makes use of 6 LEDs available and connected to the pins 30 - 35 on XMC1100 board, just like in the For Loop. However, here the order of the LEDs is determined by their order in the array, the same of their physical order.

This technique of putting the pins in an array is very handy. You don't have to have the pins sequential to one another, or even in the same order. You can rearrange them however you want.



# Hardware Required #

XMC1100 Boot Kit board:
![http://arduino-to-xmc.googlecode.com/svn/wiki/myXMC1100.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/myXMC1100.jpg)

# Circuit #

XMC1100 board already has eight additional LEDs connected to:
```
#define LED2	30	// Extended Leds P0.5
#define LED3	31	// Extended Leds P0.6
#define LED4	32	// Extended Leds P1.2
#define LED5	33	// Extended Leds P1.3
#define LED6	34	// Extended Leds P1.4
#define LED7	35	// Extended Leds P1.5
```

# Code #
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
  Arrays
 
 Demonstrates the use of  an array to hold pin numbers
 in order to iterate over the pins in a sequence. 
 Lights multiple LEDs in sequence, then in reverse.
 
 Unlike the For Loop tutorial, where the pins have to be
 contiguous, here the pins can be in any random order.
 
 The circuit:
 * LEDs from pins 2 through 7 to ground
 
 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Array
 */

int timer = 100;           // The higher the number, the slower the timing.
int ledPins[] = { 
		LED2, LED3, LED4, LED5, LED6, LED7 };       // an array of pin numbers to which LEDs are attached
int pinCount = 6;           // the number of pins (i.e. the length of the array)

void setup() {
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }
}

void loop() {
  // loop from the lowest pin to the highest:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);   
    delay(timer);                  
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);    

  }

  // loop from the highest pin to the lowest:
  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);
  }
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```