/*
 * File Name: 'input119718-34236-1irz0wg.nq0n.h'
 * File Purpose: Header file for all cpp files.
 * By: Nicholas Steele
 */

#include <Arduino.h>

// Libraries
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include "EEPROMAnything.h"
#include <EEPROM.h>
#include <SPI.h>
#include <MemoryFree.h>

/*~~~~~PER-USE SETTINGS~~~~~*/
#define USE_ALT_PIN_SETUP // Uses PD2 in place of PD3 due to an error on the
                          // board. DISABLE IN RELEASE!

#define DEFAULT_BAUD_RATE 115200 // Sets the default baud rate

// Shows "Choose here" in text boxes that need to be set. Might be wanted; this
// was only added for first time use clarification.
// #define CHOOSE_HERE_SHOWN

/*~~~~~VARIABLES~~~~~*/

#define CUSTOM_GREEN 0x2DE0 // A darker, more readable green than RA8875_GREEN.
                            // Good for text, but not so much for anything
                            // thicker.
#define CUSTOM_BLUE 0x31F // A darker, more readable blue than RA8875_CYAN.

// Library only supports hardware SPI at this time
#define RA8875_INT 20
#define RA8875_CS 53
#define RA8875_RESET 21
static Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
static uint16_t tx, ty;
const PROGMEM int touchDebounceDelay = 200; // Noise delay for touch screen. may
                                            // not be needed, but the first
                                            // display we used had wierd noise
                                            // issues.
static boolean touched = false;
static unsigned long lastTouchTime;
static unsigned int lastTouchCoord[2] = {1025, 1025};
static int cal[4];

static float xScale;
static float yScale;

static unsigned char currentPage;

// Default channel names for display and serial communication use.
#define DEFAULT_CHANNEL_NAME_1 "Ultra Vt"
#define DEFAULT_CHANNEL_NAME_2 "White"
#define DEFAULT_CHANNEL_NAME_3 "InfraRed"

#define CHANNEL_NAME_MAX_CHARACTERS 8 // Should be left at 8, since some boxes
                                      // are designed to fit eightt characters
                                      // and no more.

static char errorChar = 'e';
static char shutterTriggerTypes[2][5] = {"High", "Low"};
static char chNames[3][CHANNEL_NAME_MAX_CHARACTERS + 1];
static char titlesArray[13][17] = {"Home", "Help", "Settings", "LED Order",
	                                 "Single LED", "Profiles", "Help",
	                                 "Column Scan",  "Ring Scan", "Single Ring",
	                                 "Single Column", "Test LEDs", "Positions"};
static char helpArray[13][16] = {"Home", "Help", "Settings", "LED Order",
	                               "Single LED", "Profiles", "Help",
	                               "Column Scan",  "Ring Scan", "Single Ring",
	                               "Single Column", "Test LEDs", "Positions"};

// Stop button/progress bar positions on the display, for patterns
#define STOPBUTTON_W 150
#define STOPBUTTON_H 75
#define STOPBUTTON_X (tft.width() / 2) - (STOPBUTTON_W / 2)
#define STOPBUTTON_Y (tft.height() / 2) - (STOPBUTTON_H / 2)
#define PROGBAR_X STOPBUTTON_X
#define PROGBAR_Y STOPBUTTON_Y + STOPBUTTON_H
#define PROGBAR_W STOPBUTTON_W
#define PROGBAR_H 25

// LED ORDER/PATTERN PAGE VARS
static char ledProfileName[32];
static char shutterProfileName[32];
// char name[32]; // placeholder
static bool listLedProfiles, listShutterProfiles, listChannel,
            listShutterTrigger,
            readingTouch; // Impacts what touch in these area does
static unsigned char ledProfile[3], patternChannel,
                     shutterProfile[3], ringColNum; // used to store vars needed
                                                    // to run LED pattens
static float placeholderFloat;
static unsigned long patternStartTime;
static int xcursortest;
// static bool shutterHigh;

static unsigned char ledList[64]; // List of all LEDs that could be used
static unsigned char ledCount = 64; // Number of LEDs that will be used
static unsigned char ledListPositionCounter = 0;
static unsigned char ledListTextCounter = 0;

static int COUNTnum = 0;

// KEYBOARD
static const unsigned char keyWidth = 70, keyHeight = 50, keySpace = 10,
                           adjust[5] = {0, 0, keyWidth / 2,
	                                      (keyWidth * 6) / 5,
	                                      (keyWidth * 2) / 2}, expansionRatio = 3;
