/*
 * File Name: 'input119718-34236-d9fdzn.ux0z.h'
 * File Purpose: EEPROM control classes
 * By: Nicholas Steele
 */

#include <Arduino.h> // for type definitions
#include <EEPROM.h>

/*
 */
template <class T> int EEPROM_writeAnything(int ee, const T &value) {
	const byte *p = (const byte *)(const void *)&value;
	unsigned int i;
	for (i = 0; i < sizeof(value); i++)
		EEPROM.write(ee++, *p++);
	return i;
} // EEPROM_writeAnything

/*
 */

template <class T> int EEPROM_readAnything(int ee, T &value) {
	byte *p = (byte *)(void *)&value;
	unsigned int i;
	for (i = 0; i < sizeof(value); i++)
		*p++ = EEPROM.read(ee++);
	return i;
} // EEPROM_readAnything
