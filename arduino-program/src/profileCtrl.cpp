/* This file manages all profiles.
 * Profile type numbers:
 * 0: Scan
 * 1: Spiral
 * 2: Ring
 * 3: Column
 * 4: Shutter
 *
 * Profile ID #'s are all just their english numbering (1, 2, or 3)
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif // ifndef HEADERS_H

/*
 * Fuction Usage: Create a profile from given values
 * Parameters: Profile type, Profile ID, and the values.
 */

void writeProfile(unsigned char type, unsigned char id, unsigned char *values) {
	// Writes to a profile's EEPROM location with data to save.
	// Takes profile Type #, ID #, step count, high delay, and low delay.
	switch (type) { // Figure out which type is used
	case 0: // Scan
		if (id == 1) // Profile #1
			for (int i = SCAN1_ADDR; i < SCAN1_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - SCAN1_ADDR]); // Store the value

		if (id == 2) // Profile #2
			for (int i = SCAN2_ADDR; i < SCAN2_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - SCAN2_ADDR]); // Store the value

		if (id == 3) // Profile #3
			for (int i = SCAN3_ADDR; i < SCAN3_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - SCAN3_ADDR]); // Store the value
		break;

	case 1: // Spiral
		if (id == 1) // Profile #1
			for (int i = SPIRAL1_ADDR; i < SPIRAL1_ADDR + 3;
			     i++) // 3 values in a profile
				EEPROM.write(i, values[i - SPIRAL1_ADDR]); // Store the value

		if (id == 2) // Profile #2
			for (int i = SPIRAL2_ADDR; i < SPIRAL2_ADDR + 3;
			     i++) // 3 values in a profile
				EEPROM.write(i, values[i - SPIRAL2_ADDR]); // Store the value

		if (id == 3) // Profile #3
			for (int i = SPIRAL3_ADDR; i < SPIRAL3_ADDR + 3;
			     i++) // 3 values in a profile
				EEPROM.write(i, values[i - SPIRAL3_ADDR]); // Store the value
		break;

	case 2: // Ring
		if (id == 1) // Profile #1
			for (int i = RING1_ADDR; i < RING1_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - RING1_ADDR]); // Store the value

		if (id == 2) // Profile #2
			for (int i = RING2_ADDR; i < RING2_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - RING2_ADDR]); // Store the value

		if (id == 3) // Profile #3
			for (int i = RING3_ADDR; i < RING3_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - RING3_ADDR]); // Store the value
		break;

	case 3: // Column
		if (id == 1) // Profile #1
			for (int i = COL1_ADDR; i < COL1_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - COL1_ADDR]); // Store the value

		if (id == 2) // Profile #2
			for (int i = COL2_ADDR; i < COL2_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - COL2_ADDR]); // Store the value

		if (id == 3) // Profile #3
			for (int i = COL3_ADDR; i < COL3_ADDR + 3; i++) // 3 values in a profile
				EEPROM.write(i, values[i - COL3_ADDR]); // Store the value
		break;

	case 4: // Shutters
		if (id == 1) {
			EEPROM.write(SHUTTER1_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 2) {
			EEPROM.write(SHUTTER2_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 3) {
			EEPROM.write(SHUTTER3_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 4) {
			EEPROM.write(SHUTTER4_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 5) {
			EEPROM.write(SHUTTER5_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 6) {
			EEPROM.write(SHUTTER6_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 7) {
			EEPROM.write(SHUTTER7_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}
		if (id == 8) {
			EEPROM.write(SHUTTER8_ADDR, values[0]); // Store the values
			SHUTTERS_WRITE_ACTIVELEVEL(id, values[1]);
		}

		EEPROM.write(SHUTTER_START_DELAY_ADDR(id - 1), values[2]);
		break;
	} // switch
} // writeProfile

/*
 * Fuction Usage: Name a profile
 * Parameters: Profile type, Profile ID, and the name.
 */

void writeProfileName(unsigned char type, unsigned char id, char *name) {
	// Writes a profile name.
	switch (type) { // Figure out which type is used
	case 0: // Scan
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SCAN1NAME_ADDR + i, name[i]); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SCAN2NAME_ADDR + i, name[i]); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SCAN3NAME_ADDR + i, name[i]); // Read and set name
		break;

	case 1: // Spiral
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SPIRAL1NAME_ADDR + i, name[i]); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SPIRAL2NAME_ADDR + i, name[i]); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SPIRAL3NAME_ADDR + i, name[i]); // Read and set name
		break;

	case 2: // Ring
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(RING1NAME_ADDR + i, name[i]); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(RING2NAME_ADDR + i, name[i]); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(RING3NAME_ADDR + i, name[i]); // Read and set name
		break;

	case 3: // Column
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(COL1NAME_ADDR + i, name[i]); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(COL2NAME_ADDR + i, name[i]); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(COL3NAME_ADDR + i, name[i]); // Read and set name
		break;

	case 4: // Shutters
		if (id == 1)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER1NAME_ADDR + i, name[i]); // Read and set name

		if (id == 2)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER2NAME_ADDR + i, name[i]); // Read and set name

		if (id == 3)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER3NAME_ADDR + i, name[i]); // Read and set name

		if (id == 4)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER4NAME_ADDR + i, name[i]); // Read and set name

		if (id == 5)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER5NAME_ADDR + i, name[i]); // Read and set name

		if (id == 6)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER6NAME_ADDR + i, name[i]); // Read and set name

		if (id == 7)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER7NAME_ADDR + i, name[i]); // Read and set name

		if (id == 8)
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++)
				EEPROM.write(SHUTTER8NAME_ADDR + i, name[i]); // Read and set name

		break;
	} // switch
} // writeProfileName