static const char keys[50] = {"0123456789QWERTYUIOPASDFGHJKL#ZXCVBNM>##** ~<"};
static const char shiftKeys[] = {".,/-"};
static bool turnShiftOff;
#define SHIFT_POS_X (keyWidth * 3) + (keySpace * 3) + (keyWidth * \
	                                                     expansionRatio) + \
	(keySpace * (expansionRatio - 1))
#define SHIFT_POS_Y (keyHeight * 4) + (keySpace * 4)

// Shows "Choose here" message in text boxes that may need it.
#ifdef CHOOSE_HERE_SHOWN
static const char chooseHereText = {"Choose here"};
#endif /* ifdef CHOOSE_HERE_SHOWN */

const PROGMEM unsigned char PROFILE_NAME_LENGTH = 32;

static bool q[6] = {0, 0, 0}; // First three: Whether a channel is active
                              // Second three: whether a shutter is active
static uint8_t CHq[3]; // Stores row then column of currently active channel
static unsigned long millisDelay[3]; // Deactivation time for (first 3) LEDs
// (second 3) shutters
// static int shutterLength = 120; // Maximum shutter time in ms

static unsigned long baud = DEFAULT_BAUD_RATE; // Serial Baud Rate; default
                                               // written in

static unsigned long currentMillis; // Used to check runtime in ms

static void (*resetFunc)(void) = 0; // Software reset of arduino.

// char typeList[4][8] = {"Columns", "Rings", "Ring", "Column"};

/*~~~~~Controls LEDs~~~~~*/
class LED_object {
public:
	unsigned char num, r, c; // Stores channel and number of the LED.
	boolean ch1 = false, ch2 = false;

	// Must be set before using.
	// num should be an LID; zero-exlusive and up to 64.
	void setRC();

	void checkRow();

	void trigger(bool mode, unsigned char del, bool shutterHigh =
								 true, unsigned char shutterOnWait = 0);
};

extern LED_object ledArray[192];

/*~~~~~WRITING TO PORTS~~~~~*/
// xxx(port, bit)
#define sbi(x, y) x |= _BV(y) // set bit - using bitwise OR operator
#define cbi(x, y) x &= ~(_BV(y)) // clear bit - using bitwise AND operator
#define tbi(x, y) x ^= _BV(y) // toggle bit - using bitwise XOR operator
#define is_high(x, y) (x & _BV(y) == _BV(y))
// check if the y'th bit of register 'x' is high

/* _BV(a) is a macro which returns the value corresponding to 2 to the power
 * 'a'.
 * Thus _BV(PX3) would be 0x08 or 0b00001000. */

/*~~~~~ARRAY INFO~~~~~
 * Row Pins 1-8: PA5, PA4, PC4, PC5, PA6, PA7, PC7, PC6.
 * Channel 1 Pins 1-8: PF6, PF4, PF2, PF0, PF7, PF5, PF3, PF1
 * Channel 2 Pins 1-8: PJ0, PH0, PE4, PG5, PH1, PJ1, PD3, PE5
 * Channel 3 Pins 1-8: PE3, PH4, PH6, PB5, PH3, PH5, PB4, PB6
 */
#define RR(x)                                                                  \
	((x == 0)                                                                    \
	 ? PORTA                                                                 \
	 : ((x == 1)                                                             \
	    ? PORTA                                                          \
	    : ((x == 2)                                                      \
	       ? PORTC                                                   \
	       : ((x == 3)                                               \
	          ? PORTC                                            \
	          : ((x == 4)                                        \
	             ? PORTA                                     \
	             : ((x == 5)                                 \
	                ? PORTA                              \
	                : ((x == 6) ? PORTC                  \
	                   : PORTC))))))) // Row
// register
// for #
// Row Pins 1-8: PA5, PA4, PC4, PC5, PA6, PA7, PC7, PC6.
#define RB(x)                                                                  \
  \
	((x == 0)                                                                      \
	 ? PA5                                                                    \
	 : ((x == 1)                                                              \
	    ? PA4                                                             \
	    : ((x == 2)                                                       \
	       ? PC4                                                      \
	       : ((x == 3)                                                \
	          ? PC5                                               \
	          : ((x == 4)                                         \
	             ? PA6                                        \
	             : ((x == 5)                                  \
	                ? PA7                                 \
	                : ((x == 6) ? PC7 : PC6))))))) // Row
                                                 // bits
                                                 // for
                                                 // #x
