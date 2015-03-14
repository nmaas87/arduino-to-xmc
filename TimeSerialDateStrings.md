# Real Time Clock (RTC):: example code illustrating Time library date strings #

Demonstrates the use of the Real Time Clock (serial comunication via RS232 over USB) with date formatting as string (e.g. '23:09:27  Tue 19 Feb 2014').

[... http://playground.arduino.cc/Code/time ...]


# Hardware Required #

XMC1100 Boot Kit board: ![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg)

# Circuit #

XMC1100 board already has the serial monitor port connected to the JTAG head. Simply connect a terminal software (e.g. Tera Term) on the respective COM port.

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
 * TimeSerialDateStrings.pde
 * example code illustrating Time library date strings
 *
 * This sketch adds date string functionality to TimeSerial.pde
 *
 */

char msg_buff[80] = "HelloWord!";

void setup()  {
  //Serial.begin(19200);

	// Set the Time into RTC
	setTime(23,04,11, 19,02,2014);
}

void loop()
{

	// digital clock display of the time
	sprintf(msg_buff,"%02d:%02d:%02d  %s",hour(),minute(),second(),  dayStr(weekday()));
		sprintf(msg_buff,"%s %d %s %d\r\n",msg_buff, day(),monthStr(month()), year());

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
This is what you will get on the terminal window:
```
23:09:35  Tue 19 Feb 2014
23:09:36  Tue 19 Feb 2014
23:09:37  Tue 19 Feb 2014
23:09:38  Tue 19 Feb 2014
23:09:39  Tue 19 Feb 2014
23:09:40  Tue 19 Feb 2014
23:09:41  Tue 19 Feb 2014
23:09:43  Tue 19 Feb 2014
23:09:44  Tue 19 Feb 2014
23:09:45  Tue 19 Feb 2014
23:09:46  Tue 19 Feb 2014
```