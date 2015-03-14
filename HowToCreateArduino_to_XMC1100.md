# Introduction #

This chapter explain you how to create the Arduino\_to\_XMC1100 for XMC1100 via DAvE.

You need:
  * The board: Infineon XMC1100 Boot Kit
  * Environment: DAVE™ – Free Development Platform for Code Generation (DAVE™ 3.1.8 or later)



# STEP 1 - Create the DAvE project #

By 'File->New' (or ALT+SHIFT+N) create a new Easy Start Project:
  * Project Name: 'Arduino\_to\_XMC1100' ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step01.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step01.png)
  * Processor Info: ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step02.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step02.png)

After pressing 'Finish', you'll get your empty project. Since 'easyMain and GPIO' are not needed, just remove them:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step03.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step03.png)



# STEP 2 - Include the  Arduino library files #

## STEP 2.1 - Download connect to versioning system ##
Download the latest arduino-to-xmc files from the versioning system. As for example, I download into: 'C:\UserData\Projects\DAVE3\_workspace\ws\arduino-to-xmc\_svn':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step04.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step04.png)

**Note:** I use Tourtuouse SVN to connect to 'https://arduino-to-xmc.googlecode.com/svn/trunk/'. Subversion repository may be accessed using many different [client programs and plug-ins](http://subversion.apache.org/packages.html).

Use this command to anonymously check out the latest project source code (see [...](http://code.google.com/p/arduino-to-xmc/source/checkout)):
```
# Non-members may check out a read-only working copy anonymously over HTTP.
svn checkout http://arduino-to-xmc.googlecode.com/svn/trunk/ arduino-to-xmc-read-only 
```

## STEP 2.2 - Include into DAvE project the Arduino-to-xmc library files ##

![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step04_1.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step04_1.png)

Now, select 'New'(2) from the project panel (1). An the select Folder (3).
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step05.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step05.png)

Select 'Advanced' and then 'Link to alternate location (Linked Folder)'. Fill the path filed with your local path to the 'hardware\xmc\cores\' directory (if you follow STEP 2.1, you should have in 'C:\UserData\Projects\DAVE3\_workspace\ws\arduino-to-xmc\_svn\hardware\xmc\cores'):
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step06.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step06.png)

## STEP 2.3 - Include into DAvE project the Arduino libraries ##

Same as for STEP 2.2: 'New -> Folder -> Advanced -> Link to alternate ...'. In this case the Arduino libraries folder path should be 'C:\UserData\Projects\DAVE3\_workspace\ws\arduino-to-xmc\_svn\libraries':
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step07.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step07.png)

Now, your 'Arduino\_to\_XMC1100' project should look like as:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step08.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step08.png)



# STEP 3 - Compiler Settings #

Make sure that the compiler options are set as (ALT+ENTER on the project name):
![http://arduino-to-xmc.googlecode.com/svn/wiki/DAvE_Config_Directories_XMC1100.png](http://arduino-to-xmc.googlecode.com/svn/wiki/DAvE_Config_Directories_XMC1100.png)

  1. **Preprocessor**: you must define the following symbols:
    * 'DAVE\_CE'
    * 'ARDUINO=1100'

  1. **Directories**: you must define the following Include paths:
    * '${workspace\_loc:/${ProjName}/cores}'
    * '${workspace\_loc:/${ProjName}/cores/XMC1100}'
    * '${workspace\_loc:/${ProjName}/cores/XMC1100/inc}'
    * '${workspace\_loc:/${ProjName}/cores/XMC1100/inc/LIBS}'
    * '${workspace\_loc:/${ProjName}/cores/XMC1100/inc/DAVESupport}"

**Note:** the above Preprocessor and Directories definitions must be repeated also for the C++ compiler (ARM-GCC C++ Compiler).



# STEP 4 - Optimize code size #

In order to save code size, it is important to configure the compiler options:
  1. code size optimization (ALT+ENTER on the project name):
    * ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_20.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_20.jpg)

  1. linker optimization:
    * remove unused sections: ![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_21.jpg](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1300_LowLevelDriver_Step_21.jpg)

**Note:** the above code size optimization must be repeated also for the C++ compiler (ARM-GCC C++ Compiler).

# STEP 5 - Remove un-necessary files #

I've not yet solved all compiler issues related to C++ code size. For this reason, I normally remove from the makefile the following files (red cross marked):
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step09.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step09.png)

**Note:** do not forget to exclude from the project ('Exclude resource from build') also the XMC1300 and XMC4500 subfolders (or enable them if you are compiling for such processors).

Similarly, when you do not use some libraries, it is more convinient to 'Exclude resource from build' such:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step11.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step11.png)

# STEP 6 - Build #

Now its time to Compile, only your sketch is missing ...
```
#include "Arduino.h"

//****************************************************************************
// 							       ARDUINO SKETCH
//****************************************************************************

void setup() {
	// ...
}

void loop() {
	// ...
}


//****************************************************************************
// 							       END OF FILE
//****************************************************************************
```

Now should be allright, the empty project is about 13KB:
![http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step12.png](http://arduino-to-xmc.googlecode.com/svn/wiki/Arduino_XMC1100_ProjectSteps/Arduino_XMC1100_Step12.png)

