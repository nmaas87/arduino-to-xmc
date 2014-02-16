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
// @Module        Arduino-compatible clock implementation.
// @Filename      wiring_clock.c
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					clock language opcodes.
//
// @Link          http://playground.arduino.cc/Code/time
//
//----------------------------------------------------------------------------
// @Date          31/01/2014 22.38.34
//
//****************************************************************************




//****************************************************************************
// @Project Includes
//****************************************************************************

#include <DAVE3.h>
#include "Arduino.h"
#include "wiring_clock.h"

#include <string.h>

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

static RTC001_TimeHandle CurrentTime;
static char buffer[dt_MAX_STRING_LEN+1];

char monthShortNames_P[]  = "ErrJanFebMarAprMayJunJulAugSepOctNovDec";
char dayShortNames_P[]  = "ErrSunMonTueWedThrFriSat";

timeStatus_t td_status = timeNotSet;

//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

void refreshCache(void);

//****************************************************************************
// @Function     setTime
//
//----------------------------------------------------------------------------
// @Description   Set the RTC time to teh given value.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://playground.arduino.cc/Code/time
//----------------------------------------------------------------------------
// @Date          28/01/2014
//
//****************************************************************************

void setTime(uint8_t hr, uint8_t min, uint8_t sec, uint8_t dy, uint8_t mnth, uint16_t yr)
{
uint32_t status;

	// Disable Timer for set operation
	RTC001_Disable();

	// Compile the Time Structure
	CurrentTime.Year = yr;
	CurrentTime.Month = mnth;
	CurrentTime.Days = dy;
	CurrentTime.Hours = hr;
	CurrentTime.Min = min;
	CurrentTime.Sec = sec;
	status = RTC001_Clock_SetTime(&CurrentTime);
	if(status == DAVEApp_SUCCESS)
	{
		//Success
		RTC001_Enable();
		td_status = timeSet;
	}
}

//****************************************************************************
// @Function      now
//
//----------------------------------------------------------------------------
// @Description   This function returns the time in seconds since the
//					epoch time(01/01/1970).
//
//----------------------------------------------------------------------------
// @Returnvalue   Time in seconds since the epoch time(01/01/1970).
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://playground.arduino.cc/Code/time
//----------------------------------------------------------------------------
// @Date          28/01/2014
//
//****************************************************************************

uint32_t now()
{
uint32_t status;
time_t time_value;

	status = RTC001_Time(&time_value);
	if(status == DAVEApp_SUCCESS)
		return (time_value);
	else
		return 0L;
}


//****************************************************************************
// @Function      hour, minute, second, day, weekday, month, year functions
//
//----------------------------------------------------------------------------
// @Description   Function collection to get the current hour, minute, ... .
//
//----------------------------------------------------------------------------
// @Returnvalue   ...hour, minute, or ...
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://playground.arduino.cc/Code/time
//----------------------------------------------------------------------------
// @Date          01/02/2014
//
//****************************************************************************

uint8_t hour() { // the hour now
	refreshCache();
	return (CurrentTime.Hours);
}


uint8_t hourFormat12() { // the hour for the given time in 12 hour format
	refreshCache();
	if( CurrentTime.Hours == 0 )
		return 12; // 12 midnight
	else if( CurrentTime.Hours  > 12)
		return CurrentTime.Hours - 12 ;
	else
		return CurrentTime.Hours ;
}

bool isAM() { // returns true if time now is AM
  return !isPM(now());
}

bool isPM() { // returns true if PM
  return (hour() >= 12);
}


uint8_t minute() { // the minute for the given time
	refreshCache();
	return (CurrentTime.Min);
}


uint8_t second() {  // the second for the given time
	refreshCache();
	return (CurrentTime.Sec);
}


uint8_t day() { // the day for the given time (0-6)
	refreshCache();
	return (CurrentTime.Days);
}

uint8_t weekday() {   // Sunday is day 1
	refreshCache();
	return (CurrentTime.DaWe);
}


uint8_t month(){
	refreshCache();
	return (CurrentTime.Month);
}


uint8_t year() {  // as in Processing, the full four digit year: (2009, 2010 etc)
	refreshCache();
	return (CurrentTime.Year);
}


//****************************************************************************
// @Function      monthStr, dayStr functions
//
//----------------------------------------------------------------------------
// @Description   Function to return date strings.
//
//----------------------------------------------------------------------------
// @Returnvalue   .. month or day string (3 characters)...
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://playground.arduino.cc/Code/time
//----------------------------------------------------------------------------
// @Date          01/02/2014
//
//****************************************************************************

char* monthStr(uint8_t month)
{
	for (int i=0; i < dt_SHORT_STR_LEN; i++)
		buffer[i] = (monthShortNames_P[i+ (month*dt_SHORT_STR_LEN)]);
	buffer[dt_SHORT_STR_LEN] = 0;
	return buffer;
}

char* dayStr(uint8_t day)
{
	uint8_t index = day*dt_SHORT_STR_LEN;
	for (int i=0; i < dt_SHORT_STR_LEN; i++)
		buffer[i] = (dayShortNames_P[index + i]);
	buffer[dt_SHORT_STR_LEN] = 0;
	return buffer;
}

//****************************************************************************
// @Local Functions
//****************************************************************************

void refreshCache(void)
{
	// Read current time
	RTC001_Clock_GetTime(&CurrentTime);
}



//****************************************************************************
// 							       END OF FILE
//****************************************************************************
