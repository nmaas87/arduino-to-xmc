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
// 							       END OF FILE
//****************************************************************************
