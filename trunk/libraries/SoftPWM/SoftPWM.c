//****************************************************************************
// @Module        Arduino-compatible Software PWM Library implementation.
// @Filename      SoftPWM.cpp
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   An Arduino and Wiring Library to produce PWM signals on any
//					arbitrary pin.
//					It was originally designed for use controlling the
//					brightness of LEDs, but could be modified to control
//					servos and other low frequency PWM controlled devices as well.
//				  Features:
//					-Arbitrary output pins.
//					-Up to 20 different channels can be created.
//					-True zero level, i.e. off = off
//					-Separate fade rates for on and off.
//
// @Link          http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation
//
//----------------------------------------------------------------------------
// @Date          27/04/2014 23.30.11
//
//****************************************************************************


/* $Id: SoftPWM.cpp 132 2012-02-14 04:15:05Z bhagman@roguerobotics.com $

  A Software PWM Library

  Written by Brett Hagman
  http://www.roguerobotics.com/
  bhagman@roguerobotics.com

  Minor modification by Paul Stoffregen to support different timers

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*************************************************/

//****************************************************************************
// @Project Includes
//****************************************************************************

// #include general HEADER FILES.
#include "SoftPWM.h"

// #include Arduino HEADER FILES.
#include "Arduino.h"
#include <DAVE3.h>


//****************************************************************************
// @Macros
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************
#define TIMER_1mSec	1000			  /*!< Millisecond to Microsecond ratio */

#define SOFTPWM_TIME		   (16*TIMER_1mSec/100)/*!< 1/60 Hz = 16 [msec] */
/*!<
 * in total there are 16 timers, but delay() is using one and each
 * soft PWM is using two
 */
#define SOFTPWM_MAXCHANNELS 	7

//****************************************************************************
// @Typedefs
//****************************************************************************
typedef struct
{
	boolean m_isOn;
	boolean m_bState;
	int8_t	m_pin;
	uint8_t m_pwmvalue;
	handle_t m_TimerId_on;
	handle_t m_TimerId_off;
} softPWMChannel;

//****************************************************************************
// @Imported Global Variables
//****************************************************************************

//****************************************************************************
// @Global Variables
//****************************************************************************
softPWMChannel m_channels[SOFTPWM_MAXCHANNELS];      /*!< array of soft PWM */
uint8_t m_counter = 0;								/*!< allocated soft PWM */

//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
void m_Timer_PWM_0(void* Temp);


//****************************************************************************
// @Function     SoftPWMBegin
//
//----------------------------------------------------------------------------
// @Description   Initializes the library - sets up the timer and other tasks.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    optional defaultPolarity
//						allows all newly defined pins to take on this polarity.
//						Values: SOFTPWM_NORMAL, SOFTPWM_INVERTED
//
//----------------------------------------------------------------------------
// @Link          http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation
//----------------------------------------------------------------------------
// @Date          27/04/2014
//
//****************************************************************************

void SoftPWM_Init(void)
{
uint8_t i;

	// Set default PWM values
	for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
	{
		m_channels[i].m_isOn 		= false;
		m_channels[i].m_pin 		= -1;
		m_channels[i].m_bState 		= false;
		m_channels[i].m_pwmvalue 	= 0;
		m_channels[i].m_TimerId_on	= 0;
		m_channels[i].m_TimerId_off	= 0;
	}
	m_counter = 0;
}


//****************************************************************************
// @Function     attach
//
//----------------------------------------------------------------------------
// @Description   attach the software PWM generator to the pin (start it).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          .
//----------------------------------------------------------------------------
// @Date          27/04/2014
//
//****************************************************************************

void SoftPWM_attach(uint8_t pin)
{
int8_t firstfree = -1;  // first free index
uint8_t i;

	// If the pin isn't already set, search it
	for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
	{
		// get the first free pin if available
		if (firstfree < 0 && (m_channels[i].m_pin < 0)) {
			firstfree = i;
			break;
		}
	}
	// Add it...
	if ( (pin >= 0) && (firstfree >= 0) )
	{
		// we have a free pin we can use
			m_channels[firstfree].m_pin = pin;

		// now prepare the pin for output
			pinMode(pin, OUTPUT);

		// turn it off to start (no glitch)
		  digitalWrite(pin, LOW);

		// update soft PWM counter
		  m_counter = m_counter + 1;
	}
}


//****************************************************************************
// @Function     detach
//
//----------------------------------------------------------------------------
// @Description   detach the software PWM generator from the pin (stop it).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          .
//----------------------------------------------------------------------------
// @Date          27/04/2014
//
//****************************************************************************