// Channel 1 Pins 1-8: PF6, PF4, PF2, PF0, PF7, PF5, PF3, PF1
#define CH1R(x)                                                                \
	((x == 0)                                                                    \
	 ? PORTF                                                                 \
	 : ((x == 1)                                                             \
	    ? PORTF                                                          \
	    : ((x == 2)                                                      \
	       ? PORTF                                                   \
	       : ((x == 3)                                               \
	          ? PORTF                                            \
	          : ((x == 4)                                        \
	             ? PORTF                                     \
	             : ((x == 5)                                 \
	                ? PORTF                              \
	                : ((x == 6)                          \
	                   ? PORTF                       \
	                   : PORTF))))))) // Channel
                                    // 1
// Register
// for #x
#define CH1B(x)                                                                \
	((x == 0)                                                                    \
	 ? PF6                                                                   \
	 : ((x == 1)                                                             \
	    ? PF4                                                            \
	    : ((x == 2)                                                      \
	       ? PF2                                                     \
	       : ((x == 3)                                               \
	          ? PF0                                              \
	          : ((x == 4)                                        \
	             ? PF7                                       \
	             : ((x == 5)                                 \
	                ? PF5                                \
	                : ((x == 6) ? PF3                    \
	                   : PF1))))))) // Channel
                                  // 1 Bit
                                  // for
                                  // #x.
// Channel 2 Pins 1-8: PJ0, PH0, PE4, PG5, PH1, PJ1, PD3, PE5

#ifdef USE_ALT_PIN_SETUP // Uses alternative pins due to a fault on the
                         // origional prototype
#define CH2R(x)                                                                \
	((x == 0)                                                                    \
	 ? PORTJ                                                                 \
	 : ((x == 1)                                                             \
	    ? PORTH                                                          \
	    : ((x == 2)                                                      \
	       ? PORTE                                                   \
	       : ((x == 3)                                               \
	          ? PORTG                                            \
	          : ((x == 4) ? PORTH                                \
	             : ((x == 5) ? PORTJ                    \
	                : ((x == 6) ? PORTG        \
	                   : PORTE)))))))

	#define CH2B(x)                                                                \
    \
	((x == 0)                                                                      \
	 ? PJ0                                                                    \
	 : ((x == 1)                                                              \
	    ? PH0                                                             \
	    : ((x == 2)                                                       \
	       ? PE4                                                      \
	       : ((x == 3)                                                \
	          ? PG5                                               \
	          : ((x == 4)                                         \
	             ? PH1                                        \
	             : ((x == 5) ? PJ1                            \
	                : ((x == 6) ? PG2 : PE5)))))))

	#else /* ifdef USE_ALT_PIN_SETUP */

#define CH2R(x)                                                                \
	((x == 0)                                                                    \
	 ? PORTJ                                                                 \
	 : ((x == 1)                                                             \
	    ? PORTH                                                          \
	    : ((x == 2)                                                      \
	       ? PORTE                                                   \
	       : ((x == 3)                                               \
	          ? PORTG                                            \
	          : ((x == 4) ? PORTH                                \
	             : ((x == 5) ? PORTJ                    \
	                : ((x == 6) ? PORTD       \
	                   : PORTE)))))))
#define CH2B(x)                                                                \
  \
	((x == 0)                                                                      \
	 ? PJ0                                                                    \
	 : ((x == 1)                                                              \
	    ? PH0                                                             \
	    : ((x == 2)                                                       \
	       ? PE4                                                      \
	       : ((x == 3)                                                \
	          ? PG5                                               \
	          : ((x == 4)                                         \
	             ? PH1                                        \
	             : ((x == 5) ? PJ1                            \
	                : ((x == 6) ? PD3 : PE5)))))))
#endif /* ifdef USE_ALT_PIN_SETUP */

// Channel 3 Pins 1-8: PE3, PH4, PH6, PB5, PH3, PH5, PB4, PB6
#define CH3R(x)                                                                \
	((x == 0)                                                                    \
	 ? PORTE                                                                 \
	 : ((x == 1)                                                             \
	    ? PORTH                                                          \
	    : ((x == 2)                                                      \
	       ? PORTH                                                   \
	       : ((x == 3)                                               \
	          ? PORTB                                            \
	          : ((x == 4) ? PORTH                                \
	             : ((x == 5) ? PORTH                    \
	                : ((x == 6) ? PORTB        \
	                   : PORTB)))))))
