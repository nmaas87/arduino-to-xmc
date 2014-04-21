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
