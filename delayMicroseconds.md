# delayMicroseconds() #

Here the low level driver explanation concerning the function **delayMicroseconds()**.
As any other Arduino Wiring language statements, the low-level driver has been build by using DAvE CE and Infineon's Apps ([DAVE\_Apps\_download](http://www.infineon.com/cms/en/product/promopages/aim-mc/DAVE_3_Support_Portal/DAVE_Apps_download.html)).


# Details #

On XMC1100 it’s is not possible to use the SYSTM002 to generate a microsecond delay function (the fastest time it can support is 60us if we use the SYSTM002, the RM/interrupt chapter states that there are at least a 21Clk cycle latency to each ISR entry. i.e. ~600ns).

Instead, I used the PWMSP001 to do the delay function. This can support from 10us onwards.

## PWMSP001 Setting ##

The settings are shown here:
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_PWMSP001_settings.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_PWMSP001_settings.jpg)

## delayMicroseconds() Initialization ##
After **DAVE\_Init();**, the following code must be executed in order to initialize the **delayMicroseconds()** function:
```
	// Initialisation of variables and register2variables setup
	Timervalue			= &PWMSP001_Handle0.CC4yRegsPtr->TIMER;
	CCU4TimerStart		= &PWMSP001_Handle0.CC4yRegsPtr->TCSET;
	CCU4TimerStopClear	= &PWMSP001_Handle0.CC4yRegsPtr->TCCLR;
	CCU4Idlemode		= &PWMSP001_Handle0.CC4yKernRegsPtr->GIDLC;

	*CCU4Idlemode |=0x02;

```

## delayMicroseconds() Implementation ##
The function code is:
```
void delayMicroseconds(uint32_t dwUs)
{
	uint32_t delaycount, temp_Timer;

	delaycount = (uiUs-4)*64;
	temp_Timer = *Timervalue;

	*CCU4TimerStart		|= 0x01; //Start CCU timer

	while(temp_Timer < delaycount)
	{
		temp_Timer = *Timervalue;
	}

	*CCU4TimerStopClear	|= 0x03;//Stop CCU timer
}
```