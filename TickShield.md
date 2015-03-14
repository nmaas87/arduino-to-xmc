# Introduction #

Tick Tock Shield is a perfect start for beginners of Arduino world. You can learn and practice basic soldering tricks and programming principles when tinkering with this kit. Electronic could be fun even if you have bare technical knowledge cause we get your back by preparing a detailed soldering guide and a fully supported library of programming examples from easy to difficult. Hope you have fun and gain some knowledge with this kit!

![http://www.seeedstudio.com/wiki/images/thumb/3/34/Tickshield_02.jpg/400px-Tickshield_02.jpg](http://www.seeedstudio.com/wiki/images/thumb/3/34/Tickshield_02.jpg/400px-Tickshield_02.jpg)

Tick Tock Shield contains most common resources for a basic electronic project, like buttons, sensors, buzzer and display. After you're done with the soldering task, it turns out to be a geek style alarm clock which can auto adjust the brightness of display and keep in synch with real world time. Model: [SLD90400P](http://www.seeedstudio.com/depot/tick-tock-shield-p-1371.html?cPath=6_7).


## Tick Shield Docus and Arduino Libraries ##
  * [Tick Shield Wiki](http://www.seeedstudio.com/wiki/Tick_Tock_Shield_Kit)
  * [GitHub Library](https://github.com/Seeed-Studio/Starter_Shield)
  * [Tick\_Shield\_Schematic.pdf](http://www.seeedstudio.com/wiki/images/a/a1/Tick_Shield_Schematic.pdf)

# Hardware Required #

XMC1100 Boot Kit board:
https://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_TickTockShield.JPG

# Circuit #

Connect the shield as:
https://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_TickTockShield_on.JPG

# Code #
## TM1636 Library ##
This library is used to control the 4 digit 7-segment display by using only two pins. The Library has been slightly adapted to be working with XMC hardware. In essence, due to the order of the libraries initialization, I had to create yet another initialization function to perform the same as the object creator would do; that is:
```
/*Set the default brightness is BRIGHT_TYPICAL and clear the display*/
void TM1636::init(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
  init();
}
```
To correctly use the display, proceed as follows:
  * declare the diplay static object as usual: 'TM1636 tm1636(7,8);'
  * inside the Arduino's setup() function re-initialize the dispay: 'tm1636.init(7,8);'.

### Example 1 ###
Simple program to measure and display the temperature:
![http://www.seeedstudio.com/wiki/images/b/bb/Measure_Temperature.jpg](http://www.seeedstudio.com/wiki/images/b/bb/Measure_Temperature.jpg)

**Note:** before testing the below example code, you need to include the related Library code into the DAvE project. Libraries code are available under [arduino-to-xmc/libraries](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/libraries/).

```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

/****************************************************************************/
//  Demo function:Get the ambient temperature by the temperature sensor on the
//		Tick Tock Shield and the formula, and it is displayed by the 4-digit
//		display like " 25C" when the temperature is 25 degrees Celsius.
//
//  Author:Frankie.Chu
//  Date:23 September, 2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/
#include <math.h>

#include "TM1636.h"

//--Declare a TM1636 Class object that control the 4-digit display--//
TM1636 tm1636(7,8);

//-Declare the resistance of the resistor that connects with the temperature sensor-//
#define RESISTOR_CONNECT_THERMISTOR	10000//the resistance is 8k ohm
//-------pin definition of temperature sensor-------------//
#define TEMPERATURE_SENSOR	A0

/*Initialization for the hardware.*/
void init_pins()
{
	/*set the temperature sensor that connects with A0 to be input*/
	//pinMode(TEMPERATURE_SENSOR, INPUT);
}

/****************************************************************/
/*Return:int8_t,Temperature that range from -40 to 125 degrees.	*/
int8_t getTemperature()
{
float temperature,resistance;
int a;

	a = analogRead(TEMPERATURE_SENSOR);
	resistance   = (float)(1023-a)*RESISTOR_CONNECT_THERMISTOR/a; //Calculate the resistance of the thermistor
	int B = 3975;
	/*Calculate the temperature according to the following formula.*/
	temperature  = 1/(log(resistance/RESISTOR_CONNECT_THERMISTOR)/B+1/298.15)-273.15;
	return (int8_t)temperature;// the type convert from floating point to 8-bit integer
}
/*********************************************************************/
/*Function:Display 8-bit integer temperature on the 4-digit display. */
/*Parameter:-int8_t temperature,Temperature that range from -40 to 125 degrees. */
/*Return:	  void													*/
void displayTemperature(int8_t temperature)
{
	int8_t temp[4];
	if(temperature < 0)//if the temperature is below zero?
	{
		/*Yes, then the left-most bit will display "-".*/
		temp[0] = INDEX_NEGATIVE_SIGN;
		temperature = abs(temperature);
	}
	else if(temperature < 100)//if temperature >= 0 and temperature < 100?
	{
		/*Yes, then the left-most bit will display nothing.*/
		temp[0] = INDEX_BLANK;
	}
	else //if temperature > 100?
	{
		/*Yes, then the left-most bit will normally display.*/
		temp[0] = temperature/100;
	}
	temperature %= 100;
	temp[1] = temperature / 10;//index of second bit from left
	temp[2] = temperature % 10;//index of the third bit from left
	temp[3] = 12;	          //index of 'C' for celsius degree symbol.
	tm1636.display(temp);
}


void setup()
{
	init_pins();

	/*Set the default brightness is BRIGHT_TYPICAL and clear the display*/
	tm1636.init(7,8);
}
void loop()
{
	int8_t temperature;
	/*Read the ambient temperature and display on the digital tube.*/
	temperature = getTemperature();
	displayTemperature(temperature);
	delay(500);
}

/*The end of the "MeasureTemperature.ino"*/
//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
**Attention:** the above code run properly, but the temperature is not well measered. I suppose is a metter of pin configuration (pull-up or pull-down or open-drain), but I had not enought time to debug.

## TickTockShieldV2 Library ##
The library documentation is available under:
  * [GitHub Library](https://github.com/Seeed-Studio/Starter_Shield)

The Library has been slightly adapted to be working with XMC hardware. In essence, due to the order of the libraries initialization, I had to create yet another initialization function to perform the same as the object creator would do; that is an additional 'object::init()' function.

To correctly use the library objects, proceed as follows:
  * declare the object static variable as usual:
```
TTSDisplay display;
TTSBuzzer buz;
TTSLight light;
TTSTemp temp;
TTSButton button1;
TTSButton button2;
TTSButton button3;
TTSLed led1;
TTSLed led2;
TTSLed led3;
TTSLed led4;
```
  * inside the Arduino's setup() function re-initialize each object:
```
	/*
	 * Tick Shield Component Initialization
	 */
	button1.init(TTSK1);
	button2.init(TTSK2);
	button3.init(TTSK3);
	led1.init(TTSLED1);
	led2.init(TTSLED2);
	led3.init(TTSLED3);
	led4.init(TTSLED4);
	display.init();
	delay(100);
```

### Example 2 ###

Simply test some buttons:
```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

// test of Tick Shield
#include "TTSDisplay.h"
#include "TTSButton.h"
#include "TTSBuzzer.h"
#include "TTSLight.h"
#include "TTSTemp.h"
#include "TTSLed.h"

/*
 * Tick Shield Component Declaration
 */
TTSDisplay display;
TTSBuzzer buz;
TTSLight light;
TTSTemp temp;
TTSButton button1;
TTSButton button2;
TTSButton button3;
TTSLed led1;
TTSLed led2;
TTSLed led3;
TTSLed led4;

/*
 * Static Variables
 */
int state = 0;

void setup()
{
	/*
	 * Tick Shield Component Initialization
	 */
	button1.init(TTSK1);
	button2.init(TTSK2);
	button3.init(TTSK3);
	led1.init(TTSLED1);
	led2.init(TTSLED2);
	led3.init(TTSLED3);
	led4.init(TTSLED4);
	display.init();
	delay(100);

	/*
	 * Display an initial value
	 */
    display.num(2359);
    delay(1000);
}

void loop()
{
    display.pointOn();
    if(button1.pressed())
    {
        delay(10);
        if(button1.pressed())
        {
            state = 1-state;

            if(state)
            	led1.on();
            else
            	led1.off();
        }
        while (button1.released());
    }
    delay(500);
    display.pointOff();
    delay(500);
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
**Attention:** the above code run properly, but not all the library functions has been debug.