#define CH3B(x)                                                                \
  \
	((x == 0)                                                                      \
	 ? PE3                                                                    \
	 : ((x == 1)                                                              \
	    ? PH4                                                             \
	    : ((x == 2)                                                       \
	       ? PH6                                                      \
	       : ((x == 3)                                                \
	          ? PB5                                               \
	          : ((x == 4)                                         \
	             ? PH3                                        \
	             : ((x == 5) ? PH5                            \
	                : ((x == 6) ? PB4 : PB6)))))))

#define SR(x)                                                                  \
	((x == 0) ? PORTG : ((x == 1) ? PORTC : PORTC)) // Shutter registers
#define SB(x) ((x == 0) ? PG0 : ((x == 1) ? PC0 : PC1)) // Shutter bits

#define ENR(x)                                                                 \
	((x == 0) ? PORTL                                                            \
	 : ((x == 1) ? PORTL : PORTL)) // Enable register for a channel
#define ENB(x) ((x == 0) ? PL3 : ((x == 1) ? PL2 : PL5)) // Enable pin bits
// Binary LED readout pins
#define BIR(x)                                                                 \
	((x == 0)                                                                    \
	 ? PORTA                                                                 \
	 : ((x == 1) ? PORTA                                                     \
	    : ((x == 2) ? PORTA                                         \
	       : ((x == 3) ? PORTA                             \
	          : ((x == 4) ? PORTC                 \
	             : PORTC)))))
#define BIB(x)                                                                 \
	((x == 0)                                                                    \
	 ? PA3                                                                   \
	 : ((x == 1)                                                             \
	    ? PA2                                                            \
	    : ((x == 2) ? PA1 : ((x == 3) ? PA0 : ((x == 4) ? PC2 : PC3)))))

/*~~~~~main.cpp~~~~~*/
bool advancedDelay(unsigned long time, bool shutterHigh = false,
                   unsigned char shutterOnTime = 10);

LED_object ledPlaceholder(unsigned char num);
// void assignCHNames();

/*~~~~~PROFILES~~~~~*/
void writeProfile(unsigned char type, unsigned char id, unsigned char *values);

void writeProfileName(unsigned char type, unsigned char id, char *name);

void readProfile(unsigned char type, unsigned char id, unsigned char *values);

void readProfileName(unsigned char type, unsigned char id, char *name);

/*~~~~~DISPLAY~~~~~*/
void beginDisplay();

void patternModeDisplay(float percentageComplete, unsigned char ledNum,
                        unsigned char channel = 1);

void checkTouch();

void calTouch();

void enterPage(unsigned char page);

void updateDisplayOBSOLETE();

bool updateDisplay();

void disableAllLEDs(char *leds);

/*~~~~~shutterCtrl.cpp~~~~~*/
void beginShutters();

void setShutter(unsigned char channel, unsigned char del,
                bool shutterHigh = true, bool turnOff = false,
                bool activationFromQ = false, unsigned char shutterOnWait = 0);

void checkShutters(bool shutterHigh = false, unsigned char shutterOnTime = 0);

/*~~~~~SERIAL COMMANDS~~~~~*/
void serialReact(char serialIn);

/*~~~~~patterns.cpp~~~~~*/
void colScan(unsigned char skip, unsigned char highDel, unsigned char lowDelay,
             unsigned char channel, unsigned char shutterOnTime = 10,
             bool shutterHigh = true, unsigned char shutterOnWait = 0);

void singleRing(unsigned char skip, unsigned char highDel,
                unsigned char lowDelay, unsigned char channel,
                unsigned char ringNum, unsigned char shutterOnTime = 10,
                bool shutterHigh = true, unsigned char shutterOnWait = 0);

void singleCol(unsigned char skip, unsigned char highDel,
               unsigned char lowDelay, unsigned char channel,
               unsigned char colNum, unsigned char shutterOnTime = 10,
               bool shutterHigh = true, unsigned char shutterOnWait = 0);

void ringScan(unsigned char skip, unsigned char highDel, unsigned char lowDelay,
              unsigned char channel, unsigned char shutterOnTime = 10,
              bool shutterHigh = true, unsigned char shutterOnWait = 0);

void patternScan(unsigned char skip, char highDel, unsigned char lowDelay,
                 unsigned char channel, LED_object *ledArray);

