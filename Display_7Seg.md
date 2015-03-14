# 7-segment LED Display Modules #

The purpose of this article is to demonstrate the use of an very simple LED display module, for example (I have used a 1' model HS-1106AMS):

![http://upload.wikimedia.org/wikipedia/commons/thumb/0/02/7_segment_display_labeled.svg/220px-7_segment_display_labeled.svg.png](http://upload.wikimedia.org/wikipedia/commons/thumb/0/02/7_segment_display_labeled.svg/220px-7_segment_display_labeled.svg.png) ![http://upload.wikimedia.org/wikipedia/commons/thumb/a/ad/Seven_segment_02_Pengo.jpg/280px-Seven_segment_02_Pengo.jpg](http://upload.wikimedia.org/wikipedia/commons/thumb/a/ad/Seven_segment_02_Pengo.jpg/280px-Seven_segment_02_Pengo.jpg)

[...http://playground.arduino.cc/Main/SevenSegmentLibrary...]

**Note:** in some cases (e.g. Very minimal uC application) the usage of a single digit display, like a 7-segment display, is enought for the given purpose.

# Hardware Required #

XMC1100 Boot Kit board: ![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg)

# Circuit #

Connect the 7-segment display as:
  * Cathode to XMC GND
  * A to Arduino XMC Pin0 via 220Ohm resistor
  * B to Arduino XMC Pin1 via 220Ohm resistor
  * C to Arduino XMC Pin2 via 220Ohm resistor
  * D to Arduino XMC Pin3 via 220Ohm resistor
  * E to Arduino XMC Pin4 via 220Ohm resistor
  * F to Arduino XMC Pin5 via 220Ohm resistor
  * G to Arduino XMC Pin6 via 220Ohm resistor
![http://learn.parallax.com/sites/default/files/content/propeller-c-tutorials/simple-circuits/7-segment/7seg-schematic.png](http://learn.parallax.com/sites/default/files/content/propeller-c-tutorials/simple-circuits/7-segment/7seg-schematic.png)

Resulting in:
http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_7segment_8.JPG

**Note**: in my test I left unconnected the D.P.

# Code #
## Seg7 Library ##
The Seg7 library has been dowloaded from [Seg7](https://github.com/DepletionMode/seg7) and compiled under Arduino-to-XMC. No changes were required (you find XMC version under [Libraries](http://arduino-to-xmc.googlecode.com/svn/trunk/libraries/)).

## Example ##
Simple program to count from 0 to 9:
![http://learn.parallax.com/sites/default/files/content/propeller-c-tutorials/simple-circuits/7-segment/7seg-count.png](http://learn.parallax.com/sites/default/files/content/propeller-c-tutorials/simple-circuits/7-segment/7seg-count.png)

**Note:** before testing the below example code, you need to include the related Library code into the DAvE project. Libraries code are available under [arduino-to-xmc/libraries](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/libraries/).

```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

/*  7 segment display counter

    This sketch counts from 0 to 9 on a 7-segment display

    The circuit:

           A
          ____
         |    |
      F  |____|  B
         | G  |
      E  |____|  C
                o DP
           D

      7-segment 10-pin package:

      10 9 8 7 6
       ________
      |   __   |
      |  |__|  |
      |  |__|o |
      |________|

      1 2 3 4 5

      * If you have a common cathode device, uncomment line X
      * You only need to connect either pin 3 OR pin 8
      * 1 (E) connect to arduino pin 4
      * 2 (D) connect to arduino pin 3
      * 3 common-anode connect to +, common-cathode to -
      * 4 (C) connect to arduino pin 2
      * 5 (DP) connect to arduino pin 7
      * 6 (B) connect to arduino pin 1
      * 7 (A) connect to arduino pin 0
      * 8 common-anode connect to +, common-cathode to -
      * 9 (F) connect to arduino pin 5
      * 10 (G) connect to arduino pin 6

      This example is placed in the Public Domain and is free
      for your use/modification for any purpose
*/

#include "Seg7.h"

Seg7 s7;  // object

void setup()   {
  s7.set_cathode(true);  				// set for common-cathode
  s7.attach(0, 1, 2, 3, 4, 5, 6, 7);  	// attach a single 7-segment display
}

void loop()
{
  for (int i = 0; i < 10; i++) {  // count from 0-9
    s7.write(i);
    delay(1000);  // wait 1 second
  }
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```
The above example generate something like:
http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_7segment_5.JPG
http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_7segment_9.JPG
(I could't take a video).