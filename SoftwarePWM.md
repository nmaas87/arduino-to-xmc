# The Software PWM Library #

The Software PWM Library can generate PWM signal on all of XMC's pins simultaneously. The API is based on [SoftPWM](http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation) library but the code is slightly different.

[... http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation ...]

**Note:** the SoftPWM library can support up to 7 additional PWM channel (plus the 4 hardware PWM channels on XMC1x00), you can use any digital port for the PWM signals...

# Hardware Required #

XMC1100 Boot Kit board:
![http://arduino-to-xmc.googlecode.com/svn/wiki/myXMC1100.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/myXMC1100.jpg)
> or
XMC1300 Boot Kit board:
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1300_LED.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1300_LED.jpg)

# Circuit #

XMC1100 board already has one LED connected to standard Arduino pin13 port (P0.7). So, there is no need to attach 220-ohm resistor and LED on pin 13.
> or
XMC1300 board already has one LED connected to standard Arduino pin13 port (P0.7). So, there is no need to attach 220-ohm resistor and LED on pin 13.

**Note:** above connections are just as for example, any other pin can be configured for the PWM signal generation.

# Library Code Documentation #

The library code is well documented and the API is patterned similarly to [SoftPWM](http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation).

The availeble functions are:
```
void SoftPWM_Init(void);
void SoftPWM_attach(uint8_t pin);
void SoftPWM_detach(uint8_t pin);
boolean SoftPWM_attached(int8_t pin);
void SoftPWM_SetPercent(int8_t pin, uint8_t percent);
```

The PWM generation is running at 60Hz so to avoid flickering:
```
#define SOFTPWM_TIME		   (16*TIMER_1mSec/100)/*!< 1/60 Hz = 16 [msec] */
```

**Note:** the library is based on the 'SYSTM002' DAvE low level driver. For more details, see [Arduino\_to\_XMC\_library\_layering](http://code.google.com/p/arduino-to-xmc/wiki/Arduino_to_XMC_library_layering).

# Example: one LED fading #

**Note:** before testing the below example code, you need to include the related Library code into the DAvE project. Libraries code are available under [arduino-to-xmc/libraries](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/libraries/).

```
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
}

// the loop routine runs over and over again forever:
void loop()  {

  // set the brightness of LED:
	SoftPWM_SetPercent(LED, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 100) {
    fadeAmount = -fadeAmount;
    delay(2000);
  }
  // wait to see the dimming effect
  delay(1000);
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## EXECUTION ##

XMCx00 LED will fade slowly...

# Example: two LEDs fading #

**Note:** before testing the below example code, you need to include the related Library code into the DAvE project. Libraries code are available under [arduino-to-xmc/libraries](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/libraries/).

```
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
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## EXECUTION ##

XMCx00 LEDs will fade slowly...