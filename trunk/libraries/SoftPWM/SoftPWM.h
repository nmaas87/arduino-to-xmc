//****************************************************************************
// @Module        Arduino-compatible Software PWM Library implementation.
// @Filename      SoftPWM.cpp
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   An Arduino and Wiring Library to produce PWM signals on any
//					arbitrary pin.
//					It was originally designed for use controlling the
//					brightness of LEDs, but could be modified to control
//					servos and other low frequency PWM controlled devices as well.
//				  Features:
//					-Arbitrary output pins.
//					-Up to 20 different channels can be created.
//					-True zero level, i.e. off = off
//					-Separate fade rates for on and off.
//
// @Link          http://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation
//
//----------------------------------------------------------------------------
// @Date          27/04/2014 23.30.11
//
//****************************************************************************

/* $Id: SoftPWM.h 129 2011-05-27 20:37:08Z bhagman@roguerobotics.com $

  A Software PWM Library
  
  Written by Brett Hagman
  http://www.roguerobotics.com/
  bhagman@roguerobotics.com

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*************************************************/

#ifndef SOFTPWM_H
#define SOFTPWM_H

/*
void SoftPWMBegin(uint8_t defaultPolarity = SOFTPWM_NORMAL);
void SoftPWMSet(int8_t pin, uint8_t value, uint8_t hardset = 0);
void SoftPWMSetPercent(int8_t pin, uint8_t percent, uint8_t hardset = 0);
void SoftPWMEnd(int8_t pin);
void SoftPWMSetFadeTime(int8_t pin, uint16_t fadeUpTime, uint16_t fadeDownTime);
void SoftPWMSetPolarity(int8_t pin, uint8_t polarity);
*/

#include "Arduino.h"

void SoftPWM_Init(void);
void SoftPWM_attach(uint8_t pin);
void SoftPWM_detach(uint8_t pin);
boolean SoftPWM_attached(int8_t pin);
void SoftPWM_SetPercent(int8_t pin, uint8_t percent);

#endif /* SOFTPWM_H */

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
