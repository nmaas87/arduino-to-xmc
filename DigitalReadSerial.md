# Pushbutton #

Demonstrates the use of the serial monitor (serial comunication via RS232 over USB) and a button.
The pushbutton is a component that connects two points in a circuit when you press it. The example turns on an LED when you press the button

[... http://www.arduino.cc/en/Tutorial/Pushbutton#.UwU8BvJd6M8 ...]


# Hardware Required #

XMC1100 Boot Kit board: https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Pushbutton.JPG

When the pushbutton is open (unpressed) there is no connection between the two legs of the pushbutton, so the pin is connected to 5 volts (through the pull-up resistor) and we read a HIGH. When the button is closed (pressed), it makes a connection between its two legs, connecting the pin to ground, so that we read a LOW. (The pin is still connected to 5 volts, but the resistor in-between them means that the pin is "closer" to ground.)


# Circuit #

XMC1100 board already has the serial monitor port connected to the JTAG head. Simply connect a terminal software (e.g. Tera Term) on the respective COM port.

We connect three wires to the XMC1100 board. The first goes from one leg of the pushbutton through a pull-up resistor (here 2.2 KOhms) to the 5 volt supply. The second goes from the corresponding leg of the pushbutton to ground. The third connects to a digital i/o pin (here pin 7) which reads the button's state.

Connect to pin 7 a wire to +5V or GND to simulate the pushbutton instead.

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

#include <stdio.h>

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
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

// digital pin 7 has a pushbutton attached to it. Give it a name:
int pushButton = 7;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 19200 bits per second:
//  Serial.begin(19200);  --> already done by DAvE

	// make the pushbutton's pin an input:
	pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
	// read the input pin:
	int buttonState = digitalRead(pushButton);
	// print out the state of the button:
	if (buttonState)
		uart_printf("ON\r\n");
	else
		uart_printf("OFF\r\n");

	delay(1000);        // delay in between reads for stability
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

```
OFF
ON
OFF
ON
ON
OFF
OFF
OFF
OFF
OFF
OFF
OFF
OFF
OFF
```