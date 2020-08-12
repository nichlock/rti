# Wiring

###(to do:)
- [ ] Wiring concept, original system
- [ ] Wiring concept, our system
- [ ] Wiring details

# Common RTI Systems vs Our System

If you're familiar with LED arrays, you can skip to [How to Wire the Dome](#how-to-wire-the-dome).

## Common Matrixes


When creating an array of LEDs, the common choice is to create a matrix of LEDs. This matrix allows us to control lots of LEDs with few control lines, meaning less hardware is needed to connect and drive the matrix. Matrixes are represneted in reactangular configurations, but they can take any shape needed, and in our case, that shape is of circular rings that climb up a semi-sphere.

A comonality of RTI dome designs is to have 8 rings of 8 LEDs - and that's no coincidence. These domes are designed after an 8x8 LED matrix, which has 64 LEDs in it. One way to think of these matrixes is as a grid with units used to refer to any one position. The position (0, 0) is the first row, first column, while the position (5, 6) is the one cell that is both in the fifth column and sixth row.

Take a look at this picture. Although it may not look like a grid, it's got the same concept - the LEDs, represented with the arrow symbols, are all connected to exactly one column and one row. The columns and rows cross in this picture but they aren't connected. By "activating" column 5 and row 6, the LED at the position (5, 6) will turn on.

![Matrix schematic](https://github.com/nichlock/rti/blob/master/docs/matrix_schem.jpg)
(Image credit to Arduino: https://www.arduino.cc/en/Tutorial/RowColumnScanning)

Something to note about these is that in the real world, we can activate multiple LEDs in this matrix either one column at a time or one row at a time. If we tried to activate two LEDs diagonal to each other, say (0, 0) and (1, 1), we would end up with (0, 1) and (1, 0) also lit up.

## Our System

That's what it looks like for a single color array, but we need three colors: ultraviolet, white, and infrared. All we need is three more copies of the 8x8 design all connected - in three dimensions, you can think of stacking three 8x8 grids on top of each other. For all three stacked matrices, if the columns are kept as three seperate groups of 8, the 8 rows can be connected accross the layers, and we will still get a unique position for any coordinate. The position (0, 5, 6) will always be the LED in the first layer, sixth group of rows, and fifth column.

Before we look at the full array, have a look at what one 3-color LED looks like. This image is of our three-color LED, which is called a "common-cathode" LED, meaning that the common connection (what will connect to the grouped up rows) is the cathode, or negative, connection.

![TODO:simplified LED picture. Note the "layers" (colors) so it's clear in the next image]()

When we plug that in our schematic we can't use three dimensions, so we flatten it down. Looking at this image, notics that the only difference is that there are three LEDs for each LED before, and three additional corresponding columns.

![An image of a three color matrix](https://github.com/nichlock/rti/blob/master/docs/matrix-three-color.JPG)

# How to Wire the Dome

Given the above schematic, we now need to wire a circular dome. This brings us back to the common design of RTI domes - 8 rings of 8 LEDs lends itself well to the 8x8 matrix, so we can just essentially "wrap" our matrix around the dome.

They say a bad picture is work a thousand words, so here goes:

(TODO: FIX THIS!)

![A very bad despction of how we wrapped the connections around the dome](https://github.com/nichlock/rti/blob/master/docs/matrix-three-color-no-label-warped.JPG)

Essentially, we are connecting the common cathode as the columns and the uncommon (seperate color) anodes along the rings. We wired it this way because connecting LEDs going up the columns requires more wire, so it needs fewer connections.


## The Hardware

It is important to purchase the correct hardware, as the number of parts you'll need scales quickly. There are three important parts of the wiring:
- The wire
- The splice connectors
- The mounts for holding wires

### Wire

The wire needs to be a large enough guage to handle the current without dropping the voltage. A drop in voltage will result in a dimmer LED, and the only controllable factors which can limit the voltage drop are **wire length** and **wire thickness**.

**Wire length**: To minimize wire length, connect the end of the wire that wraps around the dome back to the beginning of the wire.

| Good     | Bad     |
| :------------- | :------------- |
| TODO (wire that goes around and connects back) | TODO (wire that does not connect back) |

**Wire Thickness**: Wire thickness depends mainly on what you can actually find to buy. Note that this depends on your selection of wire taps. We purchased (TODO).

### Splice Connectors

The splice connectors we used are wire taps, which allow one wire to pass through, while connecting another wire to it. Our specific choice was the (TODO).

### Mounts

In our design, the LED boards were attatched with tubes, which stuck out of the outside of the dome by a little over a centimeter. This worked perfectly well as a mounting mechanism, as the wires could just lay on the tubes. We also found that with how light weight our wires and splices were, we didn't need mounts anyway. You should consider this in your design, though, as the wires will pull out of any connector with enough force.

## The Process

Finally, this was our procedure for connecting the dome:
1. All row and column wires were labeled and measured. The wires all had to go to a central place on the dome, where we would connect them, so make sure to account for that in you measurement. While measuring and labelling, we also crimped the wires into the connectors to keep them organized.
