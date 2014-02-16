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

#ifndef WIRING_CLOCK_H_
#define WIRING_CLOCK_H_

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/

#include "Arduino.h"


//****************************************************************************
// @Defines
//****************************************************************************

//convenience macros to convert to and from tm years
#define  tmYearToCalendar(Y) ((Y) + 1970)  // full four digit year
#define  CalendarYrToTm(Y)   ((Y) - 1970)
#define  tmYearToY2k(Y)      ((Y) - 30)    // offset is from 2000
#define  y2kYearToTm(Y)      ((Y) + 30)

/*==============================================================================*/
/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)
#define DAYS_PER_WEEK (7UL)
#define SECS_PER_WEEK (SECS_PER_DAY * DAYS_PER_WEEK)
#define SECS_PER_YEAR (SECS_PER_WEEK * 52UL)
#define SECS_YR_2000  (946684800UL) // the time at the start of y2k

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define dayOfWeek(_time_)  ((( _time_ / SECS_PER_DAY + 4)  % DAYS_PER_WEEK)+1) // 1 = Sunday
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)  // this is number of days since Jan 1 1970
#define elapsedSecsToday(_time_)  (_time_ % SECS_PER_DAY)   // the number of seconds since last midnight

// The following macros are used in calculating alarms and assume the clock is set to a date later than Jan 1 1971
// Always set the correct time before setting alarms
#define previousMidnight(_time_) (( _time_ / SECS_PER_DAY) * SECS_PER_DAY)  // time at the start of the given day
#define nextMidnight(_time_) ( previousMidnight(_time_)  + SECS_PER_DAY )   // time at the end of the given day
#define elapsedSecsThisWeek(_time_)  (elapsedSecsToday(_time_) +  ((dayOfWeek(_time_)-1) * SECS_PER_DAY) )   // note that week starts on day 1
#define previousSunday(_time_)  (_time_ - elapsedSecsThisWeek(_time_))      // time at the start of the week for the given time
#define nextSunday(_time_) ( previousSunday(_time_)+SECS_PER_WEEK)          // time at the end of the week for the given time

/* Useful Macros for converting elapsed time to a time_t */
#define minutesToTime_t ((M)) ( (M) * SECS_PER_MIN)
#define hoursToTime_t   ((H)) ( (H) * SECS_PER_HOUR)
#define daysToTime_t    ((D)) ( (D) * SECS_PER_DAY) // fixed on Jul 22 2011
#define weeksToTime_t   ((W)) ( (W) * SECS_PER_WEEK)

#define dt_MAX_STRING_LEN 9 // length of longest date string (excluding terminating null)
#define dt_SHORT_STR_LEN  3 // the length of short strings

//****************************************************************************
// @Typedefs
//****************************************************************************

typedef enum {
	timeNotSet,
	timeNeedsSync,
	timeSet
}  timeStatus_t ;

/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/

/*============================================================================*/
/*  time and date functions   */
uint8_t     hour();            // the hour now
uint8_t     hourFormat12();    // the hour now in 12 hour format
bool	 	isAM();            // returns true if time now is AM
bool		isPM();            // returns true if time now is PM
uint8_t     minute();          // the minute now
uint8_t     second();          // the second now
uint8_t     day();             // the day now
uint8_t     weekday();         // the weekday now (Sunday is day 1)
uint8_t     month();           // the month now  (Jan is month 1)
uint8_t     year();            // the full four digit year: (2009, 2010 etc)

uint32_t 	now();   			// return the current time as seconds since Jan 1 1970
void    	setTime(uint8_t hr,uint8_t min,uint8_t sec,uint8_t day,uint8_t month,uint16_t yr);

char* monthStr(uint8_t month);
char* dayStr(uint8_t day);

#endif /* WIRING_CLOCK_H_ */
