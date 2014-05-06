/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PRINT_H_
#define PRINT_H_

#ifdef __cplusplus

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <inttypes.h>
#include <stdio.h> // for size_t - gives sprintf and other stuff to all sketches & libs

#include "WString.h"
#include "Printable.h"


//****************************************************************************
// @Defines
//****************************************************************************
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2


class Print
{
public:

	virtual size_t write(uint8_t ch) = 0;
    virtual size_t write(const char *p);
    virtual size_t write(const char *p, uint32_t len);

    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);

    size_t println(void);

private:
    size_t printNumber(unsigned long , uint8_t);
    size_t printFloat(double, uint8_t);

};


#endif  // __cplusplus

#endif /* PRINT_H_ */
