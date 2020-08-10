/*~~~~~RTI driver program~~~~~
 * This program is written to drive a Reflectance Tranfromation Imager, or RTI.
 * The Arduino Mega that is programed connects to a purpose-designed sheild
 * which is capable of current-controlling 192 1A LEDs. The intent of the
 * design is to run three seperate sets of rows, referred to as channels here.
 *
 * In our implementation:
 * Channel 1 = Ultraviolet
 * Channel 2 = White
 * Channel 3 = Infrared
 *
 * DIAGNOSTICS MODE:
 * When active, diagnostics mode provides additional information that may be
 * useful to programmers.
 *
 * The top left number (written over the 'Home' button) indicates the remaining
 * SRAM on the device, in bytes. If there are unusal problems with no ovbious
 * solutions, this might be the problem. Under typical conditions, this rarely
 * dips below 4kb of SRAM. This value can be updated by touching anywhere. If
 * the text has a white background, it was updated by the last touch, otherwise
 * it was updated just before the last page was loaded.
 *
 * The bottom left and right corners both contain page information. The bottom
 * left has the current page written on it, and the bottom right has the
 * previous visited page on it. These are mainly for troubleshooting name arrays
 * and Help pages.
 *
 * The top left rarely carries any information.
 *
 * Circles at tap locations indicate where a tap was detected, and the color can
 * be used to indicate how that tap is handled. The colors are as follows:
 * RED: The device is not in any loop. This should only be visible on pages with
 *      buttons that have simpler functions (such as changing a page)
 * BLUE: The device is in a loop, but can be escaped by pressing 'Home' or
 *     'Help'. This color is usually found on a page with buttons with complex
 *      functions.
 * CYAN: The device is in a loop that can only be escaped by following though on
 *      an action. Usually this is is used when waiting for an entry on a
 *      number pad or a stop button (stop button boxes will disapear after a set
 *      time.)
 *
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif // ifndef HEADERS_H

static LED_object ledArray[192]; // LED objects

/*~~~~~COMMAND DEFINITIONS~~~~~*/
void waitForResponse();

void checkSerial();

void setPinModes();

void setupLEDs();

void assignCHNames();

/*
 * This is a placeholder object, used to make ledArray a globally accessible
 * object array.
 */

LED_object ledPlaceholder(unsigned char num) {
	return ledArray[num];
} // ledPlaceholder

/*~~~~~Startup~~~~~*/
void setup() {
	setupLEDs();
	// If serial is enabled in headers.h
	// #ifdef SERIAL_OUT
	// baud = 9600; // This is the default choice of baud rate
	// EEPROM_writeAnything(SERIALBAUD_ADDR, baud); // (This int is two bytes
	// long)

	if (!IS_SERIAL_SET) { // Serial is not saved to EEPROM
		// if (EEPROM_readAnything(3, baud) == 0) {
		// If bit #0 of byte #0 of the EEPROM is low, the baud rate is not yet
		// set.

		// 'Baud' is automatically set to default 9600
		EEPROM_writeAnything(SERIALBAUD_ADDR, baud); // (This int is two bytes long)
		Serial.begin(baud);
		Serial.println(F("Serial initialized. Baud rate was NOT FOUND, and has "
		                 "been newly written into EEPROM"));
		TOGGLE_SERIAL_BIT;
	} else {
		EEPROM_readAnything(SERIALBAUD_ADDR,
		                    baud); // Read the baud rate at correct address.
		Serial.begin(baud);
		Serial.println(F("Serial initialized from EEPROM"));
	}
	Serial.println(F("Reflectance Transformation Imager Serial Interface "
	                 "v1.0\nDISABLE LINE ENDINGS"));

	beginDisplay();

	// Set channel names. An identical function, alled assignCHNamesDisplayFile(),
	// is run in beginDisplay(). For some reason, the variable would not retain
	// it's value when set from EEPROM.read() and called in a different file.
	assignCHNames();
	for (int i = 0; i < 3; i++)
		Serial.println(chNames[i]);

	Serial.print(F("\nFor help, press 'h'\n>"));
	// #endif

	/*~~~~~PORT DEFENITIONS~~~~~*/
	setPinModes();
	beginShutters();

	enterPage(0); // Show the home page
	// testChar = 1;
} // setup

