/*
 * File Name: 'input119718-34236-wzmmtu.wtunk.cpp'
 * File Purpose: Contains all preset patterns for running multiple LEDs
 * By: Nicholas Steele
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif // ifndef HEADERS_H

/*
 * Fuction Usage: Scans all LEDs, column by column
 * Parameters: Skip (number of LEDs to skip), LED on time delay, LED off tim
 * delay, channel number, shutter on time, shutter active level, shutter
 * activation delay time.
 */

void colScan(unsigned char skip, unsigned char highDel, unsigned char lowDelay,
             unsigned char channel, unsigned char shutterOnTime = 10,
             bool shutterHigh = true, unsigned char shutterOnWait = 0) {
	bool stopPattern = false;
	unsigned char counter = 0, ledCount;

	if (USE_CUSTOM_ARRAY(channel - 1) == 0b1) {
		ledCount = 0; // Special array of LEDs that are usable
		for (int i = 0; i < 64; i++) { // For each LED
			if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (channel - 1) * 8),
			            i % 8) == 0b0) { // If LED is usable
				ledCount++; // Add to ammount of LEDs
				// Serial.println(ledCount);
			}
		}
	} else
		ledCount = 64;

	if (shutterOnWait == 0)
		shutterOnWait == 1; // Built in 100ms shutter on-wait

	// unsigned char testChar = 0;
	// Skip, HIGH time, LOW time, channel #, LED objects
	// Delays are assumed to be x10 smaller than actual value
	if (skip == 0)
		skip = 1;
	for (int i = ((channel - 1) * 64); i < (channel * 64); i += 1) {
		if (USE_CUSTOM_ARRAY(channel - 1) == 0b1 &&
		    bitRead(EEPROM.read(USABLE_IR_ARRAY + ((i - ((channel - 1) * 64)) / 8) +
		                        (channel - 1) * 8),
		            i % 8) == 0b1)
			continue; // skip this LED because it cannot be used

		if (counter % skip != 0) {
			counter++;
			continue;
		}
		counter++;

		patternModeDisplay((((float)counter / ledCount)), i,
		                   channel); // Set the screen to the pattern window
		ledArray[i].trigger(true, shutterOnTime, shutterHigh, shutterOnWait);
		stopPattern = advancedDelay((highDel * 100) + millis(), shutterHigh,
		                            shutterOnTime); // Checks shutters during a
		ledArray[i].trigger(false, 0, shutterHigh);
		if (stopPattern) {
			// Serial.println("Canceling");
			return;
		}
		stopPattern = advancedDelay((lowDelay * 100) + millis());
		if (stopPattern) {
			// Serial.println("Canceling");
			return;
		}
	}
} // colScan

/*
 * Fuction Usage: Scans all LEDs, ring by ring
 * Parameters: Skip (number of LEDs to skip), LED on time delay, LED off tim
 * delay, channel number, shutter on time, shutter active level, shutter
 * activation delay time.
 */

