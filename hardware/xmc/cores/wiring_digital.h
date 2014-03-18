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
// @Filename      wiring_digital.h
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					Wiring Digital language opcodes.
//
// @Link          http://arduino.cc/en/Tutorial/DigitalPins
//
//----------------------------------------------------------------------------
// @Date          24/01/2014 11.45.26
//
//****************************************************************************

#ifndef WIRING_DIGITAL_H_
#define WIRING_DIGITAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/

#include ".\XMC1100\GPIO.h"

/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/

extern void wiring_digital_init(void);

/**
 * Configure behavior of a GPIO pin.
 *
 * @param pin Number of pin to configure.
 * @param mode Mode corresponding to desired pin behavior.
 * @see WiringPinMode
 */
void pinMode(uint8_t pin, uint8_t mode);

/**
 * Writes a (digital) value to a pin.  The pin must have its
 * mode set to OUTPUT or OUTPUT_OPEN_DRAIN.
 *
 * @param pin Pin to write to.
 * @param value Either LOW (write a 0) or HIGH (write a 1).
 * @see pinMode()
 */
void digitalWrite(uint8_t pin, uint8_t value);

/**
 * Read a digital value from a pin.  The pin must have its mode set to
 * one of INPUT, INPUT_PULLUP, and INPUT_PULLDOWN.
 *
 * @param pin Pin to read from.
 * @return LOW or HIGH.
 * @see pinMode()
 */
uint32_t digitalRead(uint8_t pin);


/**
 * Toggle the LED.
 *
 * If the LED is on, turn it off.  If it is off, turn it on.
 *
 * The LED must its mode set to OUTPUT. This can be accomplished
 * portably over all LeafLabs boards by calling pinMode(BOARD_LED_PIN,
 * OUTPUT) before calling this function.
 *
 * @see pinMode()
 */
static inline void toggleLED() {
	P0_7_toggle();
}
#define toggleLED1 toggleLED

static inline void toggleLED2() {
	P0_5_toggle();
}

static inline void toggleLED3() {
	P0_6_toggle();
}

static inline void toggleLED4() {
	P1_2_toggle();
}

static inline void toggleLED5() {
	P1_3_toggle();
}

static inline void toggleLED6() {
	P1_4_toggle();
}

static inline void toggleLED7() {
	P1_5_toggle();
}

#ifdef __cplusplus
}
#endif

#endif /* WIRING_DIGITAL_H_ */
