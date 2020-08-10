/*
 * File Name: 'input119718-34236-1bu89h.zkkso.cpp'
 * File Purpose: All LED_object functionality
 * By: Nicholas Steele
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif // ifndef HEADERS_H

/*
 * Fuction Usage: Sets teh row and column numbers from the given LED number.
 * Parameters: None
 */

void LED_object::setRC() { // Sets up the row and column values
	/*Expects a decimal number from 1-64
	 * r = row #, 1-8
	 * c = column #, 1-8
	 * LID = (r * 8) - (8 - c)
	 * c = LED%8 except where LED%8 == 0 (meaning LED is a multiple of 8), in
	 * which case c=8
	 * r = (LED + 8 - c) / 8
	 */
	c = ((num % 8 == 0) ? 8 : num % 8); // Sets column
	r = (num + 8 - c) / 8; // Set the row
	c--;
	r--;
} // LED_object::setRC

/*
 * Fuction Usage: Turns LED on or off. Can set shutter too, given an activation
 * delay time.
 * Parameters: mode (on or off) and on time, and optionally, whether the shutter
 * is active high and the shutter's activation delay time.
 */

void LED_object::trigger(
	bool mode, unsigned char del, bool shutterHigh = true,
	unsigned char shutterOnWait = 0) { // Set the LED to either on or off
	                                   // Begins with setShutter
	                                   // Activates channel driver

	if (mode) { // Turning the LED on
		binaryOut(num);
		sbi(RR(r), RB(r));
		if (ch1) {
			setShutter(0, del, shutterHigh, false, false, shutterOnWait);
			sbi(ENR(0), ENB(0)); // LED driver enable
			sbi(CH1R(c), CH1B(c));
		} else if (ch2) {
			setShutter(1, del, shutterHigh, false, false, shutterOnWait);
			sbi(ENR(1), ENB(1)); // LED driver enable
			sbi(CH2R(c), CH2B(c));
		} else {
			setShutter(2, del, shutterHigh, false, false, shutterOnWait);
			sbi(ENR(2), ENB(2)); // LED driver enable
			sbi(CH3R(c), CH3B(c));
		}
	} else {
		binaryOut(0);
		cbi(RR(r), RB(r));
		if (ch1) {
			setShutter(0, 0, shutterHigh, true);
			cbi(ENR(0), ENB(0)); // LED driver enable
			cbi(CH1R(c), CH1B(c));
		} else if (ch2) {
			setShutter(1, 0, shutterHigh, true);
			cbi(ENR(1), ENB(1)); // LED driver enable
			cbi(CH2R(c), CH2B(c));
		} else {
			setShutter(2, 0, shutterHigh, true);
			cbi(ENR(2), ENB(2)); // LED driver enable
			cbi(CH3R(c), CH3B(c));
		}
	}
} // LED_object::trigger
