# Introduction #

Here some deeper documentation of the Arduino Wiring language porting to XMC microcontrollers.

**Note:** this page contains the documentation of only the Wiring language statements that have been ported to XMC microcontrollers.


# Pin mode #

**pinMode(PIN,MODE);**
Set the specified PIN to MODE.

MODE can be:
  * INPUT for receiving digital input
  * INPUT\_PULLUP for receiving digital input having pull-up resistor connected
  * INPUT\_PULLDW for receiving digital input having pull-down resistor connected
  * OUTPUT for sending digital output
  * PWM for setting pulse width modulation output

Example:
```
pinMode(1,INPUT);
```

**Note:** Arduino-to-XMC declares:
```
#define INPUT		0
#define OUTPUT		1
#define INPUT_PULLUP	2
#define INPUT_PULLDW	3
#define PWM		4
```

**Note:** Arduino-to-XMC requires to define the PWM channels as 'pinMode(pin,PWM)'. This is different in respect to standard Arduino Wiring language and is needed to correctly map the pin to the Pulse Width Modulation function (check [Making physical connections to the XMC1100 Arduino™ board](https://code.google.com/p/arduino-to-xmc/wiki/XMC1100_BootKit) to know what are the pins available to generate PWM signals).

# Digital input/output #

**digitalWrite(PIN,DATA);**
Send digtal DATA output to PIN. DATA can be either HIGH or LOW?

Example:
```
pinMode(2,OUTPUT);
digitalWrite(2,HIGH);
```

**digitalRead(PIN);**
Read digital input from PIN. The result can be either HIGH or LOW.

Example:
```
bool PB1state;
 
pinMode(1,INPUT);
PB1state=digitalRead(1);
if(PB1state==HIGH)
{
      uart_printf("PIN1 state is high\n");
} else {
      uart_printf("PIN1 state is low\n");
}
```

# Analog input (ADC) #

**analogRead(ADC\_CHANNEL);**
Read analog input, the output value is between 0-4095 representing 0-5V.

Example:
```
int AnalogData;

AnalogData=analogRead(A0);
uart_printf("Analog channel 0 input is %d\n",AnalogData);

AnalogData=analogRead(A5);
uart_printf("Analog channel 5 input is %d\n",AnalogData);
```

**Note:** ARDUINO-to-XMC pin mapping description is available at https://code.google.com/p/arduino-to-xmc/wiki/XMC1100_BootKit

# Analog output (PWM) #

**analogWrite(PIN, VALUE);**
analogWrite() is used to create a PWM wave on a pin (ref.[Arduino's analogWrite()](http://arduino.cc/en/Reference/analogWrite)).

**Note 1:** the duty cycle VALUE has to be given between 0 (always off) and 255 (always on):
![http://arduino.cc/en/uploads/Tutorial/pwm.gif](http://arduino.cc/en/uploads/Tutorial/pwm.gif)

**Note 2:** the frequency of the PWM signal (i.e., the frequency of a complete on/off cycle) on the Arduino is approximately 490 Hz. On Arduino-to-XMC it is set at 10 KHz (ref [Step 5](http://code.google.com/p/arduino-to-xmc/wiki/HowToCreateLowLevelDriver_XMC1300)).

**Note 3:** since XMC1x00 microcontrollers supports up to 4 hardware PWM generator pins, in case you need more PWM signals, you can use the [SoftwarePWM library](http://code.google.com/p/arduino-to-xmc/wiki/SoftwarePWM).

Example:
```
int ledPin = 9;      // LED connected to digital pin 9
int analogPin = 3;   // potentiometer connected to analog pin 3
int val = 0;         // variable to store the read value

void setup()
{
  pinMode(ledPin, PWM);   // sets the pin as output
}

void loop()
{
  val = analogRead(analogPin);   // read the input pin
  analogWrite(ledPin, val / 4);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
}
```

**Note:** Arduino-to-XMC requires to define the PWM channels as 'pinMode(pin,PWM)'. This is different in respect to standard Arduino Wiring language and is needed to correctly map the pin to the Pulse Width Modulation function (check [Making physical connections to the XMC1100 Arduino™ board](https://code.google.com/p/arduino-to-xmc/wiki/XMC1100_BootKit) to know what are the pins available to generate PWM signals).

# Timing #
**millis(void);**
Return the number of milliseconds since the program execution started.

Example:
```
uart_printf("This has been running for %lu milliseconds.\r\n",millis());
```

**micros();**
Return the number of microseconds since the program execution started.

Example:
```
uart_printf("This has been running for %lu microseconds.\r\n",micros());
```

**delay(MILLISECONDS);**
Stop program execution for MILLISECONDS.
**Note:** this cannot be used within interrupt functions!

Example:
```
delay(1000); // stop for 1000 milliseconds (1 second)
```

**delayMicroseconds(MICROSECONDS);**
Stop program execution for MICROSECONDS.
**Note:** this cannot be used within interrupt functions!

Example:
```
delayMicroseconds(10000); // stop for 10'000 microseconds (10 milliseconds)
```

**Note:** ARDUINO-to-XMC 'delayMicroseconds()' porting description is available at http://code.google.com/p/arduino-to-xmc/wiki/delayMicroseconds

# Random number #

**randomSeed(SEED);**
Choose SEED to be seed of the random number in the program.
SEED must be a number.
To allow the program to ‘attempt’ to randomize the seed put nothing as the SEED.

Example:
To allow program to ‘attempt’ to randomize the seed autmatically
```
randomSeed();
```
To specify a random seed
```
randomSeed(1234);
random(MAX);
```
Generate a random number between 0 and MAX-1.

Example:
```
int myNumber;
myNumber=random(1000); // get a number between 0 and 999
random(MIN,MAX);
```
Generate a random number between MIN and MAX-1.

Example:
```
int myNumber;
myNumber=random(1000,2000); // get a number between 1000 and 1999
```



# Interrupts Handling #

In order to enable/disable the CPU interrupts, the following functions are available 'noInterrupts()' and 'interrupts()'.
**Note:** such functions are just the CMSIS instruction redefinition (ref. 'disable\_irq();' and 'enable\_irq();').


# noInterrupts() #


## Description ##

Disables interrupts (you can re-enable them with interrupts()). Interrupts allow certain important tasks to happen in the background and are enabled by default. Some functions will not work while interrupts are disabled, and incoming communication may be ignored. Interrupts can slightly disrupt the timing of code, however, and may be disabled for particularly critical sections of code.


### Parameters ###

None.


### Returns ###

None.


## Example ##
```
void setup() {}

void loop()
{
  noInterrupts();
  // critical, time-sensitive code here
  interrupts();
  // other code here
}
```


# interrupts() #

## Description ##

Re-enables interrupts (after they've been disabled by noInterrupts()). Interrupts allow certain important tasks to happen in the background and are enabled by default. Some functions will not work while interrupts are disabled, and incoming communication may be ignored. Interrupts can slightly disrupt the timing of code, however, and may be disabled for particularly critical sections of code.


### Parameters ###

None


### Returns ###

None


## Example ##
```
void setup() {}

void loop()
{
  noInterrupts();
  // critical, time-sensitive code here
  interrupts();
  // other code here
}

```