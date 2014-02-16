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
// @Module        Arduino-compatible software SPI implementation.
// @Filename      wiring_shift.h
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					shiftIn / shiftOut language opcodes.
//
// @Link          http://arduino.cc/en/Reference/ShiftOut
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
#include "wiring_shift.h"

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
// @Function      shiftOut
//
//----------------------------------------------------------------------------
// @Description   Shifts out a byte of data one bit at a time. Starts from
//					either the most (i.e. the leftmost) or least (rightmost)
//					significant bit. Each bit is written in turn to a data
//					pin, after which a clock pin is pulsed (taken high, then
//					low) to indicate that the bit is available.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    dataPin: the pin on which to output each bit (int)
//				  clockPin: the pin to toggle once the dataPin has been set
//					to the correct value (int)
//				  bitOrder: which order to shift out the bits.
//					(Most Significant Bit First, or, Least Significant Bit First)
//				  value: the data to shift out.
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/ShiftOut
//----------------------------------------------------------------------------
// @Date          01/02/2014
//
//****************************************************************************

void shiftOut(uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder, uint32_t ulVal)
{
	uint8_t i ;

	for ( i=0 ; i < 8 ; i++ )
    {
		if ( ulBitOrder == LSBFIRST )
        {
			digitalWrite( ulDataPin, !!(ulVal & (1 << i)) ) ;
        }
		else
        {
			digitalWrite( ulDataPin, !!(ulVal & (1 << (7 - i))) ) ;
        }

		digitalWrite( ulClockPin, HIGH ) ;
		digitalWrite( ulClockPin, LOW ) ;
	}
}


//****************************************************************************
// @Function      shiftIn
//
//----------------------------------------------------------------------------
// @Description   Shifts in a byte of data one bit at a time. Starts from
//					either the most (i.e. the leftmost) or least (rightmost)
//					significant bit. For each bit, the clock pin is pulled
//					high, the next bit is read from the data line, and then
//					the clock pin is taken low.
//
//----------------------------------------------------------------------------
// @Returnvalue   The value read (byte)
//
//----------------------------------------------------------------------------
// @Parameters    dataPin: the pin on which to input each bit (int)
//				  clockPin: the pin to toggle to signal a read from dataPin
//				  bitOrder: which order to shift out the bits.
//					(Most Significant Bit First, or, Least Significant Bit First)
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/ShiftIn
//----------------------------------------------------------------------------
// @Date          01/02/2014
//
//****************************************************************************

uint32_t shiftIn(uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder)
{
	uint8_t value = 0 ;
	uint8_t i ;

	for ( i=0 ; i < 8 ; ++i )
    {
		digitalWrite( ulClockPin, HIGH ) ;

		if ( ulBitOrder == LSBFIRST )
        {
			value |= digitalRead( ulDataPin ) << i ;
        }
		else
        {
			value |= digitalRead( ulDataPin ) << (7 - i) ;
        }

		digitalWrite( ulClockPin, LOW ) ;
	}

	return value ;
}

//****************************************************************************
// @Local Functions
//****************************************************************************








//****************************************************************************
// 							       END OF FILE
//****************************************************************************
