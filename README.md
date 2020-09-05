# Open Source RTI

Design files and released for the software, hardware and physical construction of a Reflectance Transformation Imager for George Washington University.

For information on the contents of the system, see [our Wiki](https://github.com/nichlock/rti/wiki). For more on the build and usage, [see the docs folder](../../tree/master/docs).

This repository contains our RTI's hardware and software implementation, and includes the source and documentation for:
1. A custom designed Arduino Mega shield to control the dome, which powers a three-color LED matrix and triggers the cameras.
2. Another custom circuit board which holds all three colors of LEDs in a smaller area than if we had three separate boards, allowing for a more compact dome.
3. The program to control the dome, with a serial or GUI control interface.
4. The GUI within the above program, which enables easy control over the whole system with no need for technical knowledge. See more about the GUI on our [system overview page](https://github.com/nichlock/rti/wiki/About-the-System#software-and-gui).

![Image of the main dome](../../blob/master/images/dome/fully-wired.jpg)
