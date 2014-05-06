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
// @Module        Arduino-compatible digital I/O implementation.
// @Filename      pins_arduino.h
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   XMC1100 pin mapping to Arduino Uno board.
//
// @Link          http://arduino.cc/en/Hacking/PinMapping
//
//----------------------------------------------------------------------------
// @Date          06/05/2014 22.25.33
//
//****************************************************************************

#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <XMC4500.h>

//****************************************************************************
// @Defines
//****************************************************************************

#define NUM_DIGITAL_PINS 18
#define NUM_ANALOG_INPUTS 6

// Pins				Arduino
//  0	P0.0		Device transmit UART signal-RXD
//  1	P0.1		Device received UART signal-TXD
// 13	P1.0		SPI-SCK / LED output
// 14	GND			Ground

// 30	Extended Leds P1.0

// A0	P2.6		AA
// A1	P2.8		AB
// A2	P2.9		AC
// A3	P2.10		AD
// A4	P2.11		AE
// A5	P2.2		AF

static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

static const uint8_t SDA = 18;
static const uint8_t SCL = 19;
static const uint8_t LED_BUILTIN = 13;

#define LED		13	// Standard Arduino LED pin 13
#define LED1	LED	// Extended Leds P1.1
#define LED2	30	// Extended Leds P1.0
#define BUTTON1	B1	// Extended Button P1.14
#define BUTTON2	B2	// Extended Button P1.15


#define A0 	20
#define A1 	21
#define A2  22
#define A3  23
#define A4  24
#define A5  25


#endif /* PINS_ARDUINO_H_ */
