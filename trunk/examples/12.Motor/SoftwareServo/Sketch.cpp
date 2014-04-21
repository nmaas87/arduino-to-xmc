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

