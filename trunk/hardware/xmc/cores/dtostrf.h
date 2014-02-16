//****************************************************************************
// @Module        Arduino-compatible dtostrf implementation.
// @Filename      dtostrf.h
// @Project       Arduino_XMC
//----------------------------------------------------------------------------
// @Controller    Infineon XMC1x00
//
// @Compiler      GCC
//
// @Codegenerator DAvE 3.0 Compatible
//
// @Description   This file contains low level functions to implement the
//					dtostrf conversion.
//
// @Link          http://arduino.cc/en/Reference/Delay
//
//----------------------------------------------------------------------------
// @Date          10/02/2014 00.17.23
//
//****************************************************************************


#ifndef DTOSTRF_H_
#define DTOSTRF_H_

char * dtostrf(float val, int width, unsigned int precision, char *buf);


#endif /* DTOSTRF_H_ */
