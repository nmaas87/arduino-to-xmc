# Serial Monitor #

Demonstrates the use of the serial monitor (serial comunication via RS232 over USB).

[... http://arduino.cc/en/Tutorial/ ...]


# Hardware Required #

XMC1100 Boot Kit board: ![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg)

# Circuit #

XMC1100 board already has the serial monitor port connected to the JTAG head. Simply connect a terminal software (e.g. Tera Term) on the respective COM port.

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
  HelloWord
 
 This example code is in the public domain.
 */

char msg_buff[80] = "HelloWord!\r\n";

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 19200 bits per second:
//  Serial.begin(19200);  --> already done by DAvE
}

// the loop routine runs over and over again forever:
void loop() {

	// Say Hallo to all Arduino Word!!!
	uart_printf(msg_buff);
  
	// 1 sec delay
	delay(1000);
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

![http://arduino-to-xmc.googlecode.com/svn/wiki/HelloWord.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/HelloWord.jpg)