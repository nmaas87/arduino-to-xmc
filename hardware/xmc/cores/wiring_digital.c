/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//****************************************************************************
// @Module        Arduino-compatible digital I/O implementation.
// @Filename      wiring_digital.C
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					Wiring Digital language opcodes.
//
// @Link          http://arduino.cc/en/Tutorial/DigitalPins
//
//----------------------------------------------------------------------------
// @Date          24/01/2014 11.45.26
//
//****************************************************************************



//****************************************************************************
// @Project Includes
//****************************************************************************

#include <DAVE3.h>
#include "Arduino.h"

//****************************************************************************
// @Macros
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************


//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

//****************************************************************************
// @Function      wiring_digital_init
//
//----------------------------------------------------------------------------
// @Description   Initialize the I/O ports.
//					The Arduino board contains a 13 digital I/Os.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Digital
//----------------------------------------------------------------------------
// @Date          31/01/2014
//
//****************************************************************************

void wiring_digital_init(void)
{
	// XMC1100 Boot Kit has additional 6 LEDs, set as output
		P0_5_set_mode(OUTPUT_PP_GP);	// LED2 (LED1 is pin13)
		P0_6_set_mode(OUTPUT_PP_GP);	// LED3
		//	P1_2_set_mode(OUTPUT_PP_GP);	// LED4 (also TX)
		//	P1_3_set_mode(OUTPUT_PP_GP);	// LED5 (also RX)
		P1_4_set_mode(OUTPUT_PP_GP);	// LED6
		P1_5_set_mode(OUTPUT_PP_GP);	// LED7

	// Turn-Off extended LEDs
		P0_5_set();
		P0_6_set();
		P1_4_set();
		P1_5_set();

}


//****************************************************************************
// @Function     pinMode
//
//----------------------------------------------------------------------------
// @Description   Configures the specified pin to behave either as an input or
//					an output. See the description of digital pins for details
//					on the functionality of the pins.
//					As of Arduino 1.0.1, it is possible to enable the internal
//					pullup resistors with the mode INPUT_PULLUP.
//					Additionally, the INPUT mode explicitly disables the
//					internal pullups.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the number of the pin whose mode you wish to set
//				  mode: INPUT, OUTPUT, or INPUT_PULLUP
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/PinMode
//----------------------------------------------------------------------------
// @Date          27/01/2014
//
//****************************************************************************

void pinMode(uint8_t pin, uint8_t mode)
{
uint16_t outputMode = -1;

    // Select mode
    switch(mode)
    {
		case INPUT:
			outputMode = INPUT_TS;			// Input TriState
			break;

		case INPUT_PULLDW:					// Input Pull-Down
			outputMode = INPUT_PD;
			break;

		case INPUT_PULLUP:					// Input Pull-Up
			outputMode = INPUT_PU;
			break;

		case OUTPUT:
			outputMode = OUTPUT_PP_GP;		// Output Push-Pull
			break;
    }

    // Set the pin mode
    switch(pin)
    {
		//  0	P1.2		Device transmit UART signal-RXD
    	case 0:
    		P1_2_set_mode(outputMode);
    		break;

		//  1	P1.3		Device received UART signal-TXD
    	case 1:
    		P1_3_set_mode(outputMode);
    		break;

		//  2	P1.4		External interrupt
    	case 2:
    		P1_4_set_mode(outputMode);
    		break;

		//  3	P0.0		External interrupt / PWM output
    	case 3:
    		P0_0_set_mode(outputMode);
    		break;

		//  4	P0.1		GPIO
    	case 4:
    		P0_1_set_mode(outputMode);
    		break;

		//  5	P0.2		PWM output
    	case 5:
    		P0_2_set_mode(outputMode);
    		break;

		//  6	P0.3		PWM output
    	case 6:
    		P0_3_set_mode(outputMode);
    		break;

		//  7	P0.4		GPIO
    	case 7:
    		P0_4_set_mode(outputMode);
    		break;

		//  8	P0.12		GPIO
    	case 8:
    		P0_12_set_mode(outputMode);
    		break;

		//  9	P0.8		PWM output
    	case 9:
    		P0_8_set_mode(outputMode);
    		break;

		// 10	P0.9		SPI-SS / PWM output
    	case 10:
    		P0_9_set_mode(outputMode);
    		break;

		// 11	P1.1		SPI-MOSI / PWM output
    	case 11:
    		P1_1_set_mode(outputMode);
    		break;

		// 12	P1.0		SPI-MISO
    	case 12:
    		P1_0_set_mode(outputMode);
    		break;

		// 13	P0.7		SPI-SCK / LED output
    	case 13:
    		if (mode == PWM)
    			PWMSP001_Start(&PWMSP001_Handle1);
    		else
    			P0_7_set_mode(outputMode);
    		break;

		// 14	GND			Ground

		// 15	P2.3		Analog reference voltage
    	case 15:
    		P2_3_set_mode(outputMode);
    		break;

		// 16	P2.1		I2C Data / Address
    	case 16:
    		P2_1_set_mode(outputMode);
    		break;

		// 17	P2.0		I2C Clock
    	case 17:
    		P2_0_set_mode(outputMode);
    		break;

		// LED2 30	Extended Leds P0.5
		case LED2:
			if (mode == PWM)
				PWMSP001_Start(&PWMSP001_Handle0);
			else
				P0_5_set_mode(outputMode);
			break;

		// LED3 31	Extended Leds P0.6
		case LED3:
			P0_6_set_mode(outputMode);
			break;

		// LED4
		case LED4:
			P1_2_set_mode(outputMode);
			break;

		// LED5
		case LED5:
			P1_3_set_mode(outputMode);
			break;

		// LED6
		case LED6:
			P1_4_set_mode(outputMode);
			break;

		// LED7
		case LED7:
			P1_5_set_mode(outputMode);
			break;

		// A0	P2.6		AA
    	case A0:
    		P2_6_set_mode(outputMode);
			break;

		// A1	P2.8		AB
    	case A1:
    		P2_8_set_mode(outputMode);
			break;

		// A2	P2.9		AC
    	case A2:
    		P2_9_set_mode(outputMode);
			break;

		// A3	P2.10		AD
    	case A3:
    		P2_10_set_mode(outputMode);
			break;

		// A4	P2.11		AE
    	case A4:
    		P2_11_set_mode(outputMode);
			break;

		// A5	P2.2		AF
    	case A5:
    		P2_2_set_mode(outputMode);
			break;
    }

}