void patternRing(unsigned char skip, char highDel, unsigned char lowDelay,
                 unsigned char channel, unsigned char ringNum,
                 LED_object *ledArray);

void patternColumn(unsigned char skip, char highDel, unsigned char lowDelay,
                   unsigned char channel, unsigned char colNum,
                   LED_object *ledArray);

void patternSpiral(unsigned char skip, char highDel, unsigned char lowDelay,
                   unsigned char channel, LED_object *ledArray);

void readyScan(unsigned char skip, char highDel, unsigned char lowDelay,
               unsigned char channel);

/*~~~~~hardware.cpp~~~~~*/
void checkHardware(bool encoderCheck);

void binaryOut(unsigned char ledNum);

// EEPROM address table.
// 2 bytes: boolean vars and "reset bits" (see below)
#define SERIALBAUD_ADDR 2 // 4 bytes: Serial baud rate (data type is a long)
#define DEFAULT_CHANNEL 6 // 1 byte: Default channel to use on display
#define UNDEFINED1 7 // 1 byte: // Ends before #8

#define SCAN1_ADDR 8 // Scan Pattern #1
#define SCAN2_ADDR 11 // Scan Pattern #2
#define SCAN3_ADDR 14 // Scan Pattern #3

#define SPIRAL1_ADDR 17 // Spiral Pattern #1
#define SPIRAL2_ADDR 20 // Spiral Pattern #2
#define SPIRAL3_ADDR 23 // Spiral Pattern #3

#define RING1_ADDR 26 // Ring Pattern #1
#define RING2_ADDR 29 // Ring Pattern #2
#define RING3_ADDR 32 // Ring Pattern #3

#define COL1_ADDR 35 // Column Pattern #1
#define COL2_ADDR 38 // Column Pattern #2
#define COL3_ADDR 41 // Column Pattern #3

#define SCAN1NAME_ADDR 44 // 16 bytes: Scan Pattern #1 NAME // Byte #59
#define SCAN2NAME_ADDR 76 // 16 bytes: Scan Pattern #2 NAME // Byte #75
#define SCAN3NAME_ADDR 108 // 16 bytes: Scan Pattern #3 NAME // Byte #91

#define SPIRAL1NAME_ADDR 140 // 16 bytes: Spiral Pattern #1 NAME // Byte #107
#define SPIRAL2NAME_ADDR 172 // 16 bytes: Spiral Pattern #2 NAME // Byte #123
#define SPIRAL3NAME_ADDR 204 // 16 bytes: Spiral Pattern #3 NAME // Byte #139

#define RING1NAME_ADDR 236 // 16 bytes: Ring Pattern #1 NAME // Byte #155
#define RING2NAME_ADDR 268 // 16 bytes: Ring Pattern #2 NAME // Byte #171
#define RING3NAME_ADDR 300 // 16 bytes: Ring Pattern #3 NAME // Byte #187

#define COL1NAME_ADDR 332 // 16 bytes: Column Pattern #1 NAME // Byte #203
#define COL2NAME_ADDR 364 // 16 bytes: Column Pattern #2 NAME // Byte #219
#define COL3NAME_ADDR 396 // 16 bytes: Column Pattern #3 NAME // Byte #235

#define SHUTTER1_ADDR 428 // Shutter Profile #1
#define SHUTTER2_ADDR 429 // Shutter Profile #2
#define SHUTTER3_ADDR 430 // Shutter Profile #3
#define SHUTTER4_ADDR 431 // Shutter Profile #4
#define SHUTTER5_ADDR 432 // Shutter Profile #5
#define SHUTTER6_ADDR 433 // Shutter Profile #6
#define SHUTTER7_ADDR 434 // Shutter Profile #5
#define SHUTTER8_ADDR 435 // Shutter Profile #6
// Stores bits defining whether shutters are active high or low. x is shutter #
#define SHUTTERS_ACTIVELEVEL(x) bitRead(EEPROM.read(436), x - 1)
#define SHUTTERS_WRITE_ACTIVELEVEL(y, x)                                       \
	EEPROM.write(436, EEPROM.read(436) | (x << (y - 1)))

#define SHUTTER1NAME_ADDR 437 // Shutter 1 name
#define SHUTTER2NAME_ADDR 469 // Shutter 2 name
#define SHUTTER3NAME_ADDR 501 // Shutter 3 name
#define SHUTTER4NAME_ADDR 533 // Shutter 4 name
#define SHUTTER5NAME_ADDR 565 // Shutter 5 name
#define SHUTTER6NAME_ADDR 597 // Shutter 6 name
#define SHUTTER7NAME_ADDR 629 // Shutter 7 name
#define SHUTTER8NAME_ADDR 661 // Shutter 8 name //Ends at byte 692