/*void loop() is only used to check serial,  touchpad, and timed operations.*/

void loop() {
	// Test LED delays to see if a change in state is needed.
	checkShutters();
	checkTouch();

	if (Serial.available() > 0)
		serialReact(Serial.read());
} // loop

// Set up and define ledArray[]
void setupLEDs() {
	for (int i = 0; i < 192; i++) {
		ledArray[i] = LED_object();
		if (i <= 63) { // Channel 1
			ledArray[i].num = i + 1;
			ledArray[i].ch1 = 1;
		}
		if (i > 63 && i <= 127) { // Channel 2
			ledArray[i].num = i - 63;
			ledArray[i].ch2 = 1;
		}
		if (i > 127) { // Channel 3
			ledArray[i].num = i - 127;
		}
		ledArray[i].setRC();
	}
} // setupLEDs

/*
 * Fuction Usage: Sets the names of the three channels, when referred to on the
 * display and in the serial interface. Gets either default names or EEPROM
 * stored custom ones.
 * Parameters:
 */

void assignCHNames() {
	// Check if any of the intended channel names are not set; if not, use the
	// default.
	char channelNamePlaceholder[CHANNEL_NAME_MAX_CHARACTERS + 1];
	for (int i = 0; i < CHANNEL_NAME_MAX_CHARACTERS; i++)
		channelNamePlaceholder[i] = EEPROM.read(CHANNEL_NAME_1_ADDR + i);
	if (channelNamePlaceholder == "         ") {
		EEPROM_writeAnything(CHANNEL_NAME_1_ADDR, DEFAULT_CHANNEL_NAME_1);
	}
	for (int i = 0; i < CHANNEL_NAME_MAX_CHARACTERS; i++)
		channelNamePlaceholder[i] = EEPROM.read(CHANNEL_NAME_2_ADDR + i);
	if (channelNamePlaceholder == "         ") {
		EEPROM_writeAnything(CHANNEL_NAME_2_ADDR, DEFAULT_CHANNEL_NAME_2);
	}
	for (int i = 0; i < CHANNEL_NAME_MAX_CHARACTERS; i++)
		channelNamePlaceholder[i] = EEPROM.read(CHANNEL_NAME_3_ADDR + i);
	if (channelNamePlaceholder == "         ") {
		EEPROM_writeAnything(CHANNEL_NAME_3_ADDR, DEFAULT_CHANNEL_NAME_3);
	}

	Serial.println(F("Setting channel color names:"));
	for (int i = 0; i < CHANNEL_NAME_MAX_CHARACTERS; i++) {
		chNames[0][i] = EEPROM.read(CHANNEL_NAME_1_ADDR + i);
		chNames[1][i] = EEPROM.read(CHANNEL_NAME_2_ADDR + i);
		chNames[2][i] = EEPROM.read(CHANNEL_NAME_3_ADDR + i);
	}
} // assignCHNames

/*
 * Fuction Usage: Waits a set ammount of time while checking LEDs, display
 * touches, and hardware.
 * Parameters: Takes in a delay time and optional variables related to the
 * camera shutter settings
 */

bool advancedDelay(unsigned long time, bool shutterHigh = false,
                   unsigned char shutterOnTime = 10) {
	bool stopPattern = false;
	// Waits for {time} milliseconds while checking shutters.
	while (time >= millis()) {
		checkShutters(shutterHigh,
		              shutterOnTime); // Check if any shutters should be shut off
		checkHardware(0); // Does nothing as of now
		if (updateDisplay()) { // Check touch screen
			stopPattern = true; // Stop running pattern
			return; // Finish delay to avoid long wait times after stopping
		}
	}
	return stopPattern;
} // advancedDelay

/*
 * Fuction Usage: Sets all of the pin modes for array control pins.
 */

void setPinModes() {
	// Runs off start. May not be necesary.
	DDRA = 0xff; // PORT-A as OUTPUT
	PORTA = 0x00; // All pins of PORT-A LOW

	DDRB = 0xff;
	PORTB = 0x00;

	DDRC = 0xff;
	PORTC = 0x00;

	DDRE = 0xff;
	PORTE = 0x00;

	DDRG = 0xff;
	PORTG = 0x00;

	DDRH = 0xff;
	PORTH = 0x00;

	DDRF = 0xff;
	PORTF = 0x00;

	DDRJ = 0xff;
	PORTJ = 0x00;

	DDRL = 0xff;
	PORTL = 0x00;
} // setPinModes