//****************************************************************************
// @Function     digitalRead
//
//----------------------------------------------------------------------------
// @Description   Reads the value from a specified digital pin, either HIGH or LOW.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the number of the digital pin you want to read
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/DigitalRead
//----------------------------------------------------------------------------
// @Date          27/01/2014
//
//****************************************************************************

uint32_t digitalRead(uint8_t pin)
{
uint32_t val = -1;

    // Read the pin
	switch(pin)
	{
		//  0	P1.2		Device transmit UART signal-RXD
		case 0:
			val = P1_2_read();
			break;

		//  1	P1.3		Device received UART signal-TXD
		case 1:
			val = P1_3_read();
			break;

		//  2	P1.4		External interrupt
		case 2:
			val = P1_4_read();
			break;

		//  3	P0.0		External interrupt / PWM output
		case 3:
			val = P0_0_read();
			break;

		//  4	P0.1		GPIO
		case 4:
			val = P0_1_read();
			break;

		//  5	P0.2		PWM output
		case 5:
			val = P0_2_read();
			break;

		//  6	P0.3		PWM output
		case 6:
			val = P0_3_read();
			break;

		//  7	P0.4		GPIO
		case 7:
			val = P0_4_read();
			break;

		//  8	P0.12		GPIO
		case 8:
			val = P0_12_read();
			break;

		//  9	P0.8		PWM output
		case 9:
			val = P0_8_read();
			break;

		// 10	P0.9		SPI-SS / PWM output
		case 10:
			val = P0_9_read();
			break;

		// 11	P1.1		SPI-MOSI / PWM output
		case 11:
			val = P1_1_read();
			break;

		// 12	P1.0		SPI-MISO
		case 12:
			val = P1_0_read();
			break;

		// 13	P0.7		SPI-SCK / LED output
		case 13:
			val = P0_7_read();
			break;

		// 14	GND			Ground
		case 14:
			val = LOW;
			break;

		// 15	P2.3		Analog reference voltage
		case 15:
			val = P2_3_read();
			break;

		// 16	P2.1		I2C Data / Address
		case 16:
			val = P2_1_read();
			break;

		// 17	P2.0		I2C Clock
		case 17:
			val = P2_0_read();
			break;
	}

	return ((val?HIGH:LOW));
}


//****************************************************************************
// @Function     digitalWrite
//
//----------------------------------------------------------------------------
// @Description   Write a HIGH or a LOW value to a digital pin.
//					If the pin has been configured as an OUTPUT with pinMode(),
//					its voltage will be set to the corresponding value:
//					5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the pin number
//				  value: HIGH or LOW
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/DigitalWrite
//----------------------------------------------------------------------------
// @Date          27/01/2014
//
//****************************************************************************

