# RTI
My work towards the software and hardware components of a Reflectance Transformation Imager for George Washington University.

Further documentation, other than that directly in design files, can be found in the `docs` directory. For a high-level intoduction, see [About the System](#about-the-system)

# Reflectance Transformation Imaging

Reflectance Tranformation Imaging is a way to get high-resolution models of the surfaces of objects. It works by having taking many pictures from the same location while changing the angle of light on the object, casting many different shadows on it. 

One way to go about this is to have a single light in a dark room that is moved around by hand, taking measurements of each motion. Because that can be cumbersome and inaccurate, we based our design around another method, which was to place a semi-circular dome filled with high-power lights at precise angles over the object, and to switch to lights on and off. 

# Our Work

Many solutions exist for the latter design, but very few are affordable and capable of multicolor imaging, which can be helpful for materials transparent in the visible spectrum. This [Hackaday article](https://hackaday.io/project/11951-affordable-reflectance-transformation-imaging-dome) documents the project we used as a starting point for our design.

This repository contains our implmentation of that design, including:
1. A custom designed Arduino Mega shield with all the electronics from the original design, plus optically isolated camera shutter triggers.
2. The program to control the above shield with a serial or GUI control interface
3. The GUI within the above program, which enables easy control over the whole system. Contains options for different patterns, speeds, LED configurations, camera shutter controls, and general settings.

# About the System

Our device is comprised of three major parts: the dome's physical construction, the driver board, and the code.

The dome itself is
