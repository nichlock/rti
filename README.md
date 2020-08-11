# RTI
My work towards the software and hardware components of a Reflectance Transformation Imager for George Washington University.

Further documentation, other than that directly in design files, can be found in the `docs` directory. For a high-level intoduction, see [About the System](#about-the-system)

# Reflectance Transformation Imaging

Reflectance Tranformation Imaging is a way to get high-resolution models of the surfaces of objects. It works by having taking many pictures from the same location while changing the angle of light on the object, casting many different shadows on it. 

One way to go about this is to have a single light in a dark room that is moved around by hand, taking measurements of each motion. Because that can be cumbersome and inaccurate, we based our design around another method, which was to place a semi-circular dome filled with high-power lights at precise angles over the object, and to switch to lights on and off. 

# Our Work

Many solutions exist for the latter design, but very few are affordable and capable of multicolor imaging, which can be helpful for materials transparent in the visible spectrum (we used ultraviolet, white, and infrared). This [Hackaday article](https://hackaday.io/project/11951-affordable-reflectance-transformation-imaging-dome) documents the project we used as a starting point for our design.

This repository contains our implmentation of that design, including:
1. A custom designed Arduino Mega shield with all the electronics from the original design, plus optically isolated camera shutter triggers.
2. Another custom circuit board which holds all three colors of LEDs in a smaller area than if we had three seperate boards, allowing for a more compact dome.
3. The program to control the above shield with a serial or GUI control interface
4. The GUI within the above program, which enables easy control over the whole system. Contains options for different patterns, speeds, LED configurations, camera shutter controls, and general settings.

# About the System

Our device is comprised of three major parts: the dome's physical construction, the driver and LED boards, and the code/GUI.
## Construction
The dome itself is (TODO)

## Circuit Boards

We had a number of requirements of our boards. The driver board needed three seperate 1A channels which could drive 64 LEDs each, which would have an isolated system to trigger a camera shutter. The LED boards had to both sink the 5W of poer from the LEDs and contain three sperated colors. Since these aren't common requirements for consumer-level prototype boards, we designed custom circuit boards for this solution. These are the two custom boards designed for that purpose.

### Driver Board

([Schematic](hardware/arduino-sheild/MEGA_shield_SCHEMATIC.pdf), [further documentation](docs/driver-board.md))

Since not all LED colors will operate at similar amperages, we needed three constant-current drivers on one board. Beyond that, we wanted robust connectors that would handle the maximum voltages and currents our system might see, and isolated camera triggers. For all these needs, we created a custom driver board. This driver board was implemented as a shield for an Arduino Mega.

TODO: image

### LED Board

([Schematic](hardware/led-board/LEDBoard_SCHEMATIC.pdf), [further documentation](docs/led-board.md))

The three LEDs needed to be mounted on the dome on a board that would sink much of their heat. For this, I designed another circtuit board around the same size as the common [star shaped boards](https://www.adafruit.com/product/518), but capable of holding three LEDs in a common-anode configuration, just like 4-lead RGB LEDs. Electrically, this is very simple; the only challenges were in thermal considerations and creating a robust mounting and wiring design.

TODO: images of board, wired and non-wired


In the above image, you can see a hole in the middle of the board. This is there to wire the LED through the plastic tube that was used to mount it. 

These board were not designed for long-term use, and will get very hot after a little while without any active cooling, so try not to run any one LED over 20 seconds.

## Code and GUI
