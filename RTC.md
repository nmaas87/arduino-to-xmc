# Real Time Clock (RTC) #

Demonstrates the use of the Real Time Clock (serial comunication via RS232 over USB).

[... http://playground.arduino.cc/Code/time ...]


# Hardware Required #

XMC1100 Boot Kit board: ![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg)

# Circuit #

XMC1100 board already has the serial monitor port connected to the JTAG head. Simply connect a terminal software (e.g. TestTerm) on the respective COM port.

XMC1100 has already a Real Time Clock integrated into it. So no need to buy additional chips!

# Code #

**Note:** The 'Wiring\_clock.c' code is based on the DAvE RTC001: RTC\_Timer\_RTC001 application.

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
	The Time library adds timekeeping functionality to Arduino with or without
	external timekeeping hardware. It allows a sketch to get the time and date
	as: second, minute, hour, day, month and year. It also provides time as a
	standard C time_t so elapsed times can be easily calculated and time
	values shared across different platforms.
 */

char msg_buff[80] = "HelloWord!";

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 19200 bits per second:
//  Serial.begin(19200);  --> already done by DAvE

	// Set the Time into RTC
	setTime(00,37,59, 17,02,2014);
}

// the loop routine runs over and over again forever:
void loop() {

	// Format the Date Time string ...
	sprintf(msg_buff,"Date(d-m-y):%d-%d-%d,Time %0d:%0d:%0d\r\n",day(),month(),year(), hour(),minute(),second());

	//Send the data
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
```
This is what you will get on the terminal window:
Date(d-m-y):17-2-2014,Time 0:44:17
Date(d-m-y):17-2-2014,Time 0:44:18
Date(d-m-y):17-2-2014,Time 0:44:19
Date(d-m-y):17-2-2014,Time 0:44:21
Date(d-m-y):17-2-2014,Time 0:44:22
Date(d-m-y):17-2-2014,Time 0:44:23
Date(d-m-y):17-2-2014,Time 0:44:24
Date(d-m-y):17-2-2014,Time 0:44:25
Date(d-m-y):17-2-2014,Time 0:44:26
Date(d-m-y):17-2-2014,Time 0:44:27
Date(d-m-y):17-2-2014,Time 0:44:28
Date(d-m-y):17-2-2014,Time 0:44:29
Date(d-m-y):17-2-2014,Time 0:44:30
```