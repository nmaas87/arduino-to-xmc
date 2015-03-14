# Introduction #

This chapter explain you how to create the Low Level Driver for XMC1100 via DAvE.

You need:
  * The board: Infineon XMC1100 Boot Kit or Infineon XMC1300 Boot Kit
  * Environment: DAVE™ – Free Development Platform for Code Generation (DAVE™ 3.1.8 or later)


# STEP 1 - Create the DAvE CE project #

By 'File->New' (or ALT+SHIFT+N) create a new DAvE CE project:
  * Project Name: 'Arduino\_XMC1300\_LowLevelDriver'
  * DAVE CE Project setting
  * Processor Info: XMC1302-TO38X0200

![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_1.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_1.png)

![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_2.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_2.png)

After pressing 'Finish', you''l get your empty project:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_3.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_3.png)

# STEP 2 - Create the Wiring\_time Low Level driver #
## STEP 2.a - Add 'SYSTM002' Application ##
In order to support the 'delay()', 'millis()', ... functions, it is needed to add the 'SYSTM002' application. To do this, type 'SYSTM002' in the 'App Selection View - Search filter':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_4.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_4.png)
then double click on the 'SYSTM002[1.0.0]' application in order to add one instance to your project. You'll get this in the 'S/W App Connectivy View':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_5.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_5.png)

Now, just to double check that the default setting have not been changed in your DAvE latest release, just double click on the 'SYSTM002/0' image (ref. A), you must have (ref.B):
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_6.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_6.png)

Now, double click on the 'CLK002/0' image (ref. A), you must set 'PCLK= 2\*MCLK' (ref.B):
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_7.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_7.jpg)

## STEP 2.b - Add 'PWMSP001' Application ##
In order to support the 'delayMicroseconds()' function, it is needed to add the 'PWMSP001' application. To do this, type 'PWMSP001' in the 'App Selection View - Search filter' (ref. A). Then double click on the 'PWMSP001[1.0.26]' application (ref. B) in order to add one instance to your project. You'll get this in the 'S/W App Connectivy View':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_8.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_8.jpg)

Now, just double click on the 'PWMSP001/0' image (ref. C), you must set the paramenters as shown in (ref.D):
  * CCU4 resolution = 16;
  * PWM freq = 10000 (Hz).
For more details about the 'delayMicroseconds()', just refer to: [delayMicroseconds()](http://code.google.com/p/arduino-to-xmc/wiki/delayMicroseconds).

# STEP 3 - Create the Wiring\_clock Low Level driver #
In order to support the 'setTime()', 'now()',.. functions, it is needed to add the 'RTC001' application. To do this, type 'RTC001' in the 'App Selection View - Search filter' (ref. A). Then double click on the 'RTC001[1.0.30]' application (ref. B) in order to add one instance to your project. You'll get this in the 'S/W App Connectivy View':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_9.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_9.jpg)

Now, just to double check that the default setting have not been changed in your DAvE latest release, just double click on the 'RTC001/0' image (ref. C), you must have (ref.D).

# STEP 4 - Create the Serial Monitor Low Level driver #
In order to support the Serial Monitor feature (RS232 over USB), it is needed to add the 'UART001' application. To do this, type 'UART001' in the 'App Selection View - Search filter' (ref. A). Then double click on the 'UART001[1.0.30]' application (ref. B) in order to add one instance to your project. You'll get this in the 'S/W App Connectivy View':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_10.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_10.jpg)

Now, just to double check that the default setting have not been changed in your DAvE latest release, just double click on the 'UART001/0' image (ref. C), you must have (ref.D).

# STEP 5 - Create the PWM Low Level driver #
In order to add the additional 3 PWM channels (XMC1300 can support up to 4 PWM channels), it is required to:
  1. add 3 more 'PWMSP001' instances;
  1. configure the related I/O pins.

One 'PWMSP001' instance ('PWMSP001/0') has been already created to support the 'delayMicroseconds()' function (ref. STEP 2.b).
In order to add 3 more instances, type 'PWMSP001' in the 'App Selection View - Search filter'. Then double click on the 'PWMSP001[1.0.26]' application. In the 'App sharability' window, select the already Existing Apps: 'app/ccu4global/0':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_11.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_11.jpg)

**Note:** repeat the above procedure three time, so to have in total 4 instances of the 'PWMSP001' application:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_12.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_12.jpg)

Now, just double click on the 'PWMSP001/x' image, you must set the paramenters as shown in [PWMSP001 settings](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC1100_PWMSP001_settings.jpg):
  * CCU4 resolution = 16;
  * PWM freq = 10000 (Hz).

It is now required to configure the respective pins connected to each of the PWM generator. To do this, select each of the 'PWMSP001/x' images, right-click, 'Manual Pin Assignment':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_13.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_13.jpg)

Now select the 'pin\_directoutput' and the respective pins:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_14.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_14.jpg)
  * PWMSP001/0 is P0.3 (pin 6)
  * PWMSP001/1 is P0.8 (pin 9)
  * PWMSP001/2 is P0.0 (pin 3)
  * PWMSP001/3 is P0.1 (pin 4)

Here for example the pin 3 setting:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_15.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_15.jpg)

# STEP 6 - Generate the Low Level driver code #
We can now trigger the code generation, just click on 'Generate Code':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_16.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_16.jpg)

# STEP 7 - Compile the Low Level driver code #
In order to compile the Low level driver code, just click on 'Build Active Project':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_17.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_17.jpg)

In the console window, you should get:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_18.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_18.jpg)


# STEP 8 - Optimize Low Level driver code #
In order to save code size, it is important to configure the compiler options:
  1. code size optimization:
    * project options (ALT+ENTER): ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_19.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_19.jpg)
    * ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_20.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_20.jpg)

  1. linker optimization:
    * remove unused sections: ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_21.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_21.jpg)

Now, just repeat STEP 7, recompile and you should get much more compact code (about 13k):
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_22.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_22.jpg)

The **dec** field at the end gives the total program size in bytes. The long listing of object files above the Final Size helps to identify bloated code. As you write larger projects, you may find that they use too much space. If that happens, the file-by-file listing will help you track down the culprits.
