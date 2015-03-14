Arduino™ Wiring language is a widely used language for embedded system programming. It is very easy and immediate to create little microcontrollers applications such as to control servos, motors, inputs, outputs, displays, etc.. .
This project has the aim to port the Arduino™ Wiring language to the XMC microcontrollers. I've started the project by using the Infineon XMC1100. Then I've continued by using the Infineon XMC1300 ([see details...](http://www.infineon.com/cms/en/product/microcontrollers/32-bit-industrial-microcontrollers-based-on-arm-registered-cortex-tm-m/32-bit-xmc1000-industrial-microcontrollers-arm-registered-cortex-tm-m0/channel.html?channel=db3a30433c1a8752013c1aa35a6a0029)). Now I'm testing the XMC4500 and the XMC2GO as well...

## Why Arduino to XMC? ##

I've started this porting project because I like very much the simplicity and intuitive Arduino Wiring language, but I'm not confortable with the absence of a professional debug (Arduino 'serial.print()' is good only for basic debug purposes). Merging Arduino to XMC I'll get the best of both environments:
  * ARM 32-bit power;
  * Arduino's simplicity;
  * Arduino's various examples;
  * Arduino's various libraries;
  * XMC professional Integrated Development Environment (IDE), Eclipse based;
  * XMC professional debug environment (Tasking plug-in);
  * XMC application based code generator (DAvE).

## Details ##

This project has the aim to:
  * port the intuitive Arduino Wiring Language to XMC microcontrollers;
  * create the Arduino/hardware/xmc/cores/ library;
  * port the existing Arduino tutorials (http://arduino.cc/en/Tutorial/HomePage) examples code;
  * port the top most important Arduino Libraries (displays, sensors, motors,...).

## Getting Started ##
![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1100.jpg) ![http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1300.jpg](http://www.infineon.com/export/sites/default/media/products/Microcontrollers/devel_tools_SW/XMC1300.jpg)
https://arduino-to-xmc.googlecode.com/svn/wiki/XMC4500_RelaxKit.JPG
![http://arduino-to-xmc.googlecode.com/svn/wiki/XMC2GO.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/XMC2GO.jpg)

  * The XMC1100 board: [Infineon XMC1100 Boot Kit](http://www.infineon.com/cms/en/product/microcontrollers/32-bit-industrial-microcontrollers-based-on-arm-registered-cortex-tm-m/32-bit-xmc4000-industrial-microcontrollers-arm-registered-cortex-tm-m4/xmc-development-tools-software-and-kits/xmc1000-starter-kits/boot-kit-xmc1100/channel.html?channel=db3a30433cfb5caa013d115dda020665) (you can get one with integrated debugger from [hitex](http://ehitex.com/evaluation-boards/infineon/456/xmc1100-boot-kit-kit_xmc11_boot_001) for about 16€)
  * The XMC2GO board: [XMC2GO](http://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC_2GO_XMC1100_V1/productType.html?productType=db3a304443537c4e01436ccecb5d154f) (you can get one for about 5€).
  * The XMC1300 board: [Infineon XMC1300 Boot Kit](http://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-registered-cortex-tm-m/32-bit-xmc4000-industrial-microcontroller-arm-registered-cortex-tm-m4/xmc-development-tools-software-and-kits/xmc1000-starter-kits/boot-kit-xmc1300/channel.html?channel=db3a30433cfb5caa013d115ee9e7066c)
  * The XMC4500 board: [Infineon XMC4500 Relax Kit](http://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-registered-cortex-tm-m/32-bit-xmc4000-industrial-microcontroller-arm-registered-cortex-tm-m4/xmc-development-tools-software-and-kits/xmc4500-relax/relax-lite-kit/channel.html?channel=db3a30433a747525013a97f6e265721e)
  * XMC1100 Board pin connections: [Making physical connections to the XMC1100 Arduino™ board](https://code.google.com/p/arduino-to-xmc/wiki/XMC1100_BootKit)
  * Environment: [DAVE™ – Free Development Platform for Code Generation](http://www.infineon.com/cms/en/product/microcontrollers/32-bit-industrial-microcontrollers-based-on-arm-registered-cortex-tm-m/32-bit-xmc4000-industrial-microcontrollers-arm-registered-cortex-tm-m4/xmc-development-tools-software-and-kits/dave-tm-–-free-development-platform-for-code-generation/channel.html?channel=db3a30433580b3710135afc117a9563f) (DAVE™ 3.1.8 - it's free!)
  * DAvE Forum: [...](http://www.infineonforums.com/forums/7-DAVE-trade-Forum)
  * Libraries: [Source](http://code.google.com/p/arduino-to-xmc/source/checkout) or directly via SVN [trunk](https://code.google.com/p/arduino-to-xmc/source/browse/trunk)
  * Releases: [tags](http://code.google.com/p/arduino-to-xmc/source/browse/#svn%2Ftags) or directly via SVN [trunk](https://code.google.com/p/arduino-to-xmc/source/browse/trunk)
  * Examples:  via SVN [examples](https://code.google.com/p/arduino-to-xmc/source/browse/trunk/examples).

## Arduino to XMC Documentation ##
  * [Arduino to XMC library layering](http://code.google.com/p/arduino-to-xmc/wiki/Arduino_to_XMC_library_layering)
  * [Arduino to XMC Wiring Language Documentation](http://code.google.com/p/arduino-to-xmc/wiki/Documentation)
  * [Tested Shields](https://code.google.com/p/arduino-to-xmc/wiki/TestedShields)


## Arduino to XMC First steps ##
  * [First Steps](http://code.google.com/p/arduino-to-xmc/wiki/FirstSteps)

## Examples ##
The following examples source codes can be downloaded from [code trunk](https://code.google.com/p/arduino-to-xmc/source/browse/trunk).

### 01.Basics ###
  * [Blink](http://code.google.com/p/arduino-to-xmc/wiki/Blink)
  * [Pushbutton](https://code.google.com/p/arduino-to-xmc/wiki/DigitalReadSerial)
  * [HelloWord](https://code.google.com/p/arduino-to-xmc/wiki/HelloWord)
  * ... more will come

## 02.Digital ##
  * [Blink Without Delay](http://code.google.com/p/arduino-to-xmc/wiki/BlinkWithoutDelay)
  * [Debounce](https://code.google.com/p/arduino-to-xmc/wiki/Debounce)
  * ... more will come

## 03.Analog ##
  * [Fade](https://code.google.com/p/arduino-to-xmc/wiki/Fade)
  * [Joystick Shield](https://code.google.com/p/arduino-to-xmc/wiki/JoystickShield)
  * [Smoothing: smooth multiple readings of an analog input.](https://code.google.com/p/arduino-to-xmc/wiki/Smoothing)
  * [SoftwarePWM](http://code.google.com/p/arduino-to-xmc/wiki/SoftwarePWM)
  * ... more will come

### 05.Control Structures ###
This section contain basic examples covering C/C++ language syntax. They are referencing Arduino learning tutorials.
  * [Array](https://code.google.com/p/arduino-to-xmc/wiki/Array)
  * [ForLoop](https://code.google.com/p/arduino-to-xmc/wiki/ForLoop)
  * [IfStatement](https://code.google.com/p/arduino-to-xmc/wiki/IfStatement)
  * ... more will come

### 07.Displays ###
This section contain basic examples covering various commercial displays.
  * [7-Segment Display](https://code.google.com/p/arduino-to-xmc/wiki/Display_7Seg)
  * [TM1640 Display](https://code.google.com/p/arduino-to-xmc/wiki/Display_TM1640)
  * [TM1636 Display](https://code.google.com/p/arduino-to-xmc/wiki/TickShield)
  * [LED 8x8 Matrix Display](https://code.google.com/p/arduino-to-xmc/wiki/Display_MAX7229)
  * ... more will come

### 10.Starter Kit ###
  * ... more will come

### 11.Time ###
  * [Real Time Clock (embedded into XMC1100)](https://code.google.com/p/arduino-to-xmc/wiki/RTC)
  * [RTC (example code illustrating Time library date strings)](https://code.google.com/p/arduino-to-xmc/wiki/TimeSerialDateStrings)
  * [Tick Tock Shield (clock)](https://code.google.com/p/arduino-to-xmc/wiki/TickShield)
  * ... more will come

### 12.Motor ###
  * [Servo Motor](https://code.google.com/p/arduino-to-xmc/wiki/ServoMotor)
  * [Software Servos](http://code.google.com/p/arduino-to-xmc/wiki/SoftwareServo)
  * [Unipolar Stepper Motor](https://code.google.com/p/arduino-to-xmc/wiki/UnipolarStepperMotor)
  * [Motor Driver Shield (Ardumoto)](http://code.google.com/p/arduino-to-xmc/wiki/Ardumoto)
  * ... more will come