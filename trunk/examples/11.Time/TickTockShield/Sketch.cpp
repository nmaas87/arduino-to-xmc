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
