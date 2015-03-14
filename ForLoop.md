# For Loop and Array of LEDs #

Often you want to iterate over a series of pins and do something to each one. For instance, this example blinks 6 LEDs attached the Arduino by using a for() loop to cycle back and forth through digital pins 30-35 (exdended XMC1100 LEDs). The LEDS are turned on and off, in sequence, by using both the digitalWrite() and delay() functions.

The For Loop example shows you how to light up a series of LEDs available in the extended area (not Arduino area). Those leds are: LED2, LED3, LED4, LED5, LED6 and LED7.

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
  For Loop Iteration
 
 Demonstrates the use of a for() loop. 
 Lights multiple LEDs in sequence, then in reverse.
 
 The circuit:
 * LEDs from pins 30 through 35 to ground
 
 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/ForLoop
 */

int timer = 100;           // The higher the number, the slower the timing.

void setup() {
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 30; thisPin < 36; thisPin++)  {
    pinMode(thisPin, OUTPUT);      
  }
}

void loop() {
  // loop from the lowest pin to the highest:
  for (int thisPin = 30; thisPin < 36; thisPin++) { 
    // turn the pin on:
    digitalWrite(thisPin, HIGH);   
    delay(timer);                  
    // turn the pin off:
    digitalWrite(thisPin, LOW);    
  }

  // loop from the highest pin to the lowest:
  for (int thisPin = 35; thisPin >= 30; thisPin--) { 
    // turn the pin on:
    digitalWrite(thisPin, HIGH);
    delay(timer);
    // turn the pin off:
    digitalWrite(thisPin, LOW);
  }
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```