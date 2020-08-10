/*
 * File Name: 'input119718-34236-1852eb1.82z8j.cpp'
 * File Purpose: Contains any functions specifically for input/output control
 * hardware
 * By: Nicholas Steele
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif // ifndef HEADERS_H

/*
 * Fuction Usage: Used mainly during delays to check hardware iputs. (Hardware
 * buttons never implemented. Function not used on its own, but is left in for
 * any future changes.)
 * Parameters: Whether or not to check a rotary encoder.
 */

void checkHardware(bool encoderCheck) {
	// Checks any button inputs. If {encoderCheck = 1}, and one encoder input is
	// on, then the arduino waits 20 ms for another.
	// Tells inputDecode(); if something has changed oor the encoder rotated

	// (If interrupts are implemented, doesen't check those buttons)
} // checkHardware

/*
 * Fuction Usage: Write the given number to the indicator LEDs in binary for
 * troubleshooting. Note that 64 will be written as blank, since this is
 * zero-exclusicve.
 * Parameters: The number to be shown in binary
 */

void binaryOut(unsigned char ledNum) {
	for (int i = 0; i < 6; i++) {
		if (bitRead(ledNum, i)) {
			sbi(BIR(5 - i), BIB(5 - i));
		} else {
			cbi(BIR(5 - i), BIB(5 - i));
		}
	}
} // binaryOut