void ringScan(unsigned char skip, unsigned char highDel, unsigned char lowDelay,
              unsigned char channel, unsigned char shutterOnTime = 10,
              bool shutterHigh = true, unsigned char shutterOnWait = 0) {
	bool stopPattern = false;
	static unsigned char counter, ledCount;

	if (USE_CUSTOM_ARRAY(channel - 1) == 0b1) {
		ledCount = 0; // Special array of LEDs that are usable
		for (int i = 0; i < 64; i++) { // For each LED
			if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (channel - 1) * 8),
			            i % 8) == 0b0) { // If LED is usable
				ledCount++; // Add to ammount of LEDs
				// Serial.println(ledCount);
			}
		}
	} else
		ledCount = 64;

	counter = 0;

	if (shutterOnWait == 0)
		shutterOnWait == 1; // Built in 100ms shutter on-wait

	if (skip == 0)
		skip = 1;
	// patternModeDisplay(101, 1);          // Set the screen to the pattern
	// window
	for (int ring = 0; ring < 8; ring++) // For each ring
		for (int i = ((channel - 1) * 64) + ring; i < (channel * 64);
		     i += 8) { // Loop through all LEDs in ring
			if (USE_CUSTOM_ARRAY(channel - 1) == 0b1 &&
			    bitRead(EEPROM.read(USABLE_IR_ARRAY +
			                        ((i - ((channel - 1) * 64)) / 8) +
			                        (channel - 1) * 8),
			            i % 8) == 0b1)
				continue; // skip this LED because it cannot be used

			if (counter % skip != 0) {
				counter++;
				continue;
			}
			counter++;

			patternModeDisplay(((float)counter / ledCount), i,
			                   channel); // Set the screen to the pattern window
			ledArray[i].trigger(true, shutterOnTime, shutterHigh, shutterOnWait);
			stopPattern = advancedDelay((highDel * 100) + millis(), shutterHigh,
			                            shutterOnTime); // Checks shutters during a
			ledArray[i].trigger(false, 0, shutterHigh);
			// Serial.println(stopPattern);
			if (stopPattern) {
				// Serial.println("Canceling");
				return;
			}
			stopPattern = advancedDelay((lowDelay * 100) + millis());
			if (stopPattern) {
				// Serial.println("Canceling");
				return;
			}
		}
	binaryOut(0); // Turn off binary output
	return;
} // ringScan

/*
 * Fuction Usage: Scans LEDs within a certain ring.
 * Parameters: Skip (number of LEDs to skip), LED on time delay, LED off tim
 * delay, channel number, ring number, shutter on time, shutter active level,
 * shutter activation delay time.
 */

void singleRing(unsigned char skip, unsigned char highDel,
                unsigned char lowDelay, unsigned char channel,
                unsigned char ringNum, unsigned char shutterOnTime = 10,
                bool shutterHigh = true, unsigned char shutterOnWait = 0) {
	Serial.println(ringNum);
	Serial.println(channel);
	bool stopPattern = false;
	static unsigned char counter, ledCount;

	if (USE_CUSTOM_ARRAY(patternChannel) == 0b1) {
		ledCount = 0; // Special array of LEDs that are usable
		for (int i = 8 * ((ringNum - 1)); i < 8 * (ringNum); i++) { // For each LED
			if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel) * 8),
			            i % 8) == 0b0) { // If LED is usable
				ledCount++; // Add to ammount of LEDs
			}
		}
	} else
		ledCount = 8;

	counter = 0;

	if (shutterOnWait == 0)
		shutterOnWait == 1; // Built in 100ms shutter on-wait

	// Skip, HIGH time, LOW time, channel #, Column #, LED objects
	ringNum--; // Subtract 1 from ringNum to adjust from plain english value
	// ringNum = dome column, which is schematically a row
	if (skip == 0) { // If a step of zero is selected
		patternModeDisplay(102, 1); // Put a message on the display
		delay(3000);
		return; // Stop pattern making to prevent a hang
	}
	// patternModeDisplay(102, 0); // Set the screen to the pattern window
	for (int i = (8 * ringNum + ((channel - 1) * 64));
	     i < (8 * ringNum + ((channel - 1) * 64) + 8);
	     i += 1) { // Loop through all LEDs
		if (USE_CUSTOM_ARRAY(channel - 1) == 0b1 &&
		    bitRead(EEPROM.read(USABLE_IR_ARRAY + ((i - ((channel - 1) * 64)) / 8) +
		                        (channel - 1) * 8),
		            i % 8) == 0b1)
			continue; // skip this LED because it cannot be used

		if (counter % skip != 0) {
			counter++;
			continue;
		}
		counter++;

		Serial.print(": ");
		Serial.print("y");

		patternModeDisplay(((float)counter / ledCount), i,
		                   channel); // Set the screen to the pattern window
		ledArray[i].trigger(true, shutterOnTime, shutterHigh, shutterOnWait);
		stopPattern = advancedDelay((highDel * 100) + millis(), shutterHigh,
		                            shutterOnTime); // Checks shutters during a
		ledArray[i].trigger(false, 0, shutterHigh);
		// Serial.println(stopPattern);
		if (stopPattern) {
			// Serial.println("Canceling");
			return;
		}
		stopPattern = advancedDelay((lowDelay * 100) + millis());
		if (stopPattern) {
			// Serial.println("Canceling");
			return;
		}
	}
	binaryOut(0); // Turn off binary output
	return;
} // singleRing

