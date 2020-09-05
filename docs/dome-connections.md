### Contents

- [About the Wiring Scheme](#About-the-Wiring-Scheme)
- [How to Wire the Dome Matrix](#How-to-Wire-the-Dome-Matrix)
  - [Getting Parts](#getting-parts)
- [The Process](#The-Process)
  - [1. Get Things Together](#1-Get-Things-Together)
  - [2. Solder Wires on LED Boards](#2-Solder-Wires-on-LED-Boards)
  - [3. Install LED Boards](#3-Install-LED-Boards)
  - [4. Measure and Cut Wires and Build Connectors](#4-Measure-and-Cut-Wires-and-Build-Connectors)

---

# About the Wiring Scheme

If you're familiar with LED arrays, you can skip to [How to Wire the Dome](#how-to-wire-the-dome-Matrix).

## Common Matrices

When creating an array of LEDs, the common choice is to create a matrix of LEDs. This matrix allows us to control lots of LEDs with few control lines, meaning less hardware is needed to connect and drive the matrix. Matrixes are represented in rectangular configurations, but they can take any shape needed, and in our case, that shape is of circular rings that climb up a semi-sphere.

A commonality of RTI dome designs is to have 8 rings of 8 LEDs - and that's no coincidence. These domes are designed after an 8x8 LED matrix, which has 64 LEDs in it. One way to think of these matrixes is as a grid with units used to refer to any one position. The position (0, 0) is the first row, first column, while the position (5, 6) is the one cell that is both in the fifth column and sixth row.

Take a look at this picture. Although it may not look like a grid, it's got the same concept - the LEDs, represented with the arrow symbols, are all connected to exactly one column and one row. The columns and rows cross in this picture but they aren't connected. By "activating" column 5 and row 6, the LED at the position (5, 6) will turn on.

| ![Matrix schematic](https://github.com/nichlock/rti/blob/master/images/matrix/matrix-schem.jpg) |
| :--- |
| (Original image credit to Arduino: https://www.arduino.cc/en/Tutorial/RowColumnScanning) |

Something to note about these is that in the real world, we can activate multiple LEDs in this matrix either one column at a time or one row at a time. If we tried to activate two LEDs diagonal to each other, say (0, 0) and (1, 1), we would end up with (0, 1) and (1, 0) also lit up.

## Our System

That's what it looks like for a single color array, but we need three colors: ultraviolet, white, and infrared. All we need is three more copies of the 8x8 design all connected - in three dimensions, you can think of stacking three 8x8 grids on top of each other. For all three stacked matrices, if the columns are kept as three separate groups of 8, the 8 rows can be connected across the layers, and we will still get a unique position for any coordinate. The position (0, 5, 6) will always be the LED in the first layer, sixth group of rows, and fifth column.

When we plug that in our schematic we can't use three dimensions, so we flatten it down. Looking at this image, notice that the only difference is that there are three LEDs for each LED before, and three additional corresponding columns.

![An image of a three-color matrix](https://github.com/nichlock/rti/blob/master/images/matrix/matrix-three-color.jpg)

# How to Wire the Dome Matrix

Essentially, we are connecting the common cathode as the columns and the uncommon (separate color) anodes along with the rings. We wired it this way because connecting LEDs going up the columns requires more wire, so it needs fewer connections.

## Getting Parts

It is important to purchase the correct hardware, as the number of parts you'll need scales quickly. There are three important parts of the wiring:
- The wire
- The splice connectors
- The mounts for holding wires

### Wire

The wire needs to be a large enough gauge to handle the current without dropping the voltage. A drop in voltage will result in a dimmer LED, and the only controllable factors which can limit the voltage drop are **wire length** and **wire thickness**.

**Wire length**: To minimize wire length, connect the end of the wire that wraps around the dome back to the beginning of the wire.

**Wire Thickness**: Wire thickness depends mainly on what you can actually find to buy. Note that this depends on your selection of wiretaps.

### Splice Connectors

The splice connectors we used are wiretaps, which allow one wire to pass through while connecting another wire to it. Our specific choice was the Molex `19216-0003`.

### Mounts

In our design, the LED boards were attached with PVC tubes, which stuck out of the outside of the dome by a little over a centimeter. This worked perfectly well as a mounting mechanism, as the wires could just lay on the tubes. We also found that with how lightweight our wires and splices were, we didn't need mounts anyway. You should consider this in your design, though, as the wires will pull out of any connector with enough force.

# The Process

Finally, this was our procedure for connecting the dome.

## 1. Get Things Together

Start with the dome with all holes drilled and wiring tubes installed. The LED boards should be assembled, but not yet installed on the dome. You'll want the [connectors for the dome wiring](#building-connectors) and the [splice connectors](#Splice-Connectors).

## 2. Solder Wires on LED Boards

Wires that connect to the LEDs through the tubes are all cut at the predetermined length and soldered on the LED boards. See more in the [build guide](../../blob/master/docs/RTI%20Build%20Guide.pdf).

## 3. Install LED Boards

Install the LED boards by fitting the wires through the tube in the dome. Since we planned on modifying the LEDs, we used hot glue to attach them to the dome. The wires should be fairly tight and should not loop into the dome.

| ![The wiring as viewed from inside the dome.](https://github.com/nichlock/rti/blob/master/images/dome/led-wiring-internal-two-color.jpg) | ![The wiring as viewed from outside the dome.](https://github.com/nichlock/rti/blob/master/images/dome/led-wiring-external-two-color.jpg) |
| :--- | :--- |
| An LED board installed, seen from inside the dome. This board was populated with UV and White LEDs, so it has three wires. | The view of the installed LED from the outside the dome. |

## 4. Measure and Cut Wires and Build Connectors

### Label Columns

Start by labeling the columns to help stay organized. This is temporary, so taped paper with the number written on it will do. 

![The 8 columns all labled](https://github.com/nichlock/rti/blob/master/images/dome/dom-col-labeled.jpg)

### Measure and Cut the Column Wires

Unspool a length of wire, without cutting it, and [install the 9 cable splices](#Installing-Cable-Splices). Connect the end of the wire to the topmost LED on the first column. To use the splice connector, simply insert the wires fully and clamp down the metal plate so that it goes flush with the plastic, then close the plastic clip. Make sure the wires won't just fall out by tugging on them with low force (too much force will pull the wire out by stripping it). 

Connect the wire down the column to every LED on that column. When done, let the wire go to the bottom of the dome, and, with a large bending radius, bend the wire along the lip of the dome. Run the wire along the bottom of the dome until you get to where you want the connector. Give the wire an extra `4in/10cm`, and cut it.

The red wires and attached blue connectors in this image are essentially what you should be seeing:

| ![Dome column connections](https://github.com/nichlock/rti/blob/master/images/dome/column-wiring.jpg) | ![Wires going to the connector](https://github.com/nichlock/rti/blob/master/images/dome/wiring-connector.jpg) |
| :--- | :--- |
| The connections made on the dome. For now, focus on the red wires central in the image and the blue connectors. | The column wires going into the connector. |

Crimp the wire and insert the pin into the connector. See [Building the Connectors](#building-the-connectors) below for more.

Repeat for all eight columns.

### Measure and Cut the Ring Wires

You'll need a set of 8 wires going around the dome for each fully populated color. Even if you don't need to populate all columns, it may be worth it to measure the wire and coil it up at the base of the connector if you plan on adding it later. Start with a color you don't plan on adding more of, though, since that set of wires will then be beneath all others.

Unspool a length of wire, without cutting it, and [install the 9 cable splices](#Installing-Cable-Splices). Start at the bottom ring of the final column. With the end of the wire pointing to the first column, connect the LED wire to the one you are installing. Leave enough extra wire to connect the wire to itself when it comes back around since that will reduce power losses.

Go around the dome connecting the LEDs, laying the wire on top of the tube if needed. The wire should have enough slack that it won't be a challenge to run a wire under it. 

Once you wrap the wire fully around, connect the open end of the wire to the side of the wire you're working on using the final splice. Run the wire down the area between the final column and the first column, give the wire an extra `4in/10cm`, and cut, crimp, and install it in the connector. See [Building the Connectors](#building-the-connectors) below for more.

### Installing Cable Splices

TODO: this should cover using the cable splices, and how to install them when starting a column or ring.

### Building the Connectors

TODO: Should describe stripping, crimping, and inserting a wire into the 8-pin connectors.

