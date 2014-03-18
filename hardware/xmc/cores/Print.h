/*
 * Print.h
 *
 *  Created on: 11/feb/2014
 *      Author: atti
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
