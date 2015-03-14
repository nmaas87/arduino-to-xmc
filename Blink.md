# Blink #

This example shows the simplest thing you can do with an Arduino on XMC to see physical output: it blinks an LED.

**Note:** I've tested this simple sketch on XMC1100 and XMC1300.


# Hardware Required #

XMC1100 Boot Kit board:
![http://arduino-to-xmc.googlecode.com/svn/wiki/myXMC1100.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/myXMC1100.jpg)
> or
XMC1300 Boot Kit board:
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1300_LED.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1300_LED.jpg)
> or
XMC4500 Relax Kit board:
http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC4500-Relax_Kit.JPG

# Circuit #

XMC1100 board already has one LED connected to standard Arduino pin13 port (P0.7). So, there is no need to attach 220-ohm resistor and LED on pin 13.
> or
XMC1300 board already has one LED connected to standard Arduino pin13 port (P0.7). So, there is no need to attach 220-ohm resistor and LED on pin 13.
> or
XMC4500 board already has one LED available port (P1.1). So, there is no need to attach 220-ohm resistor and LED on pin 13.

# Code #
```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// Pin 13 has the LED on XMC1100
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## Execution ##
The LED will blink at 1Hz frequency....

Here the XMC4500 test:
https://arduino-to-xmc.googlecode.com/svn/wiki/XMC4500_LedBlinking.JPG