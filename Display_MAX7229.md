# MAX7219 Led Matrix Display Modules #

The purpose of this article is to demonstrate the use of an interesting LED display module I discovered on the dealextreme website, for example:
![http://img.dxcdn.com/productimages/sku_184854_1.jpg](http://img.dxcdn.com/productimages/sku_184854_1.jpg)

[... http://playground.arduino.cc/Main/LEDMatrix...]


# Hardware Required #

XMC1100 Boot Kit board and MAX7219 Led Matrix Display: https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Max7229_4.JPG

# Circuit #

Connect the MAX7219 Led Matrix display as:
  * Vcc to XMC +5V
  * GND to XMC GND
  * DataIn to Arduino XMC Pin 12
  * CLK to Arduino XMC Pin 11
  * LOAD to Arduino XMC Pin 10

https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Max7229_Conn.JPG

# Code #
## MAX7219 Led Matrix Library ##
On the contrary of the official Arduino MAX7219 Led Matrix library, the XMC1100 version need to be initialized during the 'setup()' function. Therefore you need to:
```
void setup()
{
	lc=LedControl(12,11,10,1);

	/*
     The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call
     */
    lc.shutdown(0,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(0,8);
    /* and clear the display */
    lc.clearDisplay(0);
}
```

The library documentation is available at:
http://playground.arduino.cc/Main/LedControl

## Example 1 ##
Simple program to display all Alphabet characters:
```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************
//We always have to include the library
#include "LedControlMS.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

/*
 This time we have more than one device.
 But all of them have to be initialized
 individually.
 */
void setup()
{
	lc=LedControl(12,11,10,1);

	/*
     The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call
     */
    lc.shutdown(0,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(0,8);
    /* and clear the display */
    lc.clearDisplay(0);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=0;row<8;row++) {
    delay(100);
    lc.setRow(0,row,0b10100000);
    delay(100);
    lc.setRow(0,row,(byte)0);
    for(int i=0;i<row;i++) {
      delay(100);
      lc.setRow(0,row,0b10100000);
      delay(100);
      lc.setRow(0,row,(byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int col=0;col<8;col++) {
    delay(100);
    lc.setColumn(0,col,0b10100000);
    delay(100);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      delay(100);
      lc.setColumn(0,col,0b10100000);
      delay(100);
      lc.setColumn(0,col,(byte)0);
    }
  }
}

/*
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(100);
      lc.setLed(0,row,col,true);
      delay(100);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(100);
        lc.setLed(0,row,col,true);
        delay(100);
      }
    }
  }
}

void loop()
{
	// Some tests...
	//rows();
	//columns();
	//single();

	// Alphabet
	for (int ascii=0; ascii<41; ascii++)
	{
		//lc.clearDisplay(0);
		lc.displayChar(0,ascii);
		delay(delaytime);
	}
  delay(1000);
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
The above example generate something like:
https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Max7229_5.JPG

https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Max7229_D.JPG

https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Max7229_H.JPG

https://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Max7229_Q.JPG