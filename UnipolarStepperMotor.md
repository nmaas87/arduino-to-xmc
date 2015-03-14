# Unipolar Stepper Motor #

This page shows two examples on how to drive a unipolar stepper motor. These motors can be found in old floppy drives and are easy to control. The one we use has 6 connectors of which one is power (VCC) and the other four are used to drive the motor sending synchronous signals.


The first example is the basic code to make the motor spin in one direction. It is aiming those that have no knowledge in how to control stepper motors. The second example is coded in a more complex way, but allows to make the motor spin at different speeds, in both directions, and controlling both from a potentiometer.

[... http://arduino.cc/en/Tutorial/StepperUnipolar ...]


# Hardware Required #

![https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_UnipolarStepper.jpg](https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_UnipolarStepper.jpg)

The Unipolar Stepper motor is coming from ETT [ET MINI SMCC-547](ftp://ulita.ms.mff.cuni.cz/predn/NPRG037/ALL_MINI_IO.pdf)


# Circuit #

We connect six wires to the XMC1100 board:
  * +5V to Vcc
  * GND to GND
  * pin 8 to INA
  * pin 9 to INB
  * pin 10 to INC
  * pin 11 to IND

# Example 1: Simple example #
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
/* Stepper Unipolar
 * 
 * Example 1: Simple example
 * -------------
 *
 * Program to drive a stepper motor coming ETT
 * [ftp://ulita.ms.mff.cuni.cz/predn/NPRG037/ALL_MINI_IO.pdf]
 *
 */

int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;
int delayTime = 100;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(delayTime);
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## SETUP ##
See hardware section.

## EXECUTION ##
The Stepper Motor will rotate depending on delay settings:
  * int delayTime = 500; produces a very slow rotation
  * int delayTime = 100; produces a slow rotation
  * int delayTime = 50; produces a normal rotation
  * int delayTime = 10; produces a fast rotation.

# Example 2: Stepper Unipolar Advanced #
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

/* Stepper Unipolar
 *
 * Example 2: Stepper Unipolar Advanced
 * -------------
 *
 * Program to drive a stepper motor coming ETT
 * [ftp://ulita.ms.mff.cuni.cz/predn/NPRG037/ALL_MINI_IO.pdf]
 *
 */

int motorPins[] = {8, 9, 10, 11};
int count = 0;
int count2 = 0;
int delayTime = 500;
int val = 0;

void setup() {
  for (count = 0; count < 4; count++) {
    pinMode(motorPins[count], OUTPUT);
  }
}

void moveForward() {
  if ((count2 == 0) || (count2 == 1)) {
    count2 = 16;
  }
  count2>>=1;
  for (count = 3; count >= 0; count--) {
    digitalWrite(motorPins[count], count2>>count&0x01);
  }
  delay(delayTime);
}

void moveBackward() {
  if ((count2 == 0) || (count2 == 1)) {
    count2 = 16;
  }
  count2>>=1;
  for (count = 3; count >= 0; count--) {
    digitalWrite(motorPins[3 - count], count2>>count&0x01);
  }
  delay(delayTime);
}

void loop() {
  val = analogRead(A0);
  if (val > 540) {
    // move faster the higher the value from the potentiometer
    delayTime = 2048 - 1024 * val / 512 + 1;
    moveForward();
  } else if (val < 480) {
    // move faster the lower the value from the potentiometer
    delayTime = 1024 * val / 512 + 1;
    moveBackward();
  } else {
    delayTime = 1024;
  }
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## SETUP ##
See hardware section and additionally connect a potentiometer to Analogue Input 0. With the potentiometer you'll be able to contol the direction and the Unipolar Stepper Motor.

## EXECUTION ##
The Stepper Motor will rotate depending on analogue voltage given on pin A0.