void digitalWrite(uint8_t pin, uint8_t value)
{
    // Set the pin
    if (value == HIGH)
    {
		switch(pin)
		{
			//  0	P1.2		Device transmit UART signal-RXD
			case 0:
				P1_2_set();
				break;

			//  1	P1.3		Device received UART signal-TXD
			case 1:
				P1_3_set();
				break;

			//  2	P1.4		External interrupt
			case 2:
				P1_4_set();
				break;

			//  3	P0.0		External interrupt / PWM output
			case 3:
				P0_0_set();
				break;

			//  4	P0.1		GPIO
			case 4:
				P0_1_set();
				break;

			//  5	P0.2		PWM output
			case 5:
				P0_2_set();
				break;

			//  6	P0.3		PWM output
			case 6:
				P0_3_set();
				break;

			//  7	P0.4		GPIO
			case 7:
				P0_4_set();
				break;

			//  8	P0.12		GPIO
			case 8:
				P0_12_set();
				break;

			//  9	P0.8		PWM output
			case 9:
				P0_8_set();
				break;

			// 10	P0.9		SPI-SS / PWM output
			case 10:
				P0_9_set();
				break;

			// 11	P1.1		SPI-MOSI / PWM output
			case 11:
				P1_1_set();
				break;

			// 12	P1.0		SPI-MISO
			case 12:
				P1_0_set();
				break;

			// 13	P0.7		SPI-SCK / LED output
			case 13:
				P0_7_set();
				break;

			// 14	GND			Ground

			// 15	P2.3		Analog reference voltage
			case 15:
				P2_3_set();
				break;

			// 16	P2.1		I2C Data / Address
			case 16:
				P2_1_set();
				break;

			// 17	P2.0		I2C Clock
			case 17:
				P2_0_set();
				break;

			// LED2
			case LED2:
				P0_5_set();
				break;

			// LED3
			case LED3:
				P0_6_set();
				break;

			// LED4
			case LED4:
				P1_2_set();
				break;

			// LED5
			case LED5:
				P1_3_set();
				break;

			// LED6
			case LED6:
				P1_4_set();
				break;

			// LED7
			case LED7:
				P1_5_set();
				break;
		}

    } else {
		switch(pin)
		{
			//  0	P1.2		Device transmit UART signal-RXD
			case 0:
				P1_2_reset();
				break;

			//  1	P1.3		Device received UART signal-TXD
			case 1:
				P1_3_reset();
				break;

			//  2	P1.4		External interrupt
			case 2:
				P1_4_reset();
				break;

			//  3	P0.0		External interrupt / PWM output
			case 3:
				P0_0_reset();
				break;

			//  4	P0.1		GPIO
			case 4:
				P0_1_reset();
				break;

			//  5	P0.2		PWM output
			case 5:
				P0_2_reset();
				break;

			//  6	P0.3		PWM output
			case 6:
				P0_3_reset();
				break;

			//  7	P0.4		GPIO
			case 7:
				P0_4_reset();
				break;

			//  8	P0.12		GPIO
			case 8:
				P0_12_reset();
				break;

			//  9	P0.8		PWM output
			case 9:
				P0_8_reset();
				break;

			// 10	P0.9		SPI-SS / PWM output
			case 10:
				P0_9_reset();
				break;

			// 11	P1.1		SPI-MOSI / PWM output
			case 11:
				P1_1_reset();
				break;

			// 12	P1.0		SPI-MISO
			case 12:
				P1_0_reset();
				break;

			// 13	P0.7		SPI-SCK / LED output
			case 13:
				P0_7_reset();
				break;

			// 14	GND			Ground

			// 15	P2.3		Analog reference voltage
			case 15:
				P2_3_reset();
				break;

			// 16	P2.1		I2C Data / Address
			case 16:
				P2_1_reset();
				break;

			// 17	P2.0		I2C Clock
			case 17:
				P2_0_reset();
				break;

			// LED2
			case LED2:
				P0_5_reset();
				break;

			// LED3
			case LED3:
				P0_6_reset();
				break;

			// LED4
			case LED4:
				P1_2_reset();
				break;

			// LED5
			case LED5:
				P1_3_reset();
				break;

			// LED6
			case LED6:
				P1_4_reset();
				break;

			// LED7
			case LED7:
				P1_5_reset();
				break;
		}
    }
}




//****************************************************************************
// 							       END OF FILE
//****************************************************************************
