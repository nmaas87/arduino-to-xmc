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

int outPin = 8;                 // digital pin 8

void setup()
{
  pinMode(outPin, OUTPUT);      // sets the digital pin as output
}

void loop()
{
  digitalWrite(outPin, HIGH);   // sets the pin on
  delayMicroseconds(50);        // pauses for 50 microseconds      
  digitalWrite(outPin, LOW);    // sets the pin off
  delayMicroseconds(50);        // pauses for 50 microseconds      
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
