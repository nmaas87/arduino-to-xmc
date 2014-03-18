/*
 * Main.c
 *
 */

#define ARDUINO_MAIN
#include "Arduino.h"

#include <XMC1100.h>		//SFR declarations of the selected device
#include <DAVE3.h>

// #include Arduino HEADER FILES.
#include "pins_arduino.h"
#include "wiring_digital.h"
#include "wiring_time.h"
#include "wiring_clock.h"

/**
 * @brief This function will transmit the input data to PC Hyperterminal
 *
 * @param[in]: p start address of character buffer
 * @return void
 * */
void uart_printf(const char *p)
{
	while(*p){
		while( 0 != ((UART001_Handle0.UartRegs->TRBSR) & (USIC_CH_TRBSR_TFULL_Msk)));
		UART001_WriteData(UART001_Handle0,*p);
		p++;
	}

}

int main(void)
{

	/*
	  *  Wiring Initialization
	  */
	wiring_digital_init();
	wiring_analog_init();

	/*
	  *  Periferals Initialization
	  */
	DAVE_Init();

	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		//yield();
	}
}

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

/*
  Conditionals - If statement

 This example demonstrates the use of if() statements.
 It reads the state of a potentiometer (an analog input) and turns on an LED
 only if the LED goes above a certain threshold level. It prints the analog value
 regardless of the level.

 The circuit:
 * potentiometer connected to analog pin 0.
 Center pin of the potentiometer goes to the analog pin.
 side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 13 to ground

 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components for this example.

 created 17 Jan 2009
 modified 9 Apr 2012
 by Tom Igoe

This example code is in the public domain.

http://arduino.cc/en/Tutorial/IfStatement

 */

// These constants won't change:
const int analogPin = A0;    // pin that the sensor is attached to
const int ledPin = 13;       // pin that the LED is attached to
const int threshold = 400;   // an arbitrary threshold level that's in the range of the analog input

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication at 19200 bits per second:
//  Serial.begin(19200);  --> already done by DAvE
}

void loop() {
  // read the value of the potentiometer:
  int analogValue = analogRead(analogPin);

  // if the analog value is high enough, turn on the LED:
  if (analogValue > threshold) {
    digitalWrite(ledPin, HIGH);
    uart_printf("ON\r\n");
  }
  else {
    digitalWrite(ledPin,LOW);
    uart_printf("OFF\r\n");
  }

  delay(1);        // delay in between reads for stability
}


//****************************************************************************
// 							       END OF FILE
//****************************************************************************
