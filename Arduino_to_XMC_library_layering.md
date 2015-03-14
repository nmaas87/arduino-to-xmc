# Introduction #

This section describe how the Arduino Wiring language layering to XMC microcontrollers.


# Arduino to XMC Software Layering #

One picture describe more than many words...
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_to_XMC_software_layering.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_to_XMC_software_layering.jpg)

As visible in the above picture, the Wiring Language is interfaced to XMC hardware via the DAvE Low Level driver: this permit an easy portability across the various XMC microcontrollers and leave the freedom to extend your application code by using DAvE Apps ([App list](http://www.infineon.com/dgdl/ListofDAVE_Apps_v1.0.62.xls?folderId=db3a3043134dde6001134ef5f8ff0281&fileId=db3a304342371bb0014237c47c1d0023&ack=t), [examples](http://www.infineon.com/cms/en/product/promopages/aim-mc/dave_downloads.html)).

**Note:** you can create the Low Level Driver code by yourself: [HowToCreateLowLevelDriver](http://code.google.com/p/arduino-to-xmc/wiki/HowToCreateLowLevelDriver_XMC1300).