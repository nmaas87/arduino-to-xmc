#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************
#include "SoftPWM.h"

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup()  {
	SoftPWM_Init();
	SoftPWM_attach(LED);
	SoftPWM_attach(LED7);
}

// the loop routine runs over and over again forever:
void loop()  {
#if 0
  // set the brightness of LED:
	SoftPWM_SetPercent(LED, brightness);
	SoftPWM_SetPercent(LED7, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 100) {
    fadeAmount = -fadeAmount;
    delay(2000);
  }
  // wait to see the dimming effect
  delay(1000);

  #else
	// set the brightness of LED:
	SoftPWM_SetPercent(LED, 0);
	SoftPWM_SetPercent(LED7, 0);
	delay(1000);

	// set the brightness of LED:
	SoftPWM_SetPercent(LED, 25);
	SoftPWM_SetPercent(LED7, 25);
	delay(1000);

	// set the brightness of LED:
	SoftPWM_SetPercent(LED, 50);
	SoftPWM_SetPercent(LED7, 50);
	delay(1000);

	// set the brightness of LED:
	SoftPWM_SetPercent(LED, 75);
	SoftPWM_SetPercent(LED7, 75);
	delay(1000);

	// set the brightness of LED:
	SoftPWM_SetPercent(LED, 100);
	SoftPWM_SetPercent(LED7, 100);
	delay(5000);
#endif
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************

