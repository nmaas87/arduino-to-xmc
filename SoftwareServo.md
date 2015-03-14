# The Software Servo Library #

The Software Servo Library can drive servos on all of XMC's pins simultaneously. The API is patterned after the wiring.org servo library but the code is different. You are not limited to 8 servos, but you must call the SoftwareServo::refresh() method at least once every 20ms or so to keep your servos updating.

[... http://playground.arduino.cc/ComponentLib/Servo ...]

**Note:** the SoftwareServo library can support as many servomotors you like, you can use any digital port for the servo signal...

# Hardware Required #

http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_SoftWareServoMotor.JPG

The Servo Motors are coming from Conrad...


# Circuit #

We connect three wires to the XMC1100 board:
  * +5V to Red Servo1 cable
  * GND to Brown Servo1 cable
  * pin 8 to Orange Servo1 cable
  * +5V to Red Servo2 cable
  * GND to Brown Servo2 cable
  * pin 7 to Orange Servo2 cable

**Note:** above connections are just as for example, any other pin can be configured for the servo signals.

# Example: two servo counter-moving #

**Note:** before testing the below example code, you need to include the related Library code into the DAvE project. Libraries code are available under [arduino-to-xmc/libraries](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/libraries/).

```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************
#include "SoftwareServo.h"

#define STEP					90/6

unsigned long previousMillis 	= 0;
unsigned long previousMilli2 	= 0;
bool bUP 						= TRUE;
unsigned char pos 				= 0;
SoftwareServo myservo1, myservo2;  // create servo objects to control two servo


void setup()
{
	myservo1.attach(7);  // attaches the servo on pin 7 to the servo object
	myservo2.attach(8);  // attaches the servo on pin 8 to the servo object
	myservo1.write(0);   // sets the servo position to 0
	myservo2.write(180); // sets the servo position to 180
}

void loop()
{
unsigned long currentMillis = millis();

	// here is where you'd put code that needs to be running all the time.
	if(currentMillis - previousMilli2 > 50)
	{
		previousMilli2 = currentMillis;
		if (bUP)
		{
			myservo1.write(pos);                 // sets the servo position according to the scaled value
			myservo2.write(180-pos);             // sets the servo position according to the scaled value
			pos += STEP;
			if (pos >= 180) {
				bUP = FALSE;
				pos = 180;
			}
		} else {
			myservo1.write(pos);                 // sets the servo position according to the scaled value
			myservo2.write(180-pos);             // sets the servo position according to the scaled value
			pos -= STEP;
			if (pos <= 0) {
				bUP = TRUE;
				pos = 0;
			}
		}
		delay(15);
	}

	// Servo(s) refresh only every 20 msec
	if(currentMillis - previousMillis > 20)
	{
		// save the last time you refresh them...
		previousMillis = currentMillis;

		myservo1.refresh();
		myservo2.refresh();
	}
}


//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

## EXECUTION ##

Observing the two servo movement, you'll see the two servo motors moving in the opposite direction.