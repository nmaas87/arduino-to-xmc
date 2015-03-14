# Serial Monitor #

Demonstrates the use of the Joystik Shield (serial comunication via RS232 over USB).

[... https://www.sparkfun.com/tutorials/171 ...]


# Hardware Required #

XMC1100 Boot Kit board and Joystick Shield:
https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Joystick_1.JPG
[... https://www.sparkfun.com/tutorials/171 ...]

# Circuit #

XMC1100 board already has the serial monitor port connected to the JTAG head. Simply connect a terminal software (e.g. TestTerm) on the respective COM port.

Simply plug the Joystick shield ontop of XMC1100, as such:
https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Joystick_2.JPG

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
//#include "Print.h"

#include <stdio.h>

//Print Serial;

/**
 * @brief This function will transmit the input data to PC Hyperterminal
 *
 * @param[in]: p start address of character buffer
 * @return void
 * */
void uart_printf(const char *p)
{
	while(*p){
		while( 0 != ((UART001_Handle0.UartRegs->TRBSR) & (USIC_CH_TRBSR_TFULL_Msk)));
		UART001_WriteData(UART001_Handle0,*p);
		p++;
	}

}

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
  
  JoystickArduinoBasicExample.pde
  
  A basic sketch to demonstrate reading values from the joystick shield
  
  How to use:
  
    * Connect joystick shield to your Arduino
    * Upload this sketch to your Arduino
    * Open the Arduino IDE Serial Monitor (set to 9600 baud)
    * Waggle joystick, push buttons
  
  Requires:
  
    * Arduino
    * SparkFun Joystick Shield

  Written for SparkFun Arduino Inventor's Kit CIRC-JOY

  Based on original example by Ryan Owens

 */


// Store the Arduino pin associated with each input
const byte PIN_BUTTON_SELECT 		= 2; // Select button is triggered when joystick is pressed

const byte PIN_BUTTON_RIGHT 		= 3;
const byte PIN_BUTTON_UP 			= 4;
const byte PIN_BUTTON_DOWN 			= 5;
const byte PIN_BUTTON_LEFT 			= 6;

const byte PIN_ANALOG_X 			= A0;
const byte PIN_ANALOG_Y 			= A1;

void setup() {
  //Serial.begin(19200);

  // Specify each pin connected to a pushbutton as an input.
  // Also enable the Arduino's internal "pull-up" resistors
  // for each pushbutton we want to read--this means the shield
  // doesn't need to have resistors on it.
  // Note that when a pull-up resistor is used on a pin the
  // meaning of the values read are reversed compared to their
  // usual meanings:
  //    * HIGH = the button is not pressed
  //    * LOW = the button is pressed
  pinMode(PIN_BUTTON_SELECT, INPUT);  
  digitalWrite(PIN_BUTTON_SELECT, HIGH);  
}


void loop()
{
char msg_buff[120];

	// Print the current values of the inputs to the console.
	sprintf(msg_buff, "x: %d y: %d s: %d\r\n", (int)analogRead(PIN_ANALOG_X), (int)analogRead(PIN_ANALOG_Y), (int)digitalRead(PIN_BUTTON_SELECT));

	//Send the data
	uart_printf(msg_buff);

	// some delay
	delay(500);
}



//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## SETUP ##

  1. Connect the XMC1100 Boot Kit to your PC. Windows will install the necessary driver if it's connected the first time.
  1. Find XMC1100 virtual COM port via Control Panel->System->Device Manager->Ports->Jlink CDC UART Port (COMxx).
  1. Start Hyper Terminal on PC with the settings shown in ![http://arduino-to-xmc.googlecode.com/svn/wiki/TerminalSettings.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/TerminalSettings.jpg).

## EXECUTION ##
This is what you will get on the terminal window:

![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Joystick_3.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Joystick_3.jpg)

Here an extract of the terminal window:
```
x: 503 y: 496 s: 0
x: 503 y: 496 s: 0
x: 504 y: 496 s: 16
x: 502 y: 498 s: 16
x: 504 y: 497 s: 0
x: 504 y: 497 s: 0
x: 303 y: 496 s: 16
x: 1 y: 496 s: 16
x: 1 y: 81 s: 16
x: 2 y: 1 s: 16
x: 504 y: 496 s: 16
```

**Notes:**
  * by pressing the Joystick,'s=0' otherwise 's=16'
  * bottom-left is 'x=1, y=1'
  * top-right is 'x=1023, y=1023'