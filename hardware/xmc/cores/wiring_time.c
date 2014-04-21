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
// @Filename      wiring_time.c
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					Wiring Delay language opcodes.
//
// @Link          http://arduino.cc/en/Reference/Delay
//
//----------------------------------------------------------------------------
// @Date          28/01/2014 00.17.23
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
#define TIMER_1mSec	1000			  /*!< Millisecond to Microsecond ratio */
#define TIMER_ISR_RATIO	1							   /*!< The ISR divider */
#define TIMER_mSecTouSec_RATIO	\
				(TIMER_1mSec/TIMER_ISR_RATIO)	/*!< mS to uS scaling factor*/

//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************
static __IO bool bTimerExpired;
static __IO uint32_t *Timervalue;
static __IO uint32_t *CCU4TimerStart;
static __IO uint32_t *CCU4TimerStopClear;
static __IO uint32_t *CCU4Idlemode;

//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
void m_Timer(void* v);
void m_delayMicroseconds(uint32_t uiUs);

//****************************************************************************
// @Function      wiring_time_init
//
//----------------------------------------------------------------------------
// @Description   Initialize the time module.
//					Needed for delayMicroseconds() function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/HomePage
//----------------------------------------------------------------------------
// @Date          14/04/2014
//
//****************************************************************************

void wiring_time_init(void)
{
	// Initialization of variables and register2variables setup
#if ARDUINO==1100
		Timervalue			= &PWMSP001_Handle0.CC4yRegsPtr->TIMER;
		CCU4TimerStart		= &PWMSP001_Handle0.CC4yRegsPtr->TCSET;
		CCU4TimerStopClear	= &PWMSP001_Handle0.CC4yRegsPtr->TCCLR;
		CCU4Idlemode		= &PWMSP001_Handle0.CC4yKernRegsPtr->GIDLC;
#endif
}

//****************************************************************************
// @Function     millis
//
//----------------------------------------------------------------------------
// @Description   Returns the number of milliseconds since the Arduino board
//					began running the current program.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Millis
//----------------------------------------------------------------------------
// @Date          28/01/2014
//
//****************************************************************************

uint32_t millis(void)
{
	return (SYSTM002_GetTime());
}

//****************************************************************************
// @Function     micros
//
//----------------------------------------------------------------------------
// @Description   Returns the number of microseconds  since the Arduino board
//					began running the current program.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Micros
//----------------------------------------------------------------------------
// @Date          29/01/2014
//
//****************************************************************************

uint32_t micros(void)
{
	return (SYSTM002_GetTime()*TIMER_mSecTouSec_RATIO);
}

//****************************************************************************
// @Function     delay
//
//----------------------------------------------------------------------------
// @Description   Pauses the program for the amount of time (in miliseconds)
//					specified as parameter.
//					There are 1000 milliseconds in a second.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Delay
//----------------------------------------------------------------------------
// @Date          28/01/2014
//
//****************************************************************************

void delay(uint32_t dwMs)
{
handle_t TimerId;

	bTimerExpired = FALSE;

	/*
	 * This funcion uses SysTick Exception for controlling the timer list. Call back function
 	 *	 registered through this function will be called in SysTick exception when the timer is expired.
 	 *	 One shot timers are removed from the timer list, if it expires. To use
 	 *	 this SW timer again it has to be first deleted and then created again.
	 *
	 * 	@param[in]  Period Timer period value in microseconds
	 * 	@param[in]  TimerType Type of Timer(ONE_SHOT/PERIODIC)
	 * 	@param[in]  TimerCallBack Call back function of the timer(No Macros are allowed)
	 * 	@param[in]  pCallBackArgPtr Call back function parameter
	 */
	TimerId = SYSTM002_CreateTimer(dwMs*TIMER_mSecTouSec_RATIO,SYSTM002_ONE_SHOT,m_Timer,NULL);
	if(TimerId != 0)
	{
		//Timer is created successfully
		SYSTM002_StartTimer(TimerId);

		// Wait until timer expires
		while (!bTimerExpired)
			;
		// Delete Timer since is One-Shot
		SYSTM002_DeleteTimer(TimerId);
	}
}

//****************************************************************************
// @Function     delayMicroseconds
//
//----------------------------------------------------------------------------
// @Description   Pauses the program for the amount of time (in microseconds)
//					specified as parameter.
//					There are a thousand microseconds in a millisecond, and
//					a million microseconds in a second.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/DelayMicroseconds
//----------------------------------------------------------------------------
// @Date          14/04/2014
//
//****************************************************************************

void delayMicroseconds(uint32_t uiUs)
{
volatile u_char i;

	if (uiUs < 10)
	{
		// just for loop of 32 clock cycle at 32MHz
		for (i=0; i<32; i++)
			;
	} else {
		if (uiUs > 100) {
			for (i=0; i<(uiUs/100); i++)
				m_delayMicroseconds(100);
			// Run the rest of the delay ...
			//m_delayMicroseconds(uiUs%100);
		} else {
			m_delayMicroseconds(uiUs);
		}
	}
}


//****************************************************************************
// @Local Functions
//****************************************************************************

void m_Timer(void* Temp)
{
	bTimerExpired = TRUE;
}

void m_delayMicroseconds(uint32_t uiUs)
{
uint32_t delaycount, temp_Timer;

	// Start the PWM counter - PWMSP001_Start((PWMSP001_HandleType*)&PWMSP001_Handle0);
	*CCU4Idlemode |=0x08;

	delaycount = (uiUs-4)*64;
	temp_Timer = *Timervalue;

	*CCU4TimerStart		|= 0x01; 	//Start CCU timer

	while(temp_Timer < delaycount)
	{
		temp_Timer = *Timervalue;
	}

	*CCU4TimerStopClear	|= 0x03;	//Stop CCU timer
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