#define TOUCH_CAL_X1_ADDR 693 // Touch screen calibration value for x
#define TOUCH_CAL_X2_ADDR 695 // Touch screen calibration value for x
#define TOUCH_CAL_Y1_ADDR 697 // Touch screen calibration value for y
#define TOUCH_CAL_Y2_ADDR 699 // Touch screen calibration value for y // Ends at
                              // byte 701

// USABLE POSITIONS ARE INVERTED IN EEPROM; 0 REPRESENTS A USABLE LED WHILE 1
// REPRESENTS NONUSABLE
// (Inverted so that default is all useable)
// Can be disabled; uses first two bytes of of EEPROM (at bottom of EEPROM
// table)
// Each requires 8 bytes. (8 bytes x 8 bits/byte == 64 led bits)
#define USABLE_IR_ARRAY 702 // Usable IR LEDs as bits
#define USABLE_WHITE_ARRAY 710 // Usable White LEDs
#define USABLE_UV_ARRAY 718 // Usable UV LEDs // Ends at byte 726
// These take the LED #1-64 as an input
#define READ_BIT_USABLE_ARRAY(x, y) bitRead(EEPROM.read(USABLE_IR_ARRAY + (x / \
	                                                                         8) + \
	                                                      y * 8), x % 8)
// #define READ_BIT_USABLE_WHITE_ARRAY(x)
// ~bitRead(EEPROM.read(USABLE_WHITE_ARRAY + (x/8)), x%8)
// #define READ_BIT_USABLE_UV_ARRAY(x) ~bitRead(EEPROM.read(USABLE_UV_ARRAY +
// (x/8)), x%8)

#define CHANNEL_NAME_1_ADDR 727 // Color name of the first channel; up to 9
                                // characters (9 bytes used)
#define CHANNEL_NAME_2_ADDR 736 // Color name of the seconnd channel; up to 9
                                // characters (9 bytes used)
#define CHANNEL_NAME_3_ADDR 745 // Color name of the third channel; up to 9
                                // characters (9 bytes used) // Last byte = 754

// Added as an afterthough of how shutters should operate
#define SHUTTER_START_DELAY_ADDR(shutterNum) (755 + shutterNum) // Last byte =
                                                                // 762

/*~~~~~END EEPROM TABLE~~~~~
 * First 2 bytes of EEPROM are individual settings by bit:
 */
// Byte #0:
#define IS_SERIAL_SET bitRead(EEPROM.read(0), 0) // Serial baud rate reset bit
#define TOGGLE_SERIAL_BIT EEPROM.write(0, EEPROM.read(0) ^ (1 << 0))

#define JOIN_SHUTTERS bitRead(EEPROM.read(0), 1) // Shutters all operate as one.
#define TOGGLE_JOIN_SHUTTERS EEPROM.write(0, EEPROM.read(0) ^ (1 << 1))

#define IS_TOUCH_CALIBRATED bitRead(EEPROM.read(0), 2)
#define TOGGLE_TOUCH_CALIBATED EEPROM.write(0, EEPROM.read(0) ^ (1 << 2)) // EEPROM.read(0)
                                                                          // |
                                                                          // (x
                                                                          // <<
                                                                          // 2))
// ~(EEPROM.read(0) ^ (x << 2))

#define DISPLAY_DIAGNOSTICS_MODE bitRead(EEPROM.read(0), 3)
#define TOGGLE_DISPLAY_DIAGNOSTICS_MODE EEPROM.write(0, EEPROM.read(0) ^ (1 << \
	                                                                        3))

// !! TAKES 3 BITS
#define USE_CUSTOM_ARRAY(x) bitRead(EEPROM.read(0), 4 + x)
#define TOGGLE_USE_CUSTOM_ARRAY(x) EEPROM.write(0, EEPROM.read(0) ^ (1 << 4 + \
	                                                                   x))

#define VERBOSE_SERIAL bitRead(EEPROM.read(0), 7) // Affects ammount of
                                                  // imformation written to
                                                  // serial.
#define TOGGLE_VERBOSE_SERIAL EEPROM.write(0, EEPROM.read(0) ^ (1 << 7))

// Byte #1:
