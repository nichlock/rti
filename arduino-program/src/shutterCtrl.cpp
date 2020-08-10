/*
 * File Name: 'input119718-34236-1x483kw.63x5h.cpp'
 * File Purpose: Shutter setup/control fuctions
 * By: Nicholas Steele
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif // ifndef HEADERS_H

/*
 * Fuction Usage: Startup shutters
 */

void beginShutters() { // Opto-Isolated shutters are active low.
	if (VERBOSE_SERIAL)
		Serial.println(F("\tStartig shutters..."));
	for (int i = 0; i < 3; i++)
		setShutter(i, 0, true, true);
} // beginShutters

/*
 * Fuction Usage: Turn shutter on/off, and set a delay
 * Parameters: Channel number, shutter on time, shutter active level, whether
 * shutter is being activated or deactivated, whether shutter should be
 * activated now (false) or later, time to wait to turn shutter on.
 */

void setShutter(unsigned char channel, unsigned char del,
                bool shutterHigh = true, bool turnOff = false,
                bool activationFromQ = false, unsigned char shutterOnWait = 0) {
	// Activates the shutter on {channel} for duration of {del}
	// {del} of 0 will turn off shutter
	if (turnOff) { // A shutter is being turned off
		// Serial.print("off, ");
		// Serial.println(millis() - millisDelay[0]);
		millisDelay[channel] = 1;
		q[channel] = false;
		if (JOIN_SHUTTERS) { // If all shutters should be triggered as one
			for (int i = 0; i < 3; i++) {
				if (shutterHigh)
					cbi(SR(i), SB(i));
				else
					sbi(SR(i), SB(i));
			}
		} else { // Otherwise, only the correct one should be active.
			if (shutterHigh)
				cbi(SR(channel), SB(channel));
			else
				sbi(SR(channel), SB(channel));
		}
		tbi(PORTB, PB7); // Toggle Pin 13 LED
		return;
	} else {
		// The following if statements set the delay for the shutter to the lower of
		// del and shutterLength
		if (del == 0) {
			// If the shutter time is set to 0, the shutter should last as long as
			// the LED is on
			millisDelay[channel] = 1;
		} else {
			millisDelay[channel] = (del * 100) + millis();
		}
		if (!activationFromQ) {
			millisDelay[channel] = (shutterOnWait * 100) + millis();
			// Serial.print(F("Shutter will turn on in:"));
			// Serial.println(shutterOnWait);
		}
		if (VERBOSE_SERIAL) {
			Serial.print(F("Shutter turning "));
			if (activationFromQ)
				Serial.print(F("off"));
			else
				Serial.print(F("on"));
			Serial.print(F(" at: "));
			Serial.print(millisDelay[channel] / 1000);
			Serial.print(F(" seconds"));
			Serial.print(F("("));
			Serial.print(millisDelay[channel]);
			Serial.println(F("ms)"));
		}
		// millisDelay[channel + 3] = shutterLength + millis();
		if (activationFromQ) {
			q[channel] = true;
			if (JOIN_SHUTTERS) { // If all shutters should be triggered as one
				for (int i = 0; i < 3; i++) {
					if (shutterHigh)
						sbi(SR(i), SB(i));
					else
						cbi(SR(i), SB(i));
				}
			} else { // Otherwise, only the correct one should be active.
				if (shutterHigh)
					sbi(SR(channel), SB(channel));
				else
					cbi(SR(channel), SB(channel));
			}
		} else
			q[channel] = false;
		tbi(PORTB, PB7); // toggle Pin 13
	}
} // setShutter

/*
 * Fuction Usage: Check if shutters need to be turned on or off.
 * Parameters: Shutter active level and shutter active time.
 */

void checkShutters(bool shutterHigh = false, unsigned char shutterOnTime = 0) {
	// check the shutters for one that should be turned off.
	// Should always run in the background whenever an LED can be active.
	for (int i = 0; i < 3; i++) {
		if (millisDelay[i] != 1) { // If there is an active shutter for channel i-3
			if (q[i] == true) {
				currentMillis = millis();
				if (millisDelay[i] < currentMillis) { // And the delay has passed
					setShutter(i, 0, shutterHigh, true,
					           true); // Send shutter to be turned off
				}
			} else {
				currentMillis = millis();
				if (millisDelay[i] < currentMillis) { // And the delay has passed
					setShutter(i, shutterOnTime, shutterHigh, false,
					           true); // Send shutter to be turned on
				}
			}
		}
	}
} // checkShutters
