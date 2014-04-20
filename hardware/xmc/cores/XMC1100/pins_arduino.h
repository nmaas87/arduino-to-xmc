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
// @Date          24/01/2014 11.45.26
//
//****************************************************************************

#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <XMC1100.h>

//****************************************************************************
// @Defines
//****************************************************************************

#define NUM_DIGITAL_PINS 18
#define NUM_ANALOG_INPUTS 6

// Pins				Arduino
//  0	P1.2		Device transmit UART signal-RXD
//  1	P1.3		Device received UART signal-TXD
//  2	P1.4		External interrupt
//  3	P0.0		External interrupt / PWM output
//  4	P0.1		GPIO
//  5	P0.2		PWM output
//  6	P0.3		PWM output
//  7	P0.4		GPIO
//  8	P0.12		GPIO
//  9	P0.8		PWM output
// 10	P0.9		SPI-SS / PWM output
// 11	P1.1		SPI-MOSI / PWM output
// 12	P1.0		SPI-MISO
// 13	P0.7		SPI-SCK / LED output
// 14	GND			Ground
// 15	P2.3		Analog reference voltage
// 16	P2.1		I2C Data / Address
// 17	P2.0		I2C Clock
// 30	Extended Leds P0.5
// 31	Extended Leds P0.6
// 32	Extended Leds P1.2
// 33	Extended Leds P1.3
// 34	Extended Leds P1.4
// 35	Extended Leds P1.5

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
#define LED1	LED
#define LED2	30	// Extended Leds P0.5
#define LED3	31	// Extended Leds P0.6
#define LED4	32	// Extended Leds P1.2
#define LED5	33	// Extended Leds P1.3
#define LED6	34	// Extended Leds P1.4
#define LED7	35	// Extended Leds P1.5

#define A0 	20
#define A1 	21
#define A2  22
#define A3  23
#define A4  24
#define A5  25


#endif /* PINS_ARDUINO_H_ */
