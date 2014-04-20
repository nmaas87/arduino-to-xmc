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
// @Module        Arduino-compatible timer implementation.
// @Filename      wiring_analog.c
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					analog language opcodes.
//
// @Link          http://arduino.cc/en/Reference
//
//----------------------------------------------------------------------------
// @Date          30/01/2014 01.06.23
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
// @Function      wiring_analog_init
//
//----------------------------------------------------------------------------
// @Description   Initialize the ADC channels.
//					The Arduino board contains a 6 channel .
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Analog
//----------------------------------------------------------------------------
// @Date          31/01/2014
//
//****************************************************************************

void wiring_analog_init(void)
{
#if ARDUINO==1100
	SCU_GENERAL->PASSWD = 0x000000C0;
	SCU_CLK->CGATCLR0 |= 0x00000001;	// disable VADC gating
	while((SCU_CLK->CLKCR)&0x40000000);	// wait for VDDC to stabilize
	SCU_GENERAL->PASSWD = 0x000000C3;

	// Initialize adc on P2.6
	PORT2->IOCR4 &= ~PORT2_IOCR4_PC6_Msk;                              	// Set P2.6 as Input.
	VADC->CLC &= ~VADC_CLC_DISR_Msk;                                      // Enable Clock for the analog section.
	SHS0->SHSCFG = (SHS_SHSCFG_SCWC_Msk);                                 // Enable write access to ANOFF and AREF
	SHS0->SHSCFG &= ~(SHS_SHSCFG_ANOFF_Msk);                              // Toggle on converter.
	*((int*)0x40010500) = 0x01;                                           // workaround to enable converter.
	// SHS0->SHSCFG  TODO: set AREF
	while ((SHS0->SHSCFG & SHS_SHSCFG_ANRDY_Msk) == 0);                   // Wait until converter is ready.

	// VADC->GLOBCFG &= ~VADC_GLOBCFG_DPCAL0_Msk;                         // Enable post-calibration.
	// workaround for calibration
	VADC->GLOBCFG |= VADC_GLOBCFG_DPCAL0_Msk;
	VADC->GLOBCFG |= VADC_GLOBCFG_DPCAL1_Msk;
	VADC->GLOBCFG &= ~VADC_GLOBCFG_SUCAL_Msk;                             // Raising edge on SUCAL to initiate the calibration.
	VADC->GLOBCFG |= VADC_GLOBCFG_SUCAL_Msk;
	// workaround for calibration
	VADC->GLOBCFG |= VADC_GLOBCFG_DPCAL0_Msk;
	VADC->GLOBCFG |= VADC_GLOBCFG_DPCAL1_Msk;
	while ((SHS0->SHSCFG & SHS_SHSCFG_STATE_Msk) != 0);                   // Wait until calibration is finished.
	*((int*)0x480340E0) = 0x80008000;
	*((int*)0x480340E4) = 0x80008000;

	VADC->BRSMR |= 0x01UL;                                                // Gate always enabled.
	VADC->BRSSEL[0] |= VADC_BRSSEL_CHSELG0_Msk;                           // Select P2.6 as input channel.
	VADC->GLOBICLASS[0] |= (0x01UL << VADC_GLOBICLASS_CMS_Pos);           // Select 10-Bit conversion for channel 0.
#endif
}


//****************************************************************************
// @Function      analogRead
//
//----------------------------------------------------------------------------
// @Description   Reads the value from the specified analog pin.
//					The Arduino board contains a 6 ADC channels.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the number of the analog input pin to read from 0 to 5
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/AnalogRead
//----------------------------------------------------------------------------
// @Date          30/01/2014
//
//****************************************************************************

