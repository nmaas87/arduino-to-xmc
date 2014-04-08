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
//#include <stdio.h>

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
#if 1
#if 1

	  int i;

	  for (i=0; i<16; i++)
	  {
	    delay(500);
	    TM1640_clearDisplay();
	    TM1640_setDisplayDigit(i, i, false);
	  }
	  delay(60);

#else
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
		TM1640_setDisplayToString("HA110 XMC1100",0,0);
	}
#endif

#else

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
#endif
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