/*
 * Fuction Usage: Get a given profile's values
 * Parameters: Profile type, Profile ID, and the variable to store values in.
 */

void readProfile(unsigned char type, unsigned char id, unsigned char *values) {
	// Reads a profile's eeprom, returnes itself as an integer array.
	// Takes the profile Type/ ID # and an array to manipulate.
	switch (type) { // Figure out which type is used
	case 0: // Scan
		if (id == 1) // Profile #1
			for (int i = SCAN1_ADDR; i < SCAN1_ADDR + 3; i++) // 3 values in a profile
				values[i - SCAN1_ADDR] = EEPROM.read(i); // Store the value

		if (id == 2) // Profile #2
			for (int i = SCAN2_ADDR; i < SCAN2_ADDR + 3; i++) // 3 values in a profile
				values[i - SCAN2_ADDR] = EEPROM.read(i); // Store the value

		if (id == 3) // Profile #3
			for (int i = SCAN3_ADDR; i < SCAN3_ADDR + 3; i++) // 3 values in a profile
				values[i - SCAN3_ADDR] = EEPROM.read(i); // Store the value
		break;

	case 1: // Spiral
		if (id == 1) // Profile #1
			for (int i = SPIRAL1_ADDR; i < SPIRAL1_ADDR + 3;
			     i++) // 3 values in a profile
				values[i - SPIRAL1_ADDR] = EEPROM.read(i); // Store the value

		if (id == 2) // Profile #2
			for (int i = SPIRAL2_ADDR; i < SPIRAL2_ADDR + 3;
			     i++) // 3 values in a profile
				values[i - SPIRAL2_ADDR] = EEPROM.read(i); // Store the value

		if (id == 3) // Profile #3
			for (int i = SPIRAL3_ADDR; i < SPIRAL3_ADDR + 3;
			     i++) // 3 values in a profile
				values[i - SPIRAL3_ADDR] = EEPROM.read(i); // Store the value
		break;

	case 2: // Ring
		if (id == 1) // Profile #1
			for (int i = RING1_ADDR; i < RING1_ADDR + 3; i++) // 3 values in a profile
				values[i - RING1_ADDR] = EEPROM.read(i); // Store the value

		if (id == 2) // Profile #2
			for (int i = RING2_ADDR; i < RING2_ADDR + 3; i++) // 3 values in a profile
				values[i - RING2_ADDR] = EEPROM.read(i); // Store the value

		if (id == 3) // Profile #3
			for (int i = RING3_ADDR; i < RING3_ADDR + 3; i++) // 3 values in a profile
				values[i - RING3_ADDR] = EEPROM.read(i); // Store the value
		break;

	case 3: // Column
		if (id == 1) // Profile #1
			for (int i = COL1_ADDR; i < COL1_ADDR + 3; i++) // 3 values in a profile
				values[i - COL1_ADDR] = EEPROM.read(i); // Store the value

		if (id == 2) // Profile #2
			for (int i = COL2_ADDR; i < COL2_ADDR + 3; i++) // 3 values in a profile
				values[i - COL2_ADDR] = EEPROM.read(i); // Store the value

		if (id == 3) // Profile #3
			for (int i = COL3_ADDR; i < COL3_ADDR + 3; i++) // 3 values in a profile
				values[i - COL3_ADDR] = EEPROM.read(i); // Store the value
		break;
	case 4: // Shutters
		if (id == 1) {
			values[0] = EEPROM.read(SHUTTER1_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 2) {
			values[0] = EEPROM.read(SHUTTER2_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 3) {
			values[0] = EEPROM.read(SHUTTER3_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 4) {
			values[0] = EEPROM.read(SHUTTER4_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 5) {
			values[0] = EEPROM.read(SHUTTER5_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 6) {
			values[0] = EEPROM.read(SHUTTER6_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 7) {
			values[0] = EEPROM.read(SHUTTER7_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		if (id == 8) {
			values[0] = EEPROM.read(SHUTTER8_ADDR); // Store the values
			values[1] = SHUTTERS_ACTIVELEVEL(id);
		}
		values[2] = EEPROM.read(SHUTTER_START_DELAY_ADDR(id - 1));
		break;
	} // switch
} // readProfile

/*
 * Fuction Usage: Get a given profile's name
 * Parameters: Profile type, Profile ID, and the variable to store name in.
 */

void readProfileName(unsigned char type, unsigned char id, char *name) {
	// int i = 0;      // Variable is used later to return final character set
	switch (type) { // Figure out which type is used
	case 0: // Scan
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SCAN1NAME_ADDR + i); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SCAN2NAME_ADDR + i); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SCAN3NAME_ADDR + i); // Read and set name
		break;

	case 1: // Spiral
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SPIRAL1NAME_ADDR + i); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SPIRAL2NAME_ADDR + i); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SPIRAL3NAME_ADDR + i); // Read and set name
		break;

	case 2: // Ring
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(RING1NAME_ADDR + i); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(RING2NAME_ADDR + i); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(RING3NAME_ADDR + i); // Read and set name
		break;

	case 3: // Column
		if (id == 1) // Profile #1
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(COL1NAME_ADDR + i); // Read and set name

		if (id == 2) // Profile #2
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(COL2NAME_ADDR + i); // Read and set name

		if (id == 3) // Profile #3
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(COL3NAME_ADDR + i); // Read and set name
		break;

	case 4: // Shutters
		if (id == 1) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER1NAME_ADDR + i); // Read and set name
		}
		if (id == 2) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER2NAME_ADDR + i); // Read and set name
		}
		if (id == 3) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER3NAME_ADDR + i); // Read and set name
		}
		if (id == 4) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER4NAME_ADDR + i); // Read and set name
		}
		if (id == 5) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER5NAME_ADDR + i); // Read and set name
		}
		if (id == 6) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER6NAME_ADDR + i); // Read and set name
		}
		if (id == 7) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER7NAME_ADDR + i); // Read and set name
		}
		if (id == 8) {
			for (int i = 0; i < PROFILE_NAME_LENGTH; i++) // For each character
				name[i] = EEPROM.read(SHUTTER8NAME_ADDR + i); // Read and set name
		}
		break;
	} // switch
	  // return i; // Returns number of characters that we set in the array
} // readProfileName
