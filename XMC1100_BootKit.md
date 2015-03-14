# XMC1100 Boot Kit #
  * XMC1100 Microcontroller with 64KB Flash
  * Detachable SEGGER J-Link
  * Board shape & power supply for Arduino™ Shields: http://shieldlist.org
  * 6 LEDs

## Arduino Uno Pin layout mapping to XMC1100 Boot Kit ##
![https://arduino-to-xmc.googlecode.com/svn/wiki/ARDUINO_XMC1100_pins.png](https://arduino-to-xmc.googlecode.com/svn/wiki/ARDUINO_XMC1100_pins.png)

Here the Arduino pins definition code (ref. [pins\_arduino.h](http://code.google.com/p/arduino-to-xmc/source/browse/trunk/hardware/xmc/cores/pins_arduino.h)):
```
// Pins				Arduino
//  0	P1.2		Device transmit UART signal-RXD
//  1	P1.3		Device received UART signal-TXD
//  2	P1.4		External interrupt
//  3	P0.0		External interrupt / PWM output
//  4	P0.1		PWM output
//  5	P0.2		GPIO
//  6	P0.3		PWM output
//  7	P0.4		GPIO
//  8	P0.12		GPIO
//  9	P0.8		PWM output
// 10	P0.9		SPI-SS
// 11	P1.1		SPI-MOSI
// 12	P1.0		SPI-MISO
// 13	P0.7		SPI-SCK / LED output
// 14	GND		Ground
// 15	P2.3		Analog reference voltage
// 16	P2.1		I2C Data / Address
// 17	P2.0		I2C Clock
// 30	Extended Leds P0.5
// 31	Extended Leds P0.6
// 32	Extended Leds P1.2
// 33	Extended Leds P1.3
// 34	Extended Leds P1.4
// 35	Extended Leds P1.5

// A0	P2.6		AA
// A1	P2.8		AB
// A2	P2.9		AC
// A3	P2.10		AD
// A4	P2.11		AE
// A5	P2.2		AF


#define LED	13	// Standard Arduino LED pin 13
#define LED1	LED
#define LED2	30	// Extended Leds P0.5
#define LED3	31	// Extended Leds P0.6
#define LED4	32	// Extended Leds P1.2
#define LED5	33	// Extended Leds P1.3
#define LED6	34	// Extended Leds P1.4
#define LED7	35	// Extended Leds P1.5

#define A0 20
#define A1 21
#define A2  22
#define A3  23
#define A4  24
#define A5  25

```

## Docs and links ##
  * Boot Kit XMC110: [Documents](http://www.infineon.com/cms/en/product/microcontrollers/32-bit-industrial-microcontrollers-based-on-arm-registered-cortex-tm-m/32-bit-xmc4000-industrial-microcontrollers-arm-registered-cortex-tm-m4/xmc-development-tools-software-and-kits/xmc1000-starter-kits/boot-kit-xmc1100/channel.html?channel=db3a30433cfb5caa013d115dda020665)
  * XMC1100 Boot Kit: [Getting Started](http://www.infineon.com/dgdl/XMC1100_Boot_Kit_Getting_Started_v1_2.pdf?folderId=db3a304334fac4c601350a01037e11d2&fileId=db3a30433da119ff013da234ec27141c&ack=t)
  * XMC1000 Boot Kit Getting Started: [Introduction video](http://2696.2871.m.edge-cdn.net/vsc_2871_2696_1_vid_511733/XMC1000-Boot-Kit-Getting-Started-Introduction.html)
  * XMC1000 Boot Kit Getting Started: [XMC1100 Hardware Setup video](http://2696.2871.m.edge-cdn.net/vsc_2871_2696_1_vid_511111/XMC1000-Boot-Kit-Getting-Started-XMC1100-Hardware-Setup.html)
  * XMC1000 Boot Kit Getting Started: [DAVE™ Setup video](http://2696.2871.m.edge-cdn.net/vsc_2871_2696_1_vid_511105/XMC1000-Boot-Kit-Getting-Started-DAVE-Setup.html)