/*
 * Fuction Usage: Waits for input/response from the serial.
 * Parameters:
 */

void waitForResponse() { // Displays a cursor while awaiting a response.
	while (!Serial.available()) { // Do nothing until a response.
	}
} // waitForResponse

/*
 * Fuction Usage: Respond to a new command from the serial
 * Parameters: The character recieved in the serial
 */

void serialReact(char serialIn) { // React to a serial command being sent.
	static bool addedLast = true;
	Serial.println(serialIn);
	switch (serialIn) {
	case 'a': // Advanced Settings
		char settingSelector;
		Serial.println(
			F("Entered settings. Select one of the following options, or "
			  "use 'c' to cancel. Settings requiring a restart are marked with "
			  "'*'."));
		Serial.println(F("1. Reset Specific Settings"));
		Serial.println(F("2. Serial Baud Rate*"));
		Serial.println(F("3. Change Channel/Color Names"));
		Serial.println(F("4. Verbose Serial"));
		Serial.println(F("5. Default Channel/Color"));
		while (!Serial.available()) {
		}
		settingSelector = Serial.read();
		if (settingSelector == 'c') {
			Serial.println("Cancelled");
			return;
		} else if (settingSelector == '1') {
			Serial.println(F("SELECTED: Reset Specific Settings."));
			Serial.println(F("Enter the setting you would like to reset."));
			Serial.println(F("1. Serial Baud Rate*"));
			Serial.println(F("2. Display Calibration*"));
			Serial.println(F("3. ALL Channel/Color Names"));
			// Serial.println(F("4. Verbose Serial"));
			Serial.println(F("*=Restart required."));

			while (!Serial.available()) {
			}
			settingSelector = Serial.read();
			if (settingSelector == 'c') {
				Serial.println("Cancelled");
				return;
			}
			if (settingSelector == '1') {
				baud = DEFAULT_BAUD_RATE;
				EEPROM_writeAnything(SERIALBAUD_ADDR, baud);
				Serial.print(F("Set serial baud rate to "));
				Serial.print(baud);
				Serial.println(F(". Restart to apply."));
			}
			if (settingSelector == '2') {
				if (IS_TOUCH_CALIBRATED) // Only toggle if calibration is already on
					TOGGLE_TOUCH_CALIBATED;
				Serial.println(
					F("New display calibration requested; restart to begin "
					  "calibrating. \nStored values have NOT been changed; if "
					  "the calibration does not fix the issue AND these "
					  "values are identical to those written to serial after "
					  "calibrating, the EEPROM may be faulty (though other probelems "
					  "are much more likely.)"));

				Serial.println(F("Calibration values:"));
				Serial.print(F("\tx1: "));
				Serial.println(cal[0]);
				Serial.print(F("\tx2: "));
				Serial.println(cal[1]);
				Serial.print(F("\ty1: "));
				Serial.println(cal[2]);
				Serial.print(F("\ty2: "));
				Serial.println(cal[3]);
			}
			if (settingSelector == '3') {
				Serial.println(F("Defaulting to the following channel color names:"));

				EEPROM_writeAnything(CHANNEL_NAME_1_ADDR, DEFAULT_CHANNEL_NAME_1);
				EEPROM_writeAnything(CHANNEL_NAME_2_ADDR, DEFAULT_CHANNEL_NAME_2);
				EEPROM_writeAnything(CHANNEL_NAME_3_ADDR, DEFAULT_CHANNEL_NAME_3);

				for (int j = 0; j < CHANNEL_NAME_MAX_CHARACTERS; j++) {
					chNames[0][j] = EEPROM.read(CHANNEL_NAME_1_ADDR + j);
					chNames[1][j] = EEPROM.read(CHANNEL_NAME_2_ADDR + j);
					chNames[2][j] = EEPROM.read(CHANNEL_NAME_3_ADDR + j);
				}
				for (int i = 0; i < 3; i++)
					Serial.println(chNames[i]);
			}
		} else if (settingSelector == '2') {
			Serial.println(F("SELECTED: Serial Baud Rate"));
			Serial.println(F("Select the baud rate you would like to use:"));
			Serial.println(F("1. 300"));
			Serial.println(F("2. 2400"));
			Serial.println(F("3. 9600"));
			Serial.println(F("4. 19200"));
			Serial.println(F("5. 115200 (Default)"));

			while (!Serial.available()) {
			}
			settingSelector = Serial.read();
			if (settingSelector == 'c') {
				Serial.println("Cancelled");
				return;
			}
			if (settingSelector == '1')
				baud = 300;
			if (settingSelector == '2')
				baud = 2400;
			if (settingSelector == '3')
				baud = 9600;
			if (settingSelector == '4')
				baud = 19200;
			if (settingSelector == '5')
				baud = 115200;

			EEPROM_writeAnything(SERIALBAUD_ADDR, baud);

			Serial.print(F("Set serial baud rate to "));
			Serial.print(baud);
			Serial.println(F(". Restart to apply."));
		} else if (settingSelector == '3') {
			Serial.println(F("SELECTED: Change Channel/Color Names"));
			Serial.println(
				F("Choose which Channel/Color name you would like to change: "));
			Serial.print(F("1. "));
			Serial.println(chNames[0]);
			Serial.print(F("2. "));
			Serial.println(chNames[1]);
			Serial.print(F("3. "));
			Serial.println(chNames[2]);

			while (!Serial.available()) {
			}
			settingSelector = Serial.read();
			if (settingSelector == 'c') {
				Serial.println("Cancelled");
				return;
			}
			char newChannelName[CHANNEL_NAME_MAX_CHARACTERS + 1];
			int counter = 0;
			Serial.print(F("Enter the name you would like to change it to (press "
			               "'\\' to finish): "));
			while (true) {
				if (Serial.available()) {
					newChannelName[counter] = Serial.read();
					Serial.print(newChannelName[counter]);
					if (newChannelName[counter] == '\\') {
						newChannelName[counter] = 0;
						Serial.println(); // Finsihed; leaves code.
						break;
					}
					counter++;
					if (newChannelName[counter] == '\n') { // Ignore newlines
						newChannelName[counter] = 0;
						counter--;
					}
					if (counter == CHANNEL_NAME_MAX_CHARACTERS) {
						Serial.println();
						break;
					}
				}
			}
			for (int i = 0; i < counter; i++) {
				if (settingSelector == '1')
					EEPROM.write(CHANNEL_NAME_1_ADDR + i, newChannelName[i]);
				if (settingSelector == '2')
					EEPROM.write(CHANNEL_NAME_2_ADDR + i, newChannelName[i]);
				if (settingSelector == '3')
					EEPROM.write(CHANNEL_NAME_3_ADDR + i, newChannelName[i]);
			}
			for (int i = counter; i < CHANNEL_NAME_MAX_CHARACTERS; i++) {
				if (settingSelector == '1')
					EEPROM.write(CHANNEL_NAME_1_ADDR + i, ' ');
				if (settingSelector == '2')
					EEPROM.write(CHANNEL_NAME_2_ADDR + i, ' ');
				if (settingSelector == '3')
					EEPROM.write(CHANNEL_NAME_3_ADDR + i, ' ');
			}
		} else if (settingSelector == '4') {
			Serial.println(F("SELECTED: Verbose Serial"));
			Serial.print(F("Verbose serial output has been "));
			TOGGLE_VERBOSE_SERIAL;
			if (VERBOSE_SERIAL)
				Serial.println("ENABLED");
			else
				Serial.println("DISABLED");
		} else if (settingSelector == '5') {
			Serial.println(F("SELECTED: Default Channel/Color"));
			Serial.println(F("Enter the channel/color you would like as the default "
			                 "when using the display"));
			Serial.print(F("1. "));
			Serial.println(chNames[0]);
			Serial.print(F("2. "));
			Serial.println(chNames[1]);
			Serial.print(F("3. "));
			Serial.println(chNames[2]);

			while (!Serial.available()) {
			}
			settingSelector = Serial.read();
			if (settingSelector == 'c') {
				Serial.println("Cancelled");
				return;
			}
			if (settingSelector == '1' || settingSelector == '2' ||
			    settingSelector == '3')
				EEPROM.write(DEFAULT_CHANNEL, settingSelector - '0');
		}
		break;
	case 't': // TOUCH SCREEN CALIBRATION
		calTouch();
		break;
		break;
	case 'm': // Remaining RAM bytes
		Serial.print(F("RAM bytes remaining: "));
		Serial.println(freeMemory());
		break;
	case '0': // Activate next LED number
		if (COUNTnum >= 192)
			return;
		if (!addedLast)
			COUNTnum += 2;
		addedLast = true;
		Serial.print("LED number: ");
		Serial.print(COUNTnum);
		Serial.print("; on pin ");
		Serial.println(COUNTnum % 8 + 1);
		ledArray[COUNTnum - 1].trigger(0, 0);
		ledArray[COUNTnum].trigger(1, 1);
		COUNTnum++;
		break;
	case '.': // Activate previous LED number
		if (COUNTnum >= 192 || COUNTnum < 0)
			return;
		if (addedLast)
			COUNTnum -= 2;
		addedLast = false;
		Serial.print("LED number: ");
		Serial.print(COUNTnum);
		Serial.print("; on pin ");
		Serial.println(COUNTnum % 8 + 1);
		ledArray[COUNTnum - 1].trigger(0, 0);
		ledArray[COUNTnum + 1].trigger(0, 0);
		ledArray[COUNTnum].trigger(1, 1);
		COUNTnum--;
		break;
	case '1': // Run a test Column Scan, Channel 1
		Serial.print(F("Column scanning on channel 1: "));
		Serial.println(chNames[0]);
		colScan(1, 10, 1, 1);
		break;
	case '2': // Run a test Column Scan, Channel 2
		Serial.print(F("Column scanning on channel 2: "));
		Serial.println(chNames[1]);
		colScan(1, 10, 1, 2);
		break;
	case '3': // Run a test Column Scan, Channel 3
		Serial.print(F("Column scanning on channel 3: "));
		Serial.println(chNames[2]);
		colScan(1, 5, 2, 3);
		break;
	case 'x': // Set all LEDs off and reset active LED number
		Serial.println(F("All LEDs shut off, active LED number reset to zero."));
		addedLast = true;
		disableAllLEDs(0);
		COUNTnum = 0;
		break;
	case 'r': // Run single ring
		Serial.println(F("Ring scan called, enter ring number... (c to cancel.)"));
		char ringNumber;
		while (true) // wait for 4 seconds listening for a cancel
			if (Serial.available()) {
				ringNumber = Serial.read();
				break;
				if (ringNumber == 'c')
					return;
			}
		Serial.println(F("Enter channel... (c to cancel.)"));
		char ringChannelChar;
		while (true) // wait for 4 seconds listening for a cancel
			if (Serial.available()) {
				ringChannelChar = Serial.read();
				break;
				if (ringChannelChar == 'c')
					return;
			}
		Serial.print(F("Running column #"));
		Serial.print(ringNumber);
		Serial.print(F(", on channel #"));
		Serial.print(ringChannelChar);
		Serial.print(F(": "));
		Serial.println(chNames[ringChannelChar - '0']);
		singleCol(1, 1, 1, (ringChannelChar - '0'), (ringNumber - '0'));
		break;
	case 'c': // Run single column
		Serial.println(F("Col scan called, enter col number... (c to cancel.)"));
		char colNumber;
		while (true) // wait for 4 seconds listening for a cancel
			if (Serial.available()) {
				colNumber = Serial.read();
				break;
				if (colNumber == 'c')
					return;
			}
		Serial.println(F("Enter channel... (c to cancel.)"));
		char colChannelChar;
		while (true) // wait for 4 seconds listening for a cancel
			if (Serial.available()) {
				colChannelChar = Serial.read();
				break;
				if (colChannelChar == 'c')
					return;
			}
		Serial.print(F("Running column #"));
		Serial.print(colNumber);
		Serial.print(F(", on channel #"));
		Serial.print(colChannelChar);
		Serial.print(F(": "));
		Serial.println(chNames[colChannelChar - '0']);
		singleRing(1, 1, 1, (colChannelChar - '0'), (colNumber - '0'));
		break;
	case 's': // Restart device
		Serial.println(F("Restarting... (c to cancel.)"));
		boolean restart;
		restart = true;
		unsigned long restartTimer;
		restartTimer = millis();
		while (millis() - restartTimer <=
		       4000) // wait for 4 seconds listening for a cancel
			if (Serial.read() == 'c') {
				restart = false;
				break;
			}
		// break;
		if (restart) {
			Serial.println(F("Restarted.\n\n"));
			Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"));
			delay(100);
			resetFunc();
		} else
			Serial.println(F("Cancelled.\n"));
		break;
	case 'e': // EEPROM reset options
		while (!Serial.available()) { // Wait for aditional information
		}
		byte ans; // Create variable for next character.
		switch (Serial.read()) {
		case 'r': // Partial Reset
			        // #ifdef SERIAL_OUT
			Serial.print(F("Resetting EEPROM variables, are you sure? (Y/N):"));
			while (!Serial.available()) {
			} // Do nothing until a response.
			ans = Serial.read(); // Save response.
			if (ans == 'Y' || ans == 'y') { // If yes
				Serial.print(F(" Clearing. T- "));
				for (int i = 0; i < 2; i++) {
					EEPROM.write(i, 0);
				}
				Serial.println(F(" Done."));
			} else
				Serial.println(F(" Cancelled."));
			// #endif
			break; // END partial reset
		case 'c': // Full reset
			        // #ifdef SERIAL_OUT
			Serial.print(F("Clearing all EEPROM memory, are you sure? (Y/N): "));
			while (!Serial.available()) {
			} // Do nothing until a response.
			ans = Serial.read(); // Save response.
			if (ans == 'Y' || ans == 'y') { // If yes
				Serial.print(F(" Clearing. T- "));
				for (int i = 0; i < 4096; i++) {
					EEPROM.write(i, 0);
					if ((i % 512) == 0)
						Serial.print(8 - (i / 512));
				}
				Serial.println(F(" Done."));
			} else
				Serial.println(F(" Cancelled."));
			// #endif
			break; // END full reset
		} // switch
		break; // END EEPROM DIALOG
	case '\n': // Ignores newlines
		Serial.println(F("!Please disable newlines!"));
		break;
	case 'h': // HELP
		Serial.println(
			F("RTI Serial Help List\nThese are commands that can be "
			  "entered directly from the main command dialog.\nIf you are "
			  "experiencing issues, make sure newline is disabled."));
		Serial.println(F("\nCommand:\t\tFunction"));
		Serial.println(F("a\t\tEnter the settings dialog; contains settings "
		                 "beyond those on the display."));
		Serial.println(
			F("0\t\tIncrementing up one LED at a time, turn on one LED."));
		Serial.println(
			F(".\t\tIncrementing down one LED at a time, turn on one LED."));
		Serial.println(F("x\t\tTurn off all LEDs and start the counting usedfor  "
		                 "above commands again at zero."));
		Serial.println(
			F("1-3\t\tRun a column scan on the entered channel number."));
		Serial.println(F("r\t\tLED test (rings)."));
		Serial.println(F("c\t\tLED test (columns)."));
		Serial.println(F("m\t\tView the bytes of RAM remaining on the device."));
		Serial.println(F("s\t\tRestart the device. Cancelled with a c."));
		Serial.print(
			F("er\t\tReset the following EEPROM variables:\n\t\t\tSerial is set "
			  "to "));
		Serial.print(DEFAULT_BAUD_RATE);
		Serial.println(
			F(" baud\n\t\t\tMatching of shutter outputs is "
			  "disabled.\n\t\t\tDisplay is de-calibrated.\n\t\t\tDisplay "
			  "diagnostics are turned off."));
		Serial.println(F("ec\t\tClear ALL EEPROM - should only be done if "
		                 "absolutely necesary."));

		break; // END HELP
	default:
		Serial.println(F("Did nothing; that key is not assigned to a "
		                 "command.\n\nEnter 'h' for help."));
		break;
	} // switch
	Serial.print(F(">")); // Write a promt once any command is fully executed.
} // serialReact