/*
 * Fuction Usage: Scans LEDs within a certain column.
 * Parameters: Skip (number of LEDs to skip), LED on time delay, LED off tim
 * delay, channel number, column number, shutter on time, shutter active level,
 * shutter activation delay time.
 */

void singleCol(unsigned char skip, unsigned char highDel,
               unsigned char lowDelay, unsigned char channel,
               unsigned char colNum, unsigned char shutterOnTime = 10,
               bool shutterHigh = true, unsigned char shutterOnWait = 0) {
	Serial.println(colNum);
	Serial.println(channel);
	bool stopPattern = false;
	static unsigned char counter, ledCount;

	if (USE_CUSTOM_ARRAY(patternChannel) == 0b1) {
		ledCount = 0; // Special array of LEDs that are usable
		for (int i = 8 * ((colNum - 1)); i < 8 * (colNum); i++) { // For each LED
			if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel) * 8),
			            i % 8) == 0b0) { // If LED is usable
				ledCount++; // Add to ammount of LEDs
			}
		}
	} else
		ledCount = 8;

	if (USE_CUSTOM_ARRAY(channel - 1) == 0b1) {
		ledCount = 0; // Special array of LEDs that are usable
		for (int i = 0; i < 64; i++) { // For each LED
			if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (channel - 1) * 8),
			            i % 8) == 0b0) { // If LED is usable
				ledCount++; // Add to ammount of LEDs
				// Serial.println(ledCount);
			}
		}
	}

	counter = 0;

	if (shutterOnWait == 0)
		shutterOnWait == 1; // Built in 100ms shutter on-wait

	// Skip, HIGH time, LOW time, channel #, colNum #, LED objects
	colNum--;
	if (skip == 0) { // If a step of zero is selected
		patternModeDisplay(102, 1); // Put a message on the display
		delay(3000);
		return; // Stop pattern making to prevent a hang
	}
	patternModeDisplay(102, 0); // Set the screen to the pattern window
	for (int i = ((channel == 1) ? (colNum)
	              : (channel == 2) ? (64 + colNum) : 128 + colNum);
	     i < ((channel == 1) ? (64) : (channel == 2) ? (128) : 192);
	     i += 8) { // Loop through all LEDs
		if (USE_CUSTOM_ARRAY(channel - 1) == 0b1 &&
		    bitRead(EEPROM.read(USABLE_IR_ARRAY + ((i - ((channel - 1) * 64)) / 8) +
		                        (channel - 1) * 8),
		            i % 8) == 0b1)
			continue; // skip this LED because it cannot be used

		if (counter % skip != 0) {
			counter++;
			continue;
		}
		counter++;

		patternModeDisplay(((float)counter / ledCount), i,
		                   channel); // Set the screen to the pattern window

		Serial.print(": ");
		Serial.print("y");

		ledArray[i].trigger(true, shutterOnTime, shutterHigh, shutterOnWait);
		stopPattern = advancedDelay((highDel * 100) + millis(), shutterHigh,
		                            shutterOnTime); // Checks shutters during a
		ledArray[i].trigger(false, 0, shutterHigh);
		// Serial.println(stopPattern);
		if (stopPattern) {
			// Serial.println("Canceling");
			return;
		}
		stopPattern = advancedDelay((lowDelay * 100) + millis());
		if (stopPattern) {
			// Serial.println("Canceling");
			return;
		}
	}
	binaryOut(0); // Turn off binary output
	return;
} // singleCol
