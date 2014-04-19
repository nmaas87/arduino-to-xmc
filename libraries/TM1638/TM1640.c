//****************************************************************************
// @Module        Arduino-compatible timer implementation.
// @Filename      TM1640.c
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					TM1640 display opcodes.
//
// @Link          http://arduino.cc/en/Reference/Delay
//
//----------------------------------------------------------------------------
// @Date          28/01/2014 00.17.23
//
//****************************************************************************
/*
TM1640.cpp - Library implementation for TM1640.

Copyright (C) 2011 Ricardo Batista (rjbatista <at> gmail <dot> com)

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


//****************************************************************************
// @Project Includes
//****************************************************************************


// #include general HEADER FILES.
#include "TM1640.h"

// #include Arduino HEADER FILES.
#include "Arduino.h"
#include "pins_arduino.h"
#include "wiring_digital.h"


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
// definition for standard hexadecimal numbers
const byte NUMBER_FONT[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01110111, // A
  0b01111100, // B
  0b00111001, // C
  0b01011110, // D
  0b01111001, // E
  0b01110001  // F
};

const byte MINUS = 0b01000000;

// definition for error
const byte ERROR_DATA[] = {
  0b01111001, // E
  0b01010000, // r
  0b01010000, // r
  0b01011100, // o
  0b01010000, // r
  0,
  0,
  0
};

// definition for the displayable ASCII chars
const byte FONT_DEFAULT[] = {
  0b00000000, // (32)  <space>
  0b10000110, // (33)	!
  0b00100010, // (34)	"
  0b01111110, // (35)	#
  0b01101101, // (36)	$
  0b00000000, // (37)	%
  0b00000000, // (38)	&
  0b00000010, // (39)	'
  0b00110000, // (40)	(
  0b00000110, // (41)	)
  0b01100011, // (42)	*
  0b00000000, // (43)	+
  0b00000100, // (44)	,
  0b01000000, // (45)	-
  0b10000000, // (46)	.
  0b01010010, // (47)	/
  0b00111111, // (48)	0
  0b00000110, // (49)	1
  0b01011011, // (50)	2
  0b01001111, // (51)	3
  0b01100110, // (52)	4
  0b01101101, // (53)	5
  0b01111101, // (54)	6
  0b00100111, // (55)	7
  0b01111111, // (56)	8
  0b01101111, // (57)	9
  0b00000000, // (58)	:
  0b00000000, // (59)	;
  0b00000000, // (60)	<
  0b01001000, // (61)	=
  0b00000000, // (62)	>
  0b01010011, // (63)	?
  0b01011111, // (64)	@
  0b01110111, // (65)	A
  0b01111111, // (66)	B
  0b00111001, // (67)	C
  0b00111111, // (68)	D
  0b01111001, // (69)	E
  0b01110001, // (70)	F
  0b00111101, // (71)	G
  0b01110110, // (72)	H
  0b00000110, // (73)	I
  0b00011111, // (74)	J
  0b01101001, // (75)	K
  0b00111000, // (76)	L
  0b00010101, // (77)	M
  0b00110111, // (78)	N
  0b00111111, // (79)	O
  0b01110011, // (80)	P
  0b01100111, // (81)	Q
  0b00110001, // (82)	R
  0b01101101, // (83)	S
  0b01111000, // (84)	T
  0b00111110, // (85)	U
  0b00101010, // (86)	V
  0b00011101, // (87)	W
  0b01110110, // (88)	X
  0b01101110, // (89)	Y
  0b01011011, // (90)	Z
  0b00111001, // (91)	[
  0b01100100, // (92)	\ (this can't be the last char on a line, even in comment or it'll concat)
  0b00001111, // (93)	]
  0b00000000, // (94)	^
  0b00001000, // (95)	_
  0b00100000, // (96)	`
  0b01011111, // (97)	a
  0b01111100, // (98)	b
  0b01011000, // (99)	c
  0b01011110, // (100)	d
  0b01111011, // (101)	e
  0b00110001, // (102)	f
  0b01101111, // (103)	g
  0b01110100, // (104)	h
  0b00000100, // (105)	i
  0b00001110, // (106)	j
  0b01110101, // (107)	k
  0b00110000, // (108)	l
  0b01010101, // (109)	m
  0b01010100, // (110)	n
  0b01011100, // (111)	o
  0b01110011, // (112)	p
  0b01100111, // (113)	q
  0b01010000, // (114)	r
  0b01101101, // (115)	s
  0b01111000, // (116)	t
  0b00011100, // (117)	u
  0b00101010, // (118)	v
  0b00011101, // (119)	w
  0b01110110, // (120)	x
  0b01101110, // (121)	y
  0b01000111, // (122)	z
  0b01000110, // (123)	{
  0b00000110, // (124)	|
  0b01110000, // (125)	}
  0b00000001, // (126)	~
};


//****************************************************************************
// @Global Variables
//****************************************************************************
static byte m_dataPin;
static byte m_clockPin;

//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
void sendCommand(byte cmd);
void sendData(byte address, byte data);
void send(byte d);
void sendChar(byte pos, byte data, boolean dot);
void setDisplayToString(const char* string, const word dots, const byte pos, const byte font[]);

//****************************************************************************
// @Function     TM1640_Init
//
//----------------------------------------------------------------------------
// @Description   Initialize the port for TM1640 communications.
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
// @Date          06/04/2014
//
//****************************************************************************
	
void TM1640_Init(byte dataPin, byte clockPin)
{
  m_dataPin = dataPin;
  m_clockPin = clockPin;
  m_dataPin = dataPin;

  pinMode(m_dataPin, OUTPUT);
  pinMode(m_clockPin, OUTPUT);
  pinMode(m_dataPin, OUTPUT);

  digitalWrite(m_dataPin, HIGH);
  digitalWrite(m_clockPin, HIGH);

  sendCommand(0x40);
  sendCommand(0x80 | (TM1640_ACTIVATE ? 8 : 0) | min(7, TM1640_INTENSITY));

  digitalWrite(m_dataPin, LOW);
  send(0xC0);
  for (int i = 0; i < 16; i++) {
    send(0x00);
  }
  digitalWrite(m_dataPin, HIGH);
}

void TM1640_setDisplayToString(const char* string, const word dots, const byte pos)
{
	setDisplayToString(string, dots, pos, FONT_DEFAULT);
}

void TM1640_setDisplayDigit(byte digit, byte pos, boolean dot)
{
  sendChar(pos,  NUMBER_FONT[digit & 0xF], dot);
}

void TM1640_clearDisplay()
{
  digitalWrite(m_dataPin, LOW);
  send(0xC0);
  for (int i = 0; i < 16; i++) {
    send(0x00);
  }
  digitalWrite(m_dataPin, HIGH);
}




//****************************************************************************
// @Local Functions
//****************************************************************************
void sendCommand(byte cmd)
{
  digitalWrite(m_dataPin, LOW);
  send(cmd);
  digitalWrite(m_dataPin, HIGH);
}

void sendData(byte address, byte data)
{
  sendCommand(0x44);
  digitalWrite(m_dataPin, LOW);
  send(0xC0 | address);
  send(data);
  digitalWrite(m_dataPin, HIGH);
}

void send(byte data)
{
  for (int i = 0; i < 8; i++) {
    digitalWrite(m_clockPin, LOW);
    digitalWrite(m_dataPin, data & 1 ? HIGH : LOW);
    data >>= 1;
    digitalWrite(m_clockPin, HIGH);
  }
}

void sendChar(byte pos, byte data, boolean dot)
{
  sendData(pos, data | (dot ? 0b10000000 : 0));
  
  // necessary for the TM1640
  digitalWrite(m_dataPin, LOW);
  digitalWrite(m_clockPin, LOW);
  digitalWrite(m_clockPin, HIGH);
  digitalWrite(m_dataPin, HIGH);
}

void setDisplayToString(const char* string, const word dots, const byte pos, const byte font[])
{
  for (int i = 0; i < TM1640_DISPLAYS - pos; i++) {
  	if (string[i] != '\0') {
	  sendChar(i + pos, font[string[i] - 32], (dots & (1 << (TM1640_DISPLAYS - i - 1))) != 0);
	} else {
	  break;
	}
  }
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************


