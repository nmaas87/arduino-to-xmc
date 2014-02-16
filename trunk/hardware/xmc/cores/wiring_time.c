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
static volatile bool bTimerExpired;


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
void m_Timer(void* v);


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
	return SYSTM002_GetTime();
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
// @Date          29/01/2014
//
//****************************************************************************

void delayMicroseconds(uint32_t dwUs)
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
	TimerId = SYSTM002_CreateTimer(dwUs,SYSTM002_ONE_SHOT,m_Timer,NULL);
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
// @Local Functions
//****************************************************************************

void m_Timer(void* Temp)
{
	bTimerExpired = TRUE;
}




//****************************************************************************
// 							       END OF FILE
//****************************************************************************
