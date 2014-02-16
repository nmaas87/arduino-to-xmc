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
// @Filename      WMath.c
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					math wiring language opcodes.
//
// @Link          http://arduino.cc/en/Reference/HomePage
//
//----------------------------------------------------------------------------
// @Date          28/01/2014 23.23.23
//
//****************************************************************************




//****************************************************************************
// @Project Includes
//****************************************************************************
extern "C" {
  #include "stdlib.h"
  #include "stdint.h"
}
#include "WMath.h"


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
// @Function     map
//
//----------------------------------------------------------------------------
// @Description   Re-maps a number from one range to another.
//					That is, a value of fromLow would get mapped to toLow,
//					a value of fromHigh to toHigh, values in-between to
//					values in-between, etc.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    value: the number to map
// 					fromLow: the lower bound of the value's current range
//					fromHigh: the upper bound of the value's current range
//					toLow: the lower bound of the value's target range
//					toHigh: the upper bound of the value's target range
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Map
//----------------------------------------------------------------------------
// @Date          28/01/2014
//
//****************************************************************************

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
	return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}


//****************************************************************************
// @Function     makeWord
//
//----------------------------------------------------------------------------
// @Description   Combine two bytes into a word.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    h: the MSB byte
// 				  l: the LSB byte
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/makeWord
//----------------------------------------------------------------------------
// @Date          28/01/2014
//
//****************************************************************************

uint16_t makeWord(uint8_t h, uint8_t l)
{
  return (h << 8) | l ;
}


//****************************************************************************
// @Function     randomSeed
//
//----------------------------------------------------------------------------
// @Description   randomSeed() initializes the pseudo-random number generator,
//					causing it to start at an arbitrary point in its random
//					sequence. This sequence, while very long, and random,
//					is always the same.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    long, int - pass a number to generate the seed
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/RandomSeed
//----------------------------------------------------------------------------
// @Date          29/01/2014
//
//****************************************************************************

void randomSeed(uint32_t dwSeed)
{
  if (dwSeed != 0)
  {
    srand(dwSeed) ;
  }
}


//****************************************************************************
// @Function     random
//
//----------------------------------------------------------------------------
// @Description   The random function generates pseudo-random numbers.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    min - lower bound of the random value, inclusive (optional)
//				  max - upper bound of the random value, exclusive
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Random
//----------------------------------------------------------------------------
// @Date          29/01/2014
//
//****************************************************************************

long random(long howbig)
{
  if ( howbig == 0 )
  {
    return 0 ;
  }

  return rand() % howbig;
}

#if 0

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig)
  {
    return howsmall;
  }

  long diff = howbig - howsmall;

  return random(diff) + howsmall;
}
#endif
//****************************************************************************
// @Local Functions
//****************************************************************************





//****************************************************************************
// 							       END OF FILE
//****************************************************************************
