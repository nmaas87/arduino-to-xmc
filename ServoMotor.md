# Servo Motor #

This page shows two examples on how to Control the position of a RC (hobby) servo motor with XMC1100.


The first example is the basic code to make the motor spin the center position. The second example is coded in a more complex way, but allows to make the motor spin at different speeds, in both directions, and controlling both from a potentiometer.

[... http://arduino.cc/en/Tutorial/Sweep ...]


# Hardware Required #

https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_ServoMotor.JPG

The Servo Motor is coming from Conrad...


# Circuit #

We connect three wires to the XMC1100 board:
  * +5V to Red Servo cable
  * GND to Brown Servo cable
  * pin 8 to Orange Servo cable

# Example 1: Simple example #
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
	  *  Wiring Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();
	wiring_time_init();
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

// set pin numbers:
const int servoPin =  8;      // the number of servo pin

void setup() {
   // set the digital pin as output:
   pinMode(servoPin, OUTPUT);
}

void loop()
{
	digitalWrite(servoPin, HIGH);	// set the servo pin to +5V
	delayMicroseconds(1500);
	digitalWrite(servoPin, LOW);	// set the servo pin to GND
	delay(20);						// servo need to be updated each 20-40 ms
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## SETUP ##
See hardware section.

## EXECUTION ##
The Servo Motor will move to the center position:
![https://arduino-to-xmc.googlecode.com/svn/wiki/Servo_centro.jpg](https://arduino-to-xmc.googlecode.com/svn/wiki/Servo_centro.jpg)

# Example 2: Sweep #
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
	  *  Wiring Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();
	wiring_time_init();
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

// set pin numbers:
const int servoPin =  8;      	// the number of servo pin
int pos = 0;    				// variable to store the servo position

const int MAX = 2000;
const int MIN = 500;

void servo_write(int p)
{
	//p = map(p, 0, 179, 0, 2000);	// scale it to use it with the servo (value between 0 and 180)
	digitalWrite(servoPin, HIGH);	// set the servo pin to +5V
	delayMicroseconds(p);
	digitalWrite(servoPin, LOW);	// set the servo pin to GND
	delay(20);						// servo need to be updated each 20-40 ms
}

void setup() {
   // set the digital pin as output:
   pinMode(servoPin, OUTPUT);
}

void loop()
{
   for(pos = MIN; pos < MAX; pos += 10) // goes from 0 degrees to 180 degrees
   {
     servo_write(pos);              	// tell servo to go to position in variable 'pos'
     delay(15);                       	// waits 15ms for the servo to reach the position
   }
   for(pos = MAX; pos>=MIN; pos-=10)    // goes from 180 degrees to 0 degrees
   {
     servo_write(pos);              	// tell servo to go to position in variable 'pos'
     delay(15);                       	// waits 15ms for the servo to reach the position
   }
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## SETUP ##
See hardware section.

## EXECUTION ##
The Servo Motor will rotate clockwise and counterclock wise.