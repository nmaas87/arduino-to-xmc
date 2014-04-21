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