void SoftPWM_detach(uint8_t pin)
{
uint8_t i;

	for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
	{
		if (pin >= 0 && (m_channels[i].m_pin == pin))
		{
			// now disable the pin (put it into INPUT mode)
				pinMode(m_channels[i].m_pin, INPUT);

			// remove the pin
				m_channels[i].m_pin	= -1;
				m_channels[i].m_isOn= false;

			// update soft PWM counter
				m_counter = m_counter - 1;

			break;
		}
	}
}

//****************************************************************************
// @Function     attached
//
//----------------------------------------------------------------------------
// @Description   return if the software PWM generator is attached to any pin.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          .
//----------------------------------------------------------------------------
// @Date          27/04/2014
//
//****************************************************************************

boolean SoftPWM_attached(int8_t pin)
{
uint8_t i;

	for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
	{
		if (pin >= 0 && (m_channels[i].m_pin == pin))
		{
			break;
		}
	}
	return(m_channels[i].m_isOn);
}


//****************************************************************************
// @Function     SoftPWMSetPercent
//
//----------------------------------------------------------------------------
// @Description   Initializes the library - sets up the timer and other tasks.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters
//					pin is the output pin.
//					percent is a value between 0 and 100 (inclusive).
//
//----------------------------------------------------------------------------
// @Link          http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation
//----------------------------------------------------------------------------
// @Date          27/04/2014
//
//****************************************************************************

void SoftPWM_SetPercent(int8_t pin, uint8_t percent)
{
uint8_t i=0;
uint32_t time;

	// If the pin isn't already set ...
	for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
	{
		if ( (pin >= 0) && (m_channels[i].m_pin == pin) )
		{
			// Kill existing timers ...
				if (m_channels[i].m_TimerId_on != 0) {
					SYSTM002_DeleteTimer(m_channels[i].m_TimerId_on);
					m_channels[i].m_TimerId_on = 0;
				}
				if (m_channels[i].m_TimerId_off != 0) {
					SYSTM002_DeleteTimer(m_channels[i].m_TimerId_off);
					m_channels[i].m_TimerId_off = 0;
				}

			// check percentage setting
			if (percent == 0)
				digitalWrite(pin, LOW);		// 0% is OFF

			else if (percent == 100)
				digitalWrite(pin, HIGH);	// 100% is ON

			else if (m_channels[i].m_pwmvalue != percent)
			{
				// ...We will get a PWM period of approximately 60Hz (~16ms).
				time = ((uint32_t)(percent))*SOFTPWM_TIME;
				m_channels[i].m_TimerId_on =
					SYSTM002_CreateTimer( time,
											SYSTM002_PERIODIC,
											m_Timer_PWM_0,(void*)i);

				time = ((uint32_t)(100-percent))*SOFTPWM_TIME;
				m_channels[i].m_TimerId_off =
					SYSTM002_CreateTimer( time,
											SYSTM002_PERIODIC,
											m_Timer_PWM_0,(void*)i);

				if ( (m_channels[i].m_TimerId_on != 0) &&
					 (m_channels[i].m_TimerId_off != 0) )
				{
					// set the pin (and exit)
						m_channels[i].m_isOn	 = true;
						m_channels[i].m_pwmvalue = percent;

					//Start the timer
						SYSTM002_StopTimer(m_channels[i].m_TimerId_on);
						SYSTM002_StartTimer(m_channels[i].m_TimerId_off);
						m_channels[i].m_bState = true;
				}
			}
			break;
		}
	}
}


//****************************************************************************
// @Local Functions
//****************************************************************************


//****************************************************************************
// @Function     m_Timer
//
//----------------------------------------------------------------------------
// @Description   Software PWM interrupt handler.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation
//----------------------------------------------------------------------------
// @Date          27/04/2014
//
//****************************************************************************

void m_Timer_PWM_0(void* Temp)
{
volatile uint8_t i= (uint8_t)Temp;

	if (m_channels[i].m_isOn)
	{
		if (!m_channels[i].m_bState)
		{
			// turn it OFF
				digitalWrite(m_channels[i].m_pin, LOW);

			//Start the timer
				SYSTM002_StopTimer(m_channels[i].m_TimerId_on);
				SYSTM002_StartTimer(m_channels[i].m_TimerId_off);
				m_channels[i].m_bState = true;

		} else {
			// turn it ON
				digitalWrite(m_channels[i].m_pin, HIGH);

			//Start the timer
				SYSTM002_StopTimer(m_channels[i].m_TimerId_off);
				SYSTM002_StartTimer(m_channels[i].m_TimerId_on);
				m_channels[i].m_bState = false;
		}
	}
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
