# Motor Shield (ARDUMOTO) #

This is a motor shield for Arduino that will control two DC motors. Based on the L298 H-bridge, the Ardumoto can drive up to 2 amps per channel. The board takes its power from the same Vin line as the Arduino board,  includes blue and yellow LEDs to indicate active direction, and all driver lines are diode protected from back EMF. The new version of this shield allows for either 3.3 or 5v logic, a separate and more robust VIN connection, and the PWM input has moved to pin 3.

[... https://www.sparkfun.com/products/9815 ...]

# Hardware Required #

![https://cdn.sparkfun.com//assets/parts/3/8/4/9/09815-01.jpg](https://cdn.sparkfun.com//assets/parts/3/8/4/9/09815-01.jpg)

The Motor Shield (ARDUMOTO) is coming from Sparkfun...


# Circuit #

Just plug the Ardumoto on top of XMC1100 Arduino board:
http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Ardumoto_1.JPG


# Example: motor A #
```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************
/*
 5/22/2012
  Timothy Holmberg
  SparkFun Electronics

  This code includes the ddition of fade in and out PWM. Also a stop feature. And the addition of individual functions for motor control

  This was a revision of the example sketch that originated from Pete Dokter's code for Arduino that shows very basically how to control an Ardumoto
  motor driver shield with a 5V Arduino controller board. http://www.sparkfun.com/datasheets/DevTools/Arduino/Ardumoto_test_3.pde

  This also includes parts of the Fading Example,  Created 1 Nov 2008 By David A. Mellis, modified 30 Aug 2011 By Tom Igoe http://arduino.cc/en/Tutorial/Fading

*/

const int pwm_a = 3;	//PWM control for motor outputs 1 and 2 is on digital pin 3
const int dir_a = 12;	//direction control for motor outputs 1 and 2 is on digital pin 12
int val = 0;     		//value for fade


/* Let's take a moment to talk about these functions. The forw and back functions are simply designating the direction the motors will turn once they are fed a PWM signal.
If you only call the forw, or back functions, you will not see the motors turn. On a similar note the fade in and out functions will only change PWM, so you need to consider
the direction you were last set to. In the code above, you might have noticed that I called forw and fade in the same grouping. You will want to call a new direction, and then
declare your pwm fade. There is also a stop function.
*/

void forw() // no pwm defined
{
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
}

void back() // no pwm defined
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
}

void forward() //full speed forward
{
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  analogWrite(pwm_a, 255);    //set both motors to run at (100/255 = 39)% duty cycle
}

void backward() //full speed backward
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  analogWrite(pwm_a, 255);   //set both motors to run at 100% duty cycle (fast)
}

void stopped() //stop
{
  digitalWrite(dir_a, LOW); //Set motor direction, 1 low, 2 high
  analogWrite(pwm_a, 0);    //set both motors to run at 100% duty cycle (fast)
}

void fadein()
{
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
  {
     // sets the value (range from 0 to 255):
    analogWrite(pwm_a, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void fadeout()
{
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(pwm_a, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}
}

void astop()                   //stop motor A
{
  analogWrite(pwm_a, 0);
}


void setup()
{
  pinMode(pwm_a, PWM);  	//Set control pins to be PWM
  pinMode(dir_a, OUTPUT);	//Set control pins to be output

  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
}

void loop()
{
  forw();         //Set Motors to go forward Note : No pwm is defined with the for function, so that fade in and out works
  fadein();       //fade in from 0-255
  delay(1000);

  forward();      //continue full speed forward
  delay(1000);

  fadeout();      //Fade out from 255-0
  delay(1000);    //Wait one second

  stopped();      // stop for 2 seconds
  delay(2000);


  back();         //Set motors to revers. Note : No pwm is defined with the back function, so that fade in and out works
  fadein();       //fade in from 0-255
  delay(1000);

  backward();     //full speed backward
  delay(1000);

  fadeout();      //Fade out from 255-0
  delay(1000);
}

//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## EXECUTION ##

This is what you'll get:
http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_Ardumoto_2.JPG

**Note:** remember to supply the L298 H-bridge by appling an appropiate voltage to Vin (I did connect to +5V via a floating cable as visible...).