uint32_t analogRead(uint8_t pin)
{
uint32_t value;

	// calibration workaround
		*((int*)0x480340E0) = 0x0;
		*((int*)0x480340E4) = 0x0;
		VADC->GLOBCFG |= VADC_GLOBCFG_SUCAL_Msk;
		// workaround for calibration
		VADC->GLOBCFG |= VADC_GLOBCFG_DPCAL0_Msk;
		VADC->GLOBCFG |= VADC_GLOBCFG_DPCAL1_Msk;
		while ((SHS0->SHSCFG & SHS_SHSCFG_STATE_Msk) != 0);                   // Wait until calibration is finished.
		*((int*)0x480340E0) = 0x80008000;
		*((int*)0x480340E4) = 0x80008000;

	// Select the required channel in channel pending register
	switch(pin)
	{
		// A0	P2.6		AA
		case A0:
			VADC->BRSPND[0] |= VADC_BRSPND_CHPNDG0_Msk;
		break;

		// A1	P2.8		AB
		case A1:
			VADC->BRSPND[0] |= VADC_BRSPND_CHPNDG1_Msk;
			break;

		// A2	P2.9		AC
		case A2:
			VADC->BRSPND[0] |= VADC_BRSPND_CHPNDG2_Msk;
			break;

		// A3	P2.10		AD
		case A3:
			VADC->BRSPND[0] |= VADC_BRSPND_CHPNDG3_Msk;
			break;

		// A4	P2.11		AE
		case A4:
			VADC->BRSPND[0] |= VADC_BRSPND_CHPNDG4_Msk;
			break;

		// A5	P2.2		AF
		case A5:
			VADC->BRSPND[0] |= VADC_BRSPND_CHPNDG5_Msk;
			break;
	}
	while ((VADC->GLOBRES & VADC_GLOBRES_VF_Msk) == 0);               	// Wait until valid flag is set.
	value = (VADC->GLOBRES & VADC_GLOBRES_RESULT_Msk) >> 2;      		// Save the result.

	// Return ADC Conversion
	return (value);
}

//****************************************************************************
// @Function     analogWrite
//
//----------------------------------------------------------------------------
// @Description   Writes an analog value (PWM wave) to a pin. Can be used to
//					light a LED at varying brightnesses or drive a motor at
//					various speeds. After a call to analogWrite(), the pin
//					will generate a steady square wave of the specified duty
//					cycle until the next call to analogWrite() (or a call to
//					digitalRead() or digitalWrite() on the same pin).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the pin to write to.
//				  value: the duty cycle: between 0 (off) and 255 (full on).
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/AnalogWrite
//----------------------------------------------------------------------------
// @Date          02/02/2014
//
//****************************************************************************

void analogWrite(uint8_t pin, uint32_t ulValue)
{
float fDutyCycle;

	fDutyCycle = (float)ulValue*100.0/255.0;

    // Set the pin mode
    switch(pin)
    {
#if 0
		//  3	P0.0		External interrupt / PWM output
    	case 3:
			PWMSP001_Start(&PWMSP001_Handle0);
			PWMSP001_SetDutyCycle(&PWMSP001_Handle0, fDutyCycle);
    		break;

		//  5	P0.2		PWM output
    	case 5:
			PWMSP001_Start(&PWMSP001_Handle1);
			PWMSP001_SetDutyCycle(&PWMSP001_Handle1, fDutyCycle);
    		break;

		//  6	P0.3		PWM output
    	case 6:
			PWMSP001_Start(&PWMSP001_Handle2);
			PWMSP001_SetDutyCycle(&PWMSP001_Handle2, fDutyCycle);
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
			PWMSP001_Start(&PWMSP001_Handle3);
			PWMSP001_SetDutyCycle(&PWMSP001_Handle3, fDutyCycle);
    		break;
#endif

		// 13	P0.7		SPI-SCK / LED output
		case 13:
			PWMSP001_SetDutyCycle(&PWMSP001_Handle1, fDutyCycle);
			break;

    	case LED2:
			PWMSP001_SetDutyCycle(&PWMSP001_Handle0, fDutyCycle);
			break;

    	default:
			if (ulValue < 128)
				digitalWrite(pin, LOW);
			else
				digitalWrite(pin, HIGH);
    		break;

    }
}


//****************************************************************************
// @Local Functions
//****************************************************************************



//****************************************************************************
// 							       END OF FILE
//****************************************************************************

