# Fading #

Demonstrates the use of the analogWrite() function in fading an LED off and on. 'AnalogWrite()' uses pulse width modulation (PWM), turning a digital pin on and off very quickly, to create a fading effect.

[... http://arduino.cc/en/Tutorial/Fade ...]


# Hardware Required #

XMC1100 Boot Kit board: ![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg)

# Circuit #

XMC1100 board already has one LED connected to standard Arduino pin13 port. So, there is no need to attach 220-ohm resistor and LED on pin 13.

**Note:** the below code can only run on the available hardware PWM pins available. Check the XMC Boot Kit pinout. In case you need to use other pins, include SoftPWM library. Libraries code are available under [arduino-to-xmc/libraries](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/libraries/).

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
 Fade
 
 This example shows how to fade an LED on pin 13
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 13;          // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup()  { 
  // declare LED to be an PWM output:
  pinMode(led, PWM);

  // Turn-Off LED1 sis is not used
  pinMode(LED2, OUTPUT);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of LED:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

### NOTE ###

As you can see from the above code, to declare an output as PWM you must use the 'PWM' qualifier:
```
// the setup routine runs once when you press reset:
void setup()  { 
  // declare LED to be an PWM output:
  pinMode(led, PWM);
} 
```

**Attention:** This is different from standard Arduino Wiring syntax!!!

In fact, Arduino Wiring syntax only declares:
```
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
```

While Arduino-to-XMC declares:
```
#define INPUT			0
#define OUTPUT			1
#define INPUT_PULLUP	2
#define INPUT_PULLDW	3
#define PWM				4
```