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
