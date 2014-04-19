/*
TM1640.h - Library for TM1640.

Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef TC1640_H_
#define TC1640_H_

#ifdef __cplusplus
extern "C"{
#endif

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/
#include "Arduino.h"

//****************************************************************************
// @Defines
//****************************************************************************
#define	TM1640_ACTIVATE		true
#define	TM1640_INTENSITY	7
#define TM1640_DISPLAYS		16


//****************************************************************************
// @Typedefs
//****************************************************************************
extern const byte NUMBER_FONT[];
extern const byte MINUS;
extern const byte ERROR_DATA[];
extern const byte FONT_DEFAULT[];


/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/

void TM1640_Init(byte dataPin, byte clockPin);
void TM1640_setDisplayToString(const char* string, const word dots, const byte pos);
void TM1640_setDisplayDigit(byte digit, byte pos, boolean dot);
void TM1640_clearDisplay();

#ifdef __cplusplus
}
#endif

#endif /* TC1640_H_ */
