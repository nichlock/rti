#ifndef HEADERS_H
#define HEADERS_H
#include <headers.h>
#endif

bool filterTouch();
void preformAction(unsigned char action);
void showNumPad(int xStart, int yStart);
char readNumPad(int xStart, int yStart, int tx, int ty);
void updateNumPad(int xStart, int yStart, int place, char *ch);
void disableAllLEDs(char *leds);
void displaySingleLed();
void settingsContent();
void ledOrderContent();
void runPattern(unsigned char type);
void drawPatternLaunchPage(unsigned char type);
void timeToString(float val, char *ch, bool add_s = false,
                  bool addPeriod = true);
void updatePatternLaunchPage(unsigned char type);
float numPadReadFloat(bool allowExit, float upperLimit, float lowerLimit,
                      int xStart, int yStart);
void profilesContent();
void setProfile(unsigned char profNum);
void showKeyBoard(int xStart, int yStart);
char readKeyBoard(int xStart, int yStart, int tx, int ty);
void updateKeyBoard(int xStart, int yStart, unsigned char place, char *c);
void setShiftState(int x, int y, bool shift, bool capsLock);
void selfTest();
void LEDPosition();
// void drawAdvancedSettingsPage(); // Omitted due to lack of functionality

// void drawPatternLaunchPage(unsigned char type, unsigned char *vars,
//                            unsigned char toUpdate);
// void (*resetFunfc)(void) = 0; // Software reset of arduino.

// Buttons with very simple functions were much easier to do through a button
// object; most buttons that are purely used in menus are button objects. This
// does however take a lot of RAM, so it is used sparingly (max 8 button object
// at a time)
class buttonObj {
public:
  int width, height, x, y;
  // Button type (2 is default) and what to do when pressed.
  unsigned char t = 2;
  unsigned char action;
  // Types:
  // 0 - Home
  // 1 - Help
  // 2 - Standard button
  // 3 - boolean setting button
  boolean m; // Mode. Used for boolean button type 3.
  // Text to place on button.
  char text[16];
  bool checkTouch(int tx, int ty) {
    // Checks if an x/y coordinate is touching this button, acts accordingly
    if (t == 1 && m == true)
      return false;
    if (tx >= x && tx <= x + width && ty >= y && ty <= y + height) {
      Serial.println("Button action triggered, preforming action...");
      preformAction(action);
      return true;
    }
    return false;
  }
  void setFromType(unsigned char type) {
    // For simplicity, some common  buttons are auto-configured by setting their
    // type.
    t = type;
    if (type == 0) {
      width = 100;
      height = 50;
      x = 10;
      y = 10;
      setText("Home");
      action = 0;
    }
    if (type == 1) {
      width = 100;
      height = 50;
      x = tft.width() - 10 - width;
      y = 10;
      setText("Help");
      action = 1;
    }
  }
  void setText(String str) {
    // Sets a string to the char.
    int i = 0;
    for (i; i < str.length(); i++)
      text[i] = str.charAt(i);
    for (i; i < 16; i++)
      text[i] = 0;
  }
  void drawBtn() {
    // Draws the button on the display

    if (t == 3) {
      tft.drawRect(x, y, width, height, RA8875_RED);
      tft.textMode();
      tft.textSetCursor(x, y);
      if (m)
        tft.textTransparent(CUSTOM_GREEN);
      else
        tft.textTransparent(RA8875_RED);
      tft.textEnlarge(2);
      tft.textWrite(text);
      tft.graphicsMode();
    } else {
      tft.drawRect(x, y, width, height, RA8875_RED);
      tft.textMode();
      tft.textSetCursor(x, y);
      tft.textTransparent(RA8875_BLACK);
      tft.textEnlarge(2);
      tft.textWrite(text);
      tft.graphicsMode();
    }
  }
};

buttonObj buttons[8]; // Limited to 6 buttons at a time on the display

void setCharArray(char *ch, String str, unsigned char chLen) {
  // Sets a string to the char.
  int i = 0;
  for (i; i < str.length(); i++) // For the length of the char
    ch[i] = str.charAt(i);
  for (i; i < chLen; i++) // Clear rest of the char array
    ch[i] = 0;
}

// Resets buttons for page changes
void resetButtons(unsigned char i = 0) {
  for (i; i < 8; i++) {
    buttons[i].x = 0;
    buttons[i].y = 0;
    buttons[i].width = 0;
    buttons[i].height = 0;
    buttons[i].t = 2;
  }
}

void enterPage(unsigned char page) {
  // Displays the given page.
  char title[16];
  resetButtons();
  unsigned char n; // Counter variable
  // Place the top banner:
  tft.fillScreen(RA8875_WHITE);
  tft.fillRect(0, 0, tft.width(), 70, RA8875_CYAN);
  buttons[0].setFromType(0);
  buttons[1].setFromType(1);
  buttons[0].drawBtn();
  buttons[1].drawBtn();
  if (DISPLAY_DIAGNOSTICS_MODE == 1) {
    tft.textMode();
    tft.textSetCursor(0, 0);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);
    char c[5];
    itoa(freeMemory(), c, 10);
    tft.textWrite(c);
    tft.textSetCursor(0, tft.height() - 30);
    itoa(page, c, 10);
    tft.textWrite(c);
    tft.textSetCursor(tft.width() - 50, tft.height() - 30);
    itoa(currentPage, c, 10);
    tft.textWrite(c);
    tft.graphicsMode();
  }

  // unsigned char LEDnum[6];
  // unsigned char positionTracker[2];

  // Serial.println(page);
  switch (page) {
  case 0: // BEGIN HOME PAGE
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titles[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    // --> First Button
    n = 0;
    buttons[2].width = 250;
    buttons[2].height = 50;
    buttons[2].x = 20;
    buttons[2].y = 70 + 20 + (50 * n) + (20 * n);
    buttons[2].setText(titlesArray[3]);
    buttons[2].action = 3; // Multi LED is action 3
    buttons[2].drawBtn();
    // --> End First Button
    // --> Second Button
    n++;
    buttons[3].width = 250;
    buttons[3].height = 50;
    buttons[3].x = 20;
    buttons[3].y = 70 + 20 + (50 * n) + (20 * n);
    buttons[3].setText(titlesArray[4]);
    buttons[3].action = 4; // Single LED is action 4
    buttons[3].drawBtn();
    // --> End Second Button
    // --> Third Button
    n++;
    buttons[4].width = 250;
    buttons[4].height = 50;
    buttons[4].x = 20;
    buttons[4].y = 70 + 20 + (50 * n) + (20 * n);
    buttons[4].setText(titlesArray[2]);
    buttons[4].action = 5; // Settings is action 5
    buttons[4].drawBtn();
    // --> End Third Button
    // --> Fourth Button
    n++;
    buttons[5].width = 250;
    buttons[5].height = 50;
    buttons[5].x = 20;
    buttons[5].y = 70 + 20 + (50 * n) + (20 * n);
    buttons[5].setText(titlesArray[5]);
    buttons[5].action = 6; // Profiles is action 6
    buttons[5].drawBtn();
    // --> End Fourth Button
    // -- > Begin Fifth Button
    n++;
    buttons[6].width = 250;
    buttons[6].height = 50;
    buttons[6].x = 20;
    buttons[6].y = 70 + 20 + (50 * n) + (20 * n);
    buttons[6].setText(titlesArray[11]);
    buttons[6].action = 30; // Self Test is action 30
    buttons[6].drawBtn();
    // --> End Fifth Button
    // -- > Begin Sixth Button
    n = 0;
    buttons[7].width = 250;
    buttons[7].height = 50;
    buttons[7].x = 20 + 250 + 20;
    buttons[7].y = 70 + 20 + (50 * n) + (20 * n);
    buttons[7].setText(titlesArray[12]);
    buttons[7].action = 31; // LED postion settings is action 31
    buttons[7].drawBtn();
    // --> End Sixth Button
    break; // END HOME PAGE
  case 1:  // BEGIN RESERVED PAGE
    // Page not used.
    break; // END RESERVED PAGE
  case 2:  // SETTINGS
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titles[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content

    settingsContent();

    break;
  case 3: // LED ORDER
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titles[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content

    ledOrderContent();

    break;
  case 4: // LED Single
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titles[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    displaySingleLed();
    break;
  case 5: // PROFILES
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, "Profiles", 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    profilesContent();
    break;
  case 6: // BEGIN HELP
    // Make the normal help button inaccessible to avoid infinite loops
    buttons[1].m = false;
    // Title
    tft.textMode();
    // setCharArray(title, titlesArray[1], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[1]);
    tft.graphicsMode();
    // Content
    // --> Exit Button
    buttons[2].width = 100;
    buttons[2].height = 50;
    buttons[2].x = (tft.width() / 2 - (4 * 25) / 2);
    buttons[2].y = 350;
    buttons[2].setText("Back");
    buttons[2].action = 255; // Return to page action
    buttons[2].drawBtn();
    // --> Exit Button
    tft.textMode();
    // setCharArray(title, helpArray[currentPage], 16);
    tft.textSetCursor(50, 70 + 50);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);
    tft.textWrite(helpArray[currentPage]);
    tft.graphicsMode();
    break; // END HELP

  case 7: // BEGIN FULL SCAN
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titlesArray[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    runPattern(0);
    break; // END FULL SCAN
  case 8:  // BEGIN SPIRAL SCAN
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titlesArray[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    runPattern(1);
    break; // END SPIRAL SCAN
  case 9:  // BEGIN RING
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titlesArray[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    runPattern(2);
    break; // END RING
  case 10: // BEGIN COLUMN
    currentPage = page;
    // Title
    tft.textMode();
    // setCharArray(title, titlesArray[page], 16);
    tft.textSetCursor((tft.width() / 2 - (strlen(titlesArray[page]) * 25) / 2),
                      10);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(titlesArray[page]);
    tft.graphicsMode();
    // Content
    runPattern(3);
    break; // END COLUMN

  default:
    Serial.println("No Action; Page Unknown");
    break;
  }
}

// TOUCH PAD WIDTH: 220;
// TOUCH PAD HEIGHT: 400;

void setProfile(const unsigned char profType) {

  // Pages do not apply to this function
  char placeholderChar32[32]; // used as a placeholder
  resetButtons();
  unsigned char n; // Counter variable
  // Place the top banner:
  tft.fillScreen(RA8875_WHITE);
  tft.fillRect(0, 0, tft.width(), 70, RA8875_CYAN);
  buttons[0].setFromType(0);
  buttons[1].setFromType(1);
  buttons[0].drawBtn();
  buttons[1].drawBtn();
  tft.textMode();
  if (DISPLAY_DIAGNOSTICS_MODE == 1) {
    tft.textSetCursor(0, 0);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);
    // char memChar[5];
    itoa(freeMemory(), placeholderChar32, 10);
    tft.textWrite(placeholderChar32, 5);
  }
  tft.textSetCursor(150, 10);
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textWrite("Profile: ");
  if (profType == 0)
    tft.textWrite("Column Scan");
  if (profType == 1)
    tft.textWrite("Ring scan");
  if (profType == 2)
    tft.textWrite("Single Ring");
  if (profType == 3)
    tft.textWrite("Single Column");
  if (profType == 4)
    tft.textWrite("Shutters");
  if (profType == 5)
    tft.textWrite("All");
  tft.graphicsMode();
  // showKeyBoard(5, tft.height() - 290 - 10);
  // tft.drawRect(tft.width() / 2 - (24 * 32) / 2, tft.height() - 290 - 10 - 80,
  //              24 * 32, 60, RA8875_RED);

  // placeholder and new profile name holder with 32 characters
  static char c;
  // static char newProfileName32[PROFILE_NAME_LENGTH]; // uses ledProfileName
  static unsigned char place, profileNumber;

  place = 0;
  profileNumber = 10; // Set to impossible number
  for (int i = 0; i < 32; i++)
    ledProfileName[i] = 0; // Variable is used as placeholder later

  // DRAW/FILL IN PROFILE LISTS
  if (profType != 4 && profType != 5) { // LED TYPE PROFILE
    tft.fillRect(20, 100, 512, 3 * 45, RA8875_WHITE);
    for (int y1 = 0; y1 < 3; y1++) { // PLACE BOXES
      tft.drawRect(20, 100 + (y1 * 45), 512, 45, RA8875_RED);
      tft.textMode();
      tft.textSetCursor(20, 100 + (y1 * 45));
      tft.textTransparent(RA8875_BLACK);
      readProfileName(profType, y1 + 1, placeholderChar32);
      tft.textEnlarge(1);
      tft.textWrite(placeholderChar32, 32);
      tft.graphicsMode();
    } // END PLACE BOXES
  }   // END PROFILE
  else if (profType == 5) {
    for (int y1 = 0; y1 < 3; y1++) { // PLACE BOXES
      tft.drawRect(20, 100 + (y1 * 45), 512, 45, RA8875_RED);
      tft.textMode();
      tft.textSetCursor(20, 100 + (y1 * 45));
      tft.textTransparent(RA8875_BLACK);
      itoa(y1 + 1, placeholderChar32, 10);
      tft.textEnlarge(1);
      tft.textWrite("Edit Profiles Numbered: ");
      tft.textWrite(placeholderChar32);
      tft.graphicsMode();
    } // END PLACE BOXES
  }

  else { // SHUTTER PROFILE
    tft.fillRect(20, 100, 512, 8 * 45, RA8875_WHITE);
    for (int y1 = 0; y1 < 8; y1++) { // PLACE BOXES
      tft.drawRect(20, 100 + (y1 * 45), 512, 45, RA8875_RED);
      tft.textMode();
      tft.textSetCursor(20, 100 + (y1 * 45));
      tft.textTransparent(RA8875_BLACK);
      tft.textEnlarge(1);
      readProfileName(4, y1 + 1, placeholderChar32);
      tft.textWrite(placeholderChar32, 32);
      tft.graphicsMode();
    } // END PLACE BOXES
  }   // END SHUTTER PROFILE

  // ***************************
  // PROFILE SELECTOR while loop, exits once a profile is set.
  while (profileNumber == 10) { // Stops by setting profileNumber

    // Read and filter incomming touches
    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        return;
      } // Home button

      // Allow user to choose from list of options for selected profile type:
      // CHECK DROPDOWNS
      if (tx > 20 && tx <= 20 + 512) { // tx checker
        if (profType == 4) {           // Profile list 8 entries long
          // Display for loop; no need to test before three due to above loop
          for (int y1 = 0; y1 < 8; y1++) {
            if (ty > 100 + (y1 * 45) && ty <= 100 + (y1 * 45) + 45) {
              profileNumber = y1 + 1;
            } // Y checker
          }   // For loop
        }     // Profile type: shutters only

        else {                             // Profile list 3 entries long
          for (int y1 = 0; y1 < 3; y1++) { // Display for loop
            if (ty > 100 + (y1 * 45) && ty <= 100 + (y1 * 45) + 45) {
              profileNumber = y1 + 1;
            }       // Y checker
          }         // For loop
          continue; // Skip to end of while loop
        }           // Profile list 3 entries long
      }             // tx checker
    }               // Touch checker
  }                 // While loop

  // Clear screen.
  tft.fillRect(0, 70, tft.width(), tft.height() - 70, RA8875_WHITE);

  // Place type-in box and then keyboard
  tft.drawRect(tft.width() / 2 - (24 * 32) / 2, tft.height() - 290 - 10 - 80,
               24 * 32, 60, RA8875_RED);
  showKeyBoard(5, tft.height() - 290 - 10);
  // Serial.println(profType);

  // ***************************
  // PROFILE NAME SETUP while loops: these run for the correct profile type.
  // they are left after choosing a name (profType must NEVER be changed! use
  // "break;" instead)

  // MUST exit with "break;"! Do not change profType!
  while (profType != 4) { // All types other than shutter
                          // Read and filter incomming touches
    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        return;
      } // Home button

      // Check/update keyboard
      c = readKeyBoard(5, tft.height() - 290 - 10, tx, ty);
      if (c != '!' && c != '~' && c != '>' && place < PROFILE_NAME_LENGTH) {
        if (c == '<')
          if (place > 0)
            place--; // Backspace pressed; go backwards
          else {
          }
        else {
          ledProfileName[place] = c; // Add character to new name
          place++;                   // Go forward one position in name
        }
        updateKeyBoard(tft.width() / 2 - (24 * 32) / 2,
                       tft.height() - 290 - 10 - 80 + 4, place, &c);
      }
      if (place == PROFILE_NAME_LENGTH || c == '>') {
        // Name has reached limit or enter was pressed
        Serial.print(F("Selected name: "));
        Serial.println(ledProfileName);
        break;
      }

    } // Touch checker
  }   // COL SCAN, RING SCAN, SINGLE RING, SINGLE COL loop

  // MUST exit with "break;"! Do not change profType!
  while (profType == 4) { // shutter profiles
                          // Read and filter incomming touches
    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        return;
      } // Home button

      // Check/update keyboard
      c = readKeyBoard(5, tft.height() - 290 - 10, tx, ty);
      if (c != '!' && c != '~' && c != '>' && place < PROFILE_NAME_LENGTH) {
        if (c == '<') {
          place--; // Backspace pressed; go backwards
          updateKeyBoard(tft.width() / 2 - (24 * 32) / 2,
                         tft.height() - 290 - 10 - 80 + 4, place, &c);
        } else {
          updateKeyBoard(tft.width() / 2 - (24 * 32) / 2,
                         tft.height() - 290 - 10 - 80 + 4, place, &c);
          ledProfileName[place] = c; // Add character to new name
          place++;                   // Go forward one position in name
        }
      }
      if (place == PROFILE_NAME_LENGTH || c == '>') {
        // Name has reached limit or enter was pressed
        Serial.print(F("Selected name: "));
        Serial.println(ledProfileName);
        break;
      }
    } // Touch checker
  }   // SHUTTERS white loop

  // ***************************
  // ADDITIONAL SETTINGS FOR PROFILES: these are settings that are entered
  // one by one by the user.

  // Write the first question outside of while loops
  tft.fillRect(0, 70, tft.width(), tft.height() - 70, RA8875_WHITE);
  tft.textMode();
  tft.textEnlarge(1);
  tft.textSetCursor(20, 100);
  tft.textTransparent(RA8875_BLACK);
  tft.textWrite("Profile name: ");
  tft.textTransparent(CUSTOM_GREEN);
  tft.textWrite(ledProfileName);
  tft.textTransparent(RA8875_BLACK);
  tft.textSetCursor(20, 140);

  if (profType != 4) {
    tft.textWrite("Enter the time the LED should ");
    tft.textSetCursor(40, 180);
    tft.textWrite("remain ON (.1-25.5s):");
    // draw a numPad and get on time
    tft.graphicsMode(); // For numPadReadFloat
    placeholderFloat = numPadReadFloat(true, 25.5, .1, 560, 70);
    if (placeholderFloat == 27.5) // Error condition returning max+2 (user exit)
      return;                     // Skip to end of loop
    tft.textMode();
    tft.textEnlarge(1);
    tft.textSetCursor(380, 180);
    tft.textTransparent(CUSTOM_GREEN);
    ledProfile[1] = placeholderFloat * 10;
    timeToString(placeholderFloat, placeholderChar32);
    Serial.println(placeholderChar32);
    tft.textTransparent(CUSTOM_GREEN);
    tft.textWrite(placeholderChar32);

    Serial.println("drawing off time...");

    // draw a numPad and get off time
    tft.textTransparent(RA8875_BLACK);
    tft.textSetCursor(20, 220);
    tft.textWrite("Enter the time the LED should ");
    tft.textSetCursor(40, 260);
    tft.textWrite("remain OFF (0-25.5s):");
    // draw a numPad and get on time
    tft.graphicsMode(); // For numPadReadFloat
    placeholderFloat = numPadReadFloat(true, 25.5, 0, 560, 70);
    if (placeholderFloat == 27.5) // Error condition returning max+2 (user exit)
      return;                     // Skip to end of loop
    tft.textMode();               // numPadReadFloat turns textMode off
    tft.textEnlarge(1);
    tft.textSetCursor(380, 260);
    tft.textTransparent(CUSTOM_GREEN);
    ledProfile[2] = placeholderFloat * 10;
    timeToString(placeholderFloat, placeholderChar32);
    Serial.println(placeholderChar32);
    tft.textTransparent(CUSTOM_GREEN);
    tft.textWrite(placeholderChar32);

    // draw a numPad and get LED increment ammount
    tft.textTransparent(RA8875_BLACK);
    tft.textSetCursor(20, 300);
    tft.textWrite("Enter the number of LEDs to ");
    tft.textSetCursor(40, 340);
    tft.textWrite("increment by (1-64 LEDs):");
    // draw a numPad and get on time
    tft.graphicsMode(); // For numPadReadFloat
    placeholderFloat = numPadReadFloat(true, 64, 1, 560, 70);
    if (placeholderFloat == 66) // Error condition returning max+2 (user exit)
      return;                   // Skip to end of loop
    tft.textMode();             // numPadReadFloat turns textMode off
    tft.textEnlarge(1);
    tft.textSetCursor(450, 340);
    tft.textTransparent(CUSTOM_GREEN);
    ledProfile[0] = placeholderFloat;
    timeToString(placeholderFloat, placeholderChar32, false, false);
    Serial.println(placeholderChar32);
    tft.textTransparent(CUSTOM_GREEN);
    tft.textWrite(placeholderChar32);

  } else {
    // draw a numPad and get on time
    tft.textWrite("Enter the minimum time the shutter");
    tft.textSetCursor(40, 180);
    tft.textWrite("should remain on (.1-25s):");
    tft.graphicsMode(); // For numPadReadFloat
    placeholderFloat = numPadReadFloat(true, 25.5, .1, 560, 70);
    if (placeholderFloat == 27.5) // Error condition returning max+2 (user exit)
      return;                     // Skip to end of loop
    tft.textMode();               // numPadReadFloat turns textMode off
    tft.textEnlarge(1);
    tft.textSetCursor(480, 180);
    tft.textTransparent(CUSTOM_GREEN);
    shutterProfile[0] = placeholderFloat * 10;
    timeToString(placeholderFloat, placeholderChar32);
    Serial.println(placeholderChar32);
    tft.textTransparent(CUSTOM_GREEN);
    tft.textWrite(placeholderChar32);

    // draw a numPad and get high/low
    tft.textTransparent(RA8875_BLACK);
    tft.textSetCursor(20, 220);
    tft.textWrite("Enter '0' to set shutter active");
    tft.textSetCursor(40, 260);
    tft.textWrite("voltage to ");
    tft.textWrite(shutterTriggerTypes[1], 4);
    tft.textSetCursor(40, 300);
    tft.textWrite("Enter '1' to set shutter active");
    tft.textSetCursor(40, 340);
    tft.textWrite("voltage to ");
    tft.textWrite(shutterTriggerTypes[0], 4);
    // draw a numPad and get on time
    tft.graphicsMode(); // For numPadReadFloat
    placeholderFloat = numPadReadFloat(true, 1, 0, 560, 70);
    if (placeholderFloat == 3) // Error condition returning max+2 (user exit)
      return;                  // Skip to end of loop
    tft.textMode();            // numPadReadFloat turns textMode off
    tft.textEnlarge(1);
    tft.textSetCursor(350, 340);
    tft.textTransparent(CUSTOM_GREEN);
    shutterProfile[1] = placeholderFloat;
    // timeToString(placeholderFloat, placeholderChar32);
    Serial.println(shutterProfile[1]);
    tft.textTransparent(CUSTOM_GREEN);
    tft.textWrite(shutterTriggerTypes[1 - shutterProfile[1]], 4);

    // Shutter on start delay
    tft.textTransparent(RA8875_BLACK);
    tft.textSetCursor(20, 380);
    tft.textWrite("Enter the time before a shutter");
    tft.textSetCursor(40, 420);
    tft.textWrite("should run (.1-25s):");
    // draw a numPad and get on time
    tft.graphicsMode(); // For numPadReadFloat
    placeholderFloat = numPadReadFloat(true, 25.5, .1, 560, 70);
    if (placeholderFloat == 27.5) // Error condition returning max+2 (user exit)
      return;                     // Skip to end of loop
    tft.textMode();               // numPadReadFloat turns textMode off
    tft.textEnlarge(1);
    tft.textSetCursor(360, 420);
    tft.textTransparent(CUSTOM_GREEN);
    shutterProfile[2] = placeholderFloat * 10;
    timeToString(placeholderFloat, placeholderChar32);
    Serial.println(placeholderChar32);
    tft.textTransparent(CUSTOM_GREEN);
    tft.textWrite(placeholderChar32);
  }
  tft.graphicsMode();
  // All settings selected; Write them to EEPROM
  if (profType == 5)
    for (unsigned char i = 0; i < 4; i++)
      writeProfileName(i, profileNumber, ledProfileName);
  else
    writeProfileName(profType, profileNumber, ledProfileName);

  if (profType == 4)
    writeProfile(profType, profileNumber, shutterProfile);
  else if (profType == 5)
    for (unsigned char i = 0; i < 4; i++)
      writeProfile(i, profileNumber, ledProfile);
  else
    writeProfile(profType, profileNumber, ledProfile);
}

void profilesContent() {
  char title[10];
  tft.textMode();
  tft.textSetCursor(20, 70);
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textWrite("Choose a profile type to begin:");
  unsigned char n = 0;

  // --> Full Scan
  buttons[2].width = 400;
  buttons[2].height = 50;
  buttons[2].x = 20;
  buttons[2].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[2].setText("All Columns");
  buttons[2].t = 2;
  buttons[2].action = 20; // Toggle mode is action 7
  buttons[2].drawBtn();
  // --> End full scan
  n++;
  // --> Spiral Down
  buttons[3].width = 400;
  buttons[3].height = 50;
  buttons[3].x = 20;
  buttons[3].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[3].setText("All Rings");
  buttons[3].t = 2;
  buttons[3].action = 21; // Toggle mode is action 7
  buttons[3].drawBtn();
  // --> End Spiral Down
  n++;
  // --> Single Ring
  buttons[4].width = 400;
  buttons[4].height = 50;
  buttons[4].x = 20;
  buttons[4].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[4].setText("Single Ring");
  buttons[4].t = 2;
  buttons[4].action = 22; // Toggle mode is action 7
  buttons[4].drawBtn();
  // --> End Single Ring
  n++;
  // --> Single Column
  buttons[5].width = 400;
  buttons[5].height = 50;
  buttons[5].x = 20;
  buttons[5].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[5].setText("Single Column");
  buttons[5].t = 2;
  buttons[5].action = 23; // Toggle mode is action 7
  buttons[5].drawBtn();
  // --> End Single Column
  n++;
  buttons[6].width = 400;
  buttons[6].height = 50;
  buttons[6].x = 20;
  buttons[6].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[6].setText("Shutters");
  buttons[6].t = 2;
  buttons[6].action = 24; // Toggle mode is action 7
  buttons[6].drawBtn();
  // --> End Single Column
  n = 0;
  buttons[7].width = 340;
  buttons[7].height = 50;
  buttons[7].x = 440;
  buttons[7].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[7].setText("All Patterns");
  buttons[7].t = 2;
  buttons[7].action = 25; // Toggle mode is action 7
  buttons[7].drawBtn();
  // --> End Single Column
  n++;
}

// KEYBOARD HEIGHT = 290px
void showKeyBoard(int xStart, int yStart) {
  // A number pad.
  // static unsigned char counter = 0;
  static const char xTextAdj = 23, yTextAdj = 0;
  // keys: ~ denotes location of caps lock/shift. Space denotes a space bar. #
  // is ignored (used to end rows smaller than 10 characters long). Asterists
  // (*) denote keys that change with shift.
  // static const char;
  // shiftKeys: Every other array position is a new key, with that position
  // being the non-shift key and the one after it being the shifted char.
  // (e.g.:
  // {".,"} will switch to key '.' turn to ',' when shifted.)
  // xTextAdj/yTextAdj: Centers the text in the key. Set in pixels.

  static unsigned char keyNum, shiftNum;

  keyNum = 0;
  shiftNum = 0;
  // Draw text box
  for (int yPos = 0; yPos < 5; yPos++) {
    for (int xPos = 0; xPos < 10; xPos++) {
      if (keys[keyNum] != '#' && keys[keyNum] != ' ' && keys[keyNum] != 0 &&
          keys[keyNum] != '*' && keys[keyNum] != '~') {
        tft.drawRect(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                         +adjust[yPos],
                     yStart + (keyHeight * yPos) + (keySpace * yPos), keyWidth,
                     keyHeight, RA8875_RED);
        tft.textMode();
        tft.textSetCursor(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                              +adjust[yPos] + xTextAdj,
                          yStart + (keyHeight * yPos) + (keySpace * yPos) +
                              yTextAdj);
        tft.textTransparent(RA8875_BLACK);
        tft.textEnlarge(2);
        if (keys[keyNum] == '>') { // Enter key, draw a continuous text arrow
          // Values are maually ajdusted, but should work for any key location
          tft.textSetCursor(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                                +adjust[yPos] + xTextAdj - 10,
                            yStart + (keyHeight * yPos) + (keySpace * yPos) +
                                yTextAdj - 3);
          tft.textWrite("-");
          tft.textSetCursor(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                                +adjust[yPos] + xTextAdj + 8,
                            yStart + (keyHeight * yPos) + (keySpace * yPos) +
                                yTextAdj - 3);
          tft.textWrite("-");
          tft.textSetCursor(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                                +adjust[yPos] + xTextAdj + 14,
                            yStart + (keyHeight * yPos) + (keySpace * yPos) +
                                yTextAdj - 3);
        }
        tft.textWrite(&keys[keyNum], 1);
        tft.graphicsMode();
      } else if (keys[keyNum] == ' ' ||
                 keys[keyNum] == '~') { // Space/shift bar
        // Place expanded rect
        tft.drawRect(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                         +adjust[yPos],
                     yStart + (keyHeight * yPos) + (keySpace * yPos),
                     (keyWidth * expansionRatio) +
                         (keySpace * ceil((float)expansionRatio / 2)),
                     keyHeight, RA8875_RED);
        tft.textMode();
        // Center text bases on expanded rect.
        // ((24 * 5) / 2)) is based on 5 characters of width 24 ("SPACE" at font
        // size 2)
        tft.textSetCursor(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                              ((((keyWidth * expansionRatio) +
                                 (keySpace * ceil((float)expansionRatio / 2))) /
                                2) -
                               ((24 * 5) / 2)) +
                              +adjust[yPos],
                          yStart + (keyHeight * yPos) + (keySpace * yPos) +
                              yTextAdj);
        tft.textTransparent(RA8875_BLACK);
        tft.textEnlarge(2);
        if (keys[keyNum] == ' ')
          tft.textWrite("SPACE");
        else
          tft.textWrite("SHIFT");
        tft.graphicsMode();
        xPos += expansionRatio - 1;     // Move forward 2 extra key spaces
      } else if (keys[keyNum] == '*') { // Shifted keys
        tft.drawRect(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                         +adjust[yPos],
                     yStart + (keyHeight * yPos) + (keySpace * yPos), keyWidth,
                     keyHeight, RA8875_RED);
        tft.textMode();
        tft.textSetCursor(xStart + (keyWidth * xPos) + (keySpace * xPos) +
                              (xTextAdj / 2) + adjust[yPos],
                          yStart + (keyHeight * yPos) + (keySpace * yPos) +
                              yTextAdj);
        tft.textTransparent(RA8875_BLACK);
        tft.textEnlarge(2);
        tft.textWrite(&shiftKeys[shiftNum * 2], 1);
        tft.textWrite(&shiftKeys[(shiftNum * 2) + 1], 1);
        tft.graphicsMode();
        shiftNum++;
      }
      keyNum++;
    }
  }
  while (tft.touched()) {    // Clear touch buffer
    tft.touchRead(&tx, &ty); // Remove previous touches
    delay(50);
  }
}

char readKeyBoard(int xStart, int yStart, int tx, int ty) {
  static bool shift, capsLock = false;
  // Values must be kept through multiple calls
  static char toReturn;
  static unsigned char keyNum, shiftNum;
  static bool skipX = false;

  toReturn = '!';
  turnShiftOff = true;
  keyNum = 0;
  shiftNum = 0;
  // Draw text box
  for (int yPos = 0; yPos < 5; yPos++) {
    for (int xPos = 0; xPos < 10; xPos++) {
      if (keys[keyNum] == ' ' ||
          keys[keyNum] ==
              '~') { // space/shift bar are larger; test them differently
        if (tx >
                xStart + (keyWidth * xPos) + (keySpace * xPos) + adjust[yPos] &&
            tx <= xStart + (keyWidth * xPos) + (keySpace * xPos) +
                      adjust[yPos] + (keyWidth * expansionRatio) +
                      (keySpace * ceil((float)expansionRatio / 2))) {
          skipX = true; // X should be skipped, but xPos is modified first:
        }
        xPos += expansionRatio - 1; // Happens regardless of above if statement
        if (skipX)
          goto checkY; // Goto is used to skip following if statement:
      } else if (tx > xStart + (keyWidth * xPos) + (keySpace * xPos) +
                          adjust[yPos] &&
                 tx <= xStart + (keyWidth * xPos) + (keySpace * xPos) +
                           adjust[yPos] + keyWidth) {
      checkY:
        skipX = false; // Reset variable
        if (ty > yStart + (keyHeight * yPos) + (keySpace * yPos) &&
            ty <= yStart + (keyHeight * yPos) + (keySpace * yPos) + keyHeight) {
          if (keys[keyNum] != '#' && keys[keyNum] != 0 && keys[keyNum] != '*' &&
              keys[keyNum] != '~') {
            // Check if letters should be in capital case (or for plain enter
            // sign)
            if (shift || capsLock || keys[keyNum] - '0' < 10 ||
                keys[keyNum] == '<')
              toReturn = keys[keyNum]; // Return capital (normal) char
            else
              toReturn =
                  keys[keyNum] + 32; // Return lowercase (different number) char

            if (keys[keyNum] == '>')
              toReturn = '>';

          } else if (keys[keyNum] == '~') { // SHIFT
            // Shift key manages both shift and caps
            if (shift && !capsLock) { // Shift is on, turn caps on.
              capsLock = true;
            } else if (capsLock) { // caps is on, turn off both shift and caps
              shift = false;
              capsLock = false;
            } else { // Turn shift on, caps left off
              shift = true;
              turnShiftOff = false;
            }
            toReturn = '~';
            setShiftState(5, tft.height() - 290 - 10, shift, capsLock);
          } else if (keys[keyNum] == '*') { // Shifted key
            if (shift)
              toReturn = shiftKeys[(shiftNum * 2) + 1];
            else
              toReturn = shiftKeys[shiftNum * 2];
            // shiftNum++;
          } // Shifted key
        }   // Y CHECKER
      }     // XCHECKER
      if (keys[keyNum] == '*')
        shiftNum++;
      keyNum++;
    } // X LOOP
  }   // Y LOOP

  if (shift && turnShiftOff &&
      toReturn != '!') { // If shift is on but was not just set on
    shift = false;       // Turn shift off
    setShiftState(5, tft.height() - 290 - 10, shift, capsLock);
  }

  // Serial.print("Returning: ");
  // Serial.println(toReturn);

  return toReturn; // If all else fails, an error will be sent.
}

void updateKeyBoard(int xStart, int yStart, unsigned char place, char *c) {
  if (*c != '<') { // Not backspace
    tft.textMode();
    tft.textSetCursor(xStart + 24 * place, yStart);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite(c, 1);
    tft.graphicsMode();
  } else // Backspace was pressed
    tft.fillRect(xStart + 24 * (place + 1), yStart, 24, 42, RA8875_WHITE);
  Serial.println(c);
}

void setShiftState(int x, int y, bool shift, bool capsLock) {

  if (!shift && !capsLock) {
    tft.fillRect(x + SHIFT_POS_X, y + SHIFT_POS_Y,
                 (keyWidth * expansionRatio) +
                     (keySpace * (expansionRatio - 1)),
                 keyHeight, RA8875_WHITE);
    tft.drawRect(x + SHIFT_POS_X, y + SHIFT_POS_Y,
                 (keyWidth * expansionRatio) +
                     (keySpace * (expansionRatio - 1)),
                 keyHeight, RA8875_RED);
    tft.textMode();
    // Center text bases on expanded rect.
    // Based on 5 characters of width 24 ("SPACE" at font size 2)
    tft.textSetCursor(x + SHIFT_POS_X + ((24 * 5) / 2), y + SHIFT_POS_Y);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(2);
    tft.textWrite("SHIFT");
    tft.graphicsMode();
  } else if (shift && !capsLock)
    tft.drawRect(x + SHIFT_POS_X, y + SHIFT_POS_Y,
                 (keyWidth * expansionRatio) +
                     (keySpace * (expansionRatio - 1)),
                 keyHeight, RA8875_BLUE);
  else if (capsLock)
    tft.fillRect(x + SHIFT_POS_X, y + SHIFT_POS_Y + 45,
                 (keyWidth * expansionRatio) +
                     (keySpace * (expansionRatio - 1)),
                 keyHeight - 45, RA8875_BLUE);
}

void showNumPad(int xStart, int yStart) {
  // A number pad.
  unsigned char counter = 0;
  char nums[12] = {"123456789.0>"};
  tft.fillRect(xStart, yStart, 240, 400, RA8875_WHITE);
  tft.drawRect(xStart, yStart + 20, 220, 60, RA8875_RED);
  for (int yCount = 1; yCount < 5; yCount++) {
    for (int xCount = 0; xCount < 3; xCount++) {
      tft.drawRect(xStart + (60 * xCount) + (20 * xCount),
                   yStart + 20 + (60 * yCount) + (20 * yCount), 60, 60,
                   RA8875_RED);
      tft.textMode();
      tft.textSetCursor(xStart + (60 * xCount) + (20 * xCount) + 17,
                        yStart + 20 + (60 * yCount) + (20 * yCount));
      tft.textTransparent(RA8875_BLACK);
      tft.textEnlarge(2);
      tft.textWrite(&nums[counter], 1);
      tft.graphicsMode();
      counter++;
    }
  }
  while (tft.touched()) {    // Clear touch buffer
    tft.touchRead(&tx, &ty); // Remove previous touches
    delay(50);
  }
}

char readNumPad(int xStart, int yStart, int tx, int ty) {
  // Returns the integer pressed on a number pad.
  char nums[12] = {"123456789.0>"};
  for (int yCount = 1; yCount < 5; yCount++) {
    for (int xCount = 0; xCount < 3; xCount++) {
      if (tx >= xStart + (60 * xCount) + (20 * xCount) &&
          tx <= xStart + 60 + (60 * xCount) + (20 * xCount))
        if (ty >= yStart + 20 + (60 * yCount) + (20 * yCount) &&
            ty <= yStart + 20 + 60 + (60 * yCount) + (20 * yCount)) {
          // A touch was detected at button #(3 * y) + x
          return nums[((3 * (yCount - 1)) + xCount)];
        }
    }
  }
  return '!';
}

void updateNumPad(int xStart, int yStart, int place, char *ch) {
  // Writes a character or error to the number pad's number display.
  // Start text placment
  tft.textMode();
  tft.textSetCursor(xStart, yStart + 20);
  tft.textEnlarge(2);
  // Conditionally continue placement
  if (ch != &errorChar) {
    tft.textTransparent(RA8875_BLACK);
    tft.textSetCursor(xStart + (30 * place), yStart + 20);
    tft.textWrite(ch, 1);
    // tft.graphicsMode();
  } else {
    tft.textTransparent(RA8875_RED);
    Serial.println("error");
    if (place == 0)
      tft.textWrite("TOO LOW");
    if (place == 1)
      tft.textWrite("TOO HIGH");
    if (place == 2)
      tft.textWrite("error 2");
    if (place == 3)
      tft.textWrite("error 4");
  }
  tft.graphicsMode();
}

float numPadReadFloat(bool allowExit, float upperLimit, float lowerLimit, int x,
                      int y) {
  // Reads a full number out of the numPad
  // STEPS
  // Get limits and rules for data to be entered
  // Only check for touches on numpad
  // While numbers are being entered:
  //  - If character is decimal, ensure that place is set.
  //  - If number is too large while entering, flash "TOO HIGH"
  //      error for 1 second and then return
  // Loop ends when '>' is entered, even if number is zero

  // CODE:
  static char enteredChar; // Char entered on the numpad
  static unsigned char placesBeforeDec, placesAfterDec, enteredNum;
  static char place;
  static float numToReturn; // Float to be returned
  // static bool keepChecking;
  static char c[10];

  for (int i = 0; i < 10; i++)
    c[i] = 0;

  enteredChar = 0;
  enteredNum = 0;
  place = 0;
  numToReturn = upperLimit + 1; // Preset the return number to an impossible
                                // number so that the program can check if
  // anything was entered. This number also serves as the error condition
  // number.
  showNumPad(x, y);
  placesAfterDec = 1; // If more places are needed, they can be calculated
                      // similarly to placesBeforeDec.

  for (int i = 0; i < 3; i++)    // For three different places
    if (upperLimit < (10 ^ i)) { // If the number is less than 10^(place number)
      placesBeforeDec = i;       // i is the number of places.
      break;                     // Don't bother checking the rest
    }

  // keepChecking = true;
  while (true) { // While entry is incomplete
    if (filterTouch()) {
      // Screen was touched, act accordingly

      if (allowExit) { // If home or back button should be usable to leave the
                       // page
        if (DISPLAY_DIAGNOSTICS_MODE == 1) // Blue for escapable loop
          tft.fillCircle((uint16_t)(tx), (uint16_t)(ty), 4, RA8875_BLUE);
        // while typing
        if (buttons[0].checkTouch(tx, ty)) {
          return upperLimit + 2; // Error condition: user exit
        }                        // Home button

        else if (buttons[1].checkTouch(tx, ty)) {
          return upperLimit + 2;              // Error condition: user exit
        }                                     // Home button
      }                                       // END if(allowExit)
      else if (DISPLAY_DIAGNOSTICS_MODE == 1) // Cyan for inescapable loop
        tft.fillCircle((uint16_t)(tx), (uint16_t)(ty), 4, RA8875_CYAN);

      // Only check for touches on numpad
      // While numbers are being entered:
      //  - If character is decimal, ensure that place is set.
      //  - If number is too large while entering, flash "TOO HIGH"
      //      error for 1 second and then return
      // Loop ends when '>' is entered, even if number is zero

      // Set any touch pad touches to enteredChar:
      enteredChar = (readNumPad(x, y, tx, ty));
      if (enteredChar == '!')   // If touch was not on a numPad button
        continue;               // Skip to the end of the while loop
      if (enteredChar == '>') { // User is done entering number

        if (numToReturn < lowerLimit) { // Number too low
          tft.fillRect(x + 1, y + 21, 218, 58, RA8875_WHITE);
          updateNumPad(x, y, 0, &errorChar);
          while (millis() - lastTouchTime <= 2000) // Wait two seconds
            tft.touchRead(&tx, &ty); // Clear touches in buffer during this time
          tft.fillRect(x + 1, y + 21, 218, 58,
                       RA8875_WHITE); // Re-write the number
          tft.textMode();
          tft.textSetCursor(x, y + 20);
          tft.textTransparent(RA8875_BLACK);
          tft.textEnlarge(2);
          tft.textWrite(c, 10);
          tft.graphicsMode();
          continue; // Dont leave
        }

        // If the user tries to leave before setting the number (e.g. to
        // cancel
        // changing a value), the function will return the maximum allowable
        // number + 1 as a fault condition. This must be handled by the
        // calling fuction.
        tft.fillRect(x, y, 220, 400, RA8875_WHITE); // Hide the numpad again
        return numToReturn;
      }                                       // END '>'
      else if (numToReturn == upperLimit + 1) // If the number has not been set
        numToReturn = 0; // Start the number at zero to be set below
      if (enteredChar == '.' &&
          place >= 0) { // Decimal point, which was not already pressed
        place = -1; // set place to indicate that the decimal point was written

      } else { // Numpad was touched at a number
        enteredNum = enteredChar - '0';
        if ((place != -1)
                ? ((numToReturn * 10) + enteredNum <= upperLimit)
                : (numToReturn + (((float)enteredNum) * 0.1) <=
                   upperLimit)) {      // If the number will not go over max
          if (place != -1) {           // If the number is not a decimal
            numToReturn *= 10;         // Shift all digits over by one place
            numToReturn += enteredNum; // Add the new digit
          } else {
            numToReturn += ((float)enteredNum) * 0.1; // Add the new decimal
            place--;
          }
          tft.fillRect(x + 1, y + 21, 218, 58, RA8875_WHITE);
          tft.textMode();
          tft.textSetCursor(x, y + 20);
          tft.textTransparent(RA8875_BLACK);
          tft.textEnlarge(2);
          dtostrf(numToReturn, 1, placesAfterDec, c);
          // Clear all of the digits including and after the decimal point:
          if (place >= 0) // if no decimal has been placed yet
            for (int i = 0; i < 10; i++)
              if (c[i] == '.')
                for (int j = i; j < 10; j++)
                  c[j] = 0;

          tft.textWrite(c, 10);
          tft.graphicsMode();
        }      // END If the number will not go over max
        else { // Number too large; throw error
          tft.fillRect(x + 1, y + 21, 218, 58, RA8875_WHITE);
          updateNumPad(x, y, 1, &errorChar);
          while (millis() - lastTouchTime <= 2000) // Wait two seconds
            tft.touchRead(&tx, &ty); // Clear touches in buffer during this time
          tft.fillRect(x + 1, y + 21, 218, 58,
                       RA8875_WHITE); // Re-write the number
          tft.textMode();
          tft.textSetCursor(x, y + 20);
          tft.textTransparent(RA8875_BLACK);
          tft.textEnlarge(2);
          tft.textWrite(c, 10);
          tft.graphicsMode();
        }
      } // END numpad number selected

    } // touch filter/checker
  }   // while(keepChecking)

  tft.fillRect(x, y, 220, 400, RA8875_WHITE); // Hide the numpad again
  // Serial.println("Left while loop");
} // function

void disableAllLEDs(char *leds = ' ') { // dont use char
  for (int i = 0; i < 192; i++)
    ledArray[i].trigger(0, 0);
}

void selfTest() {
  // tft.fillRect(0, 0, tft.width(), tft.height(), RA8875_BLACK);
  // tft.textMode();
  // tft.textTransparent(RA8875_WHITE);
  // tft.textEnlarge(3);
  // tft.textSetCursor(0, 150);
  // tft.textWrite(
  //     "Running self test... this will take approximately 30 seconds.");
  // tft.graphicsMode();
  //
  // static int baselineLightSense;
  // baselineLightSense = readLightSensor();
  // for (unsigned char channel = 0; channel < 3; channel++;) // For each
  // channel
  //   for (int ring = 0; ring < 8; ring++)                   // For each ring
  //     for (int i = ((channel - 1) * 64) + ring; i < (channel * 64);
  //          i += 8 * skip) { // Loop through all LEDs in ring
  //       if (USE_CUSTOM_ARRAY(channel - 1) == 0b1 &&
  //           bitRead(EEPROM.read(USABLE_IR_ARRAY +
  //                               ((i - ((channel - 1) * 64)) / 8) +
  //                               (channel - 1) * 8),
  //                   i % 8) == 0b1)
  //         continue; // skip this LED because it cannot be used
  //       ledArray[i].trigger(1, 0);
  //       // WAIT FOR LIGHT SENSOR TO SHOW LIGHT, MAX TIME 300ms
  //       while ()
  //         ledArray[i].trigger(0, 0);
  //       delay(10); // Buffer delay
  //       counter++; // Used to keep track of precentage complete
  //     }
}

void assignCHNamesDisplayFile() {
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
}

void runPattern(unsigned char type) {
  // for (int i = 0; i < CHANNEL_NAME_MAX_CHARACTERS; i++) {
  //   chNames[0][i] = EEPROM.read(CHANNEL_NAME_1_ADDR + i);
  //   chNames[1][i] = EEPROM.read(CHANNEL_NAME_2_ADDR + i);
  //   chNames[2][i] = EEPROM.read(CHANNEL_NAME_3_ADDR + i);
  // }
  Serial.println(chNames[0]);
  // STEPS (marked with --> in program)
  // --> Open start page and estimated time (DONE)
  // --> Try to get a profile choice
  // --> If no profile chosen, get data
  // --> Try to get a shutter profile
  // --> If none chosen, get data
  // --> If needed, get the ring or column number to use
  // --> Get channel #
  // --> Start when start button pressed
  // --> Place/leave cancel button on screen
  // !!!!!
  // --> Set up global vars dictation where to place a progress bar when
  // running
  // --- a program
  // !!!!!
  // --> When done, display end time
  // --> Allow user to continue doing scans while changing channel
  // BEGIN PROGRAM:

  static char name[32]; // placeholder

  // Moved to headers
  // static char ledProfileName[32];
  // static char shutterProfileName[32];
  // // char name[32]; // placeholder
  // static bool listLedProfiles, listShutterProfiles, listChannel,
  //     readingTouch; // Impacts what touch in these area does
  // static unsigned char ledProfile[3], channel,
  //     shutterProfile[2]; // used to store LED profile values

  for (int i = 0; i < 32; i++) {
    name[i] = 0;
    ledProfileName[i] = 0;
    shutterProfileName[i] = 0;
  }
  listLedProfiles = false;
  listShutterProfiles = false;
  listChannel = false;
  listShutterTrigger = false;
  readingTouch = true; // Leaves the touch sensing while loop. Likely unsused.
  patternChannel = 0;
  ringColNum = 1;
  for (int i = 0; i < 3; i++) {
    ledProfile[i] = 0;
    if (i != 2)
      shutterProfile[i] = 0;
  }

  // --> Open start page and estimated time
  drawPatternLaunchPage(type);

  // --> Try to get a profile choice
  // --> If no profile chosen, get data
  // --> Try to get a shutter profile
  // --> If none chosen, get data
  // --> If needed, get the ring or column number to use
  // --> Get channel #

  while (readingTouch) { // Constantly run
                         // Read and filter incomming touches
    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        return;
      } // Home button
      // other functions for buttons here
      // Check all text boxes/titles to see if being updated
      // Check dropdowns to see if they need to be used
      // if needed, check numpad
      // Check start button. if pressed, enter a new void and it's own
      // while
      // loop.
      unsigned char n = 0;
      // CHECK DROPDOWNS
      if (listLedProfiles) {
        if (tx > 20 && tx <= 20 + 512)
          if (ty > 120 + 35 && ty <= 120 + 35 + 45 * 3) {
            // A profile was selected; find out which and save it
            for (int y1 = 0; y1 < 3; y1++) { // Display for loop
              if (ty > 120 + 35 + (y1 * 45) &&
                  ty <= 120 + 35 + (y1 * 45) + 45) {
                listLedProfiles = false;
                readProfileName(type, y1 + 1, ledProfileName);

                // Get info based on selection
                readProfile(type, y1 + 1, ledProfile);

                // Push new and old info to display
                drawPatternLaunchPage(type);
                updatePatternLaunchPage(type);
              }
            }
            continue; // Skip to end of while loop
          }
      } // if (listLedProfiles)
      n++;
      if (listChannel) {
        if (tx > 20 && tx <= 20 + 192)
          if (ty > 120 + 35 + (n * 80) &&
              ty <= 120 + 35 + (3 * 45) + (n * 80)) {
            // A profile was selected; find out which and save it
            for (int y1 = 0; y1 < 3; y1++) { // Display for loop
              if (ty > 120 + 35 + (y1 * 45) + (n * 80) &&
                  ty <= 120 + 35 + (y1 * 45) + 45 + (n * 80)) {
                listChannel = false;
                patternChannel = y1;

                // Push new and old info to display
                drawPatternLaunchPage(type);
                updatePatternLaunchPage(type);
              }
            }
            continue; // Skip to end of while loop
          }
      } // if (listChannel)
      if (listShutterProfiles) {
        static bool skipWhileLoop;
        if (tx > 20 + 200 && tx <= 20 + 200 + 512) {
          for (int y1 = 0; y1 < 8; y1++) { // Display for loop
            if (ty > 120 + (y1 * 45) && ty <= 120 + (y1 * 45) + 45) {
              listShutterProfiles = false;
              readProfileName(4, y1 + 1, shutterProfileName);
              readProfile(4, y1 + 1, shutterProfile);

              // Push new and old info to display
              drawPatternLaunchPage(type);
              updatePatternLaunchPage(type);
              skipWhileLoop = true; // continue; // Skip to end of while loop
            }                       // Y cehcker
          }                         // For loop
          if (skipWhileLoop) {
            skipWhileLoop = false;
            continue; // Skip to end of while loop
          }           // skipWhileLoop
        }             // tx checker
      }               // if (listShutterProfiles)

      if (listShutterTrigger) {
        static bool skipWhileLoop;
        if (tx > 20 + 200 && tx <= 20 + 200 + 192) {
          for (int y1 = 0; y1 < 8; y1++) { // Display for loop
            if (ty > 120 + 35 + (80 * 3) + (y1 * 45) &&
                ty <= 120 + 35 + (80 * 3) + (y1 * 45) + 45) {
              listShutterTrigger = false;
              // readProfileName(4, y1 + 1, shutterProfileName);
              // readProfile(4, y1 + 1, shutterProfile);
              shutterProfile[1] = 1 - y1;
              // Push new and old info to display
              drawPatternLaunchPage(type);
              updatePatternLaunchPage(type);
              skipWhileLoop = true; // continue; // Skip to end of while loop
            }                       // Y cehcker
          }                         // For loop
          if (skipWhileLoop) {
            skipWhileLoop = false;
            continue; // Skip to end of while loop
          }           // skipWhileLoop
        }             // tx checker
      }               // if (listShutterProfiles)

      // ROW/COL NUMBER (ringColNum)
      if (type == 2 || type == 3) // Must be correct pattern type
        if (tx > 20 + 395 && tx <= 20 + 395 + 140) {
          if (ty > 80 && ty <= 80 + 80) {
            // STEPS:
            // Highlight correct box to show where entry is occuring
            // Check for numpad touches by getting float numPadReadFloat();
            // Turn float into byte for storage.

            // CODE:
            // Highlight correct box to show where entry is occuring
            tft.drawRect(20 + 395 + 58, 80 + 35, 24, 40, RA8875_BLUE);
            tft.drawRect(21 + 395 + 58, 81 + 35, 22, 38, RA8875_BLUE);
            // Check for numpad touches by getting float numPadReadFloat();
            placeholderFloat = numPadReadFloat(1, 8, 0, tft.width() - 240, 70);

            // If numPadReadFloat did not return error value of max + 1
            if (placeholderFloat != 8 + 1)
              // Turn float into byte and store it.
              ringColNum = (unsigned char)(placeholderFloat);

            placeholderFloat = -1;

            // Reset display:
            drawPatternLaunchPage(type);
            updatePatternLaunchPage(type);

            continue; // Skip to end of while loop
          }
        }

      // START BUTTON
      if (tx > 20 + 395 && tx <= 20 + 395 + 140) {
        if (type == 2 || type == 3) // These have a lower start button
          if (ty > 80 + 80 && ty <= 80 + 80 + 40)
            goto checkXcoord; // Goto is used to skip the normal
                              // y-checker:
        if (ty > 80 && ty <= 80 + 40 && type < 2) {
        checkXcoord:

          // Show stop button
          tft.fillRect(STOPBUTTON_X, STOPBUTTON_Y, STOPBUTTON_W, STOPBUTTON_H,
                       RA8875_RED);
          tft.textMode();
          tft.textTransparent(RA8875_WHITE);
          tft.textEnlarge(3);
          tft.textSetCursor(STOPBUTTON_X + 8, STOPBUTTON_Y);
          tft.textWrite("STOP");
          tft.graphicsMode();

          patternStartTime = millis(); // Set up timer

          if (type == 0) {
            colScan(ledProfile[0], ledProfile[1], ledProfile[2],
                    patternChannel + 1, shutterProfile[0],
                    (shutterProfile[1] == 0) ? true : false, shutterProfile[2]);
          }
          if (type == 1) {
            ringScan(ledProfile[0], ledProfile[1], ledProfile[2],
                     patternChannel + 1, shutterProfile[0],
                     (shutterProfile[1] == 0) ? true : false,
                     shutterProfile[2]);
          }
          if (type == 2) {
            singleCol(ledProfile[0], ledProfile[1], ledProfile[2],
                      patternChannel + 1, ringColNum, shutterProfile[0],
                      (shutterProfile[1] == 0) ? true : false,
                      shutterProfile[2]);
          }
          if (type == 3) {
            singleRing(ledProfile[0], ledProfile[1], ledProfile[2],
                       patternChannel + 1, ringColNum, shutterProfile[0],
                       (shutterProfile[1] == 0) ? true : false,
                       shutterProfile[2]);
          }

          // Read note below, this if statement should never be activated
          // under normal operation!
          if (type == 5) {

            /* IMPORTANT NOTE, READ BEFOR MODYFYING THESE IF STATEMENTS:
            This program would not work on our Arduino without including
            this additional if statement containing a repeat of the lines
            calling different patterns. The Arduino would consistently
            crash
            due to what seemed to be a complete loss of free SRAM (free
            SRAM
            can be seen at the top left of the display with Diagnostics
            Mode
            on). The error would sometimes bring the free RAM from ~5kb to
            ~-1kb (usually exactly negative 1060 bytes)*/

            // colScan(ledProfile[0], ledProfile[1], ledProfile[2], 1);
            //
            // ringScan(ledProfile[0], ledProfile[1], ledProfile[2], 1);
            // // colScan(ledProfile[0], ledProfile[1], ledProfile[2], 1);
            //
            // singleCol(ledProfile[0], ledProfile[1], ledProfile[2], 1, 1);
            // // colScan(ledProfile[0], ledProfile[1], ledProfile[2], 1);
            //
            // singleRing(ledProfile[0], ledProfile[1], ledProfile[2], 1, 1);
            // // colScan(ledProfile[0], ledProfile[1], ledProfile[2], 1);
          }

          // Indicate finished, allow time to read final values
          tft.fillRect(STOPBUTTON_X, STOPBUTTON_Y, STOPBUTTON_W, STOPBUTTON_H,
                       RA8875_GREEN);
          patternStartTime = millis(); // Reuse variable for delay
          while (millis() - patternStartTime <= 2000) // Wait two seconds
            tft.touchRead(&tx, &ty); // Clear touches in buffer during this time

          // Set up display again
          drawPatternLaunchPage(type);
          updatePatternLaunchPage(type);
        }
      }

      // COLUMN-BASED OPERATIONS:

      // unsigned char n;
      n = 0; // Drops y coord checker IF statements by one box per n++;

      if (tx > 20 && tx <= 20 + 192) { // FIRST COLUMN
        if (!listLedProfiles && ty > 120 + 35 &&
            ty <= 120 + 35 + 45) { // PROFILE
          listLedProfiles = true;  // List is showing now
          listChannel = false;     // Hide other lists
          listShutterProfiles = false;
          listShutterTrigger = false;
          tft.fillRect(20, 120 + 35, 512, 3 * 45, RA8875_WHITE);
          for (int y1 = 0; y1 < 3; y1++) { // PLACE BOXES
            tft.drawRect(20, 120 + 35 + (y1 * 45), 512, 45, RA8875_RED);
            tft.textMode();
            tft.textSetCursor(20, 120 + 35 + (y1 * 45));
            tft.textTransparent(RA8875_BLACK);
            readProfileName(type, y1 + 1, name);
            tft.textEnlarge(1);
            tft.textWrite(name, 32);
            tft.graphicsMode();
          }         // END PLACE BOXES
          continue; // Skip to end of while loop
        }           // END PROFILE
        n++;
        // List channels
        if (!listChannel && ty > 120 + 35 + (n * 80) &&
            ty <= 120 + 35 + 45 + (n * 80)) {
          listChannel = true;
          tft.fillRect(20, 120 + 35 + (n * 80), 192, 3 * 45, RA8875_WHITE);
          for (int y1 = 0; y1 < 3; y1++) { // PLACE BOXES
            tft.drawRect(20, 120 + 35 + (n * 80) + (y1 * 45), 192, 45,
                         RA8875_RED);
            tft.textMode();
            tft.textSetCursor(20, 120 + 35 + (y1 * 45) + (n * 80));
            tft.textTransparent(RA8875_BLACK);
            tft.textWrite(chNames[y1]);
            Serial.println(chNames[0]);
            tft.graphicsMode();
          }         // END PLACE BOXES
          continue; // Skip to end of while loop
        }           // END CHANNELS
        n++;
        // ON-TIME CHANGER
        if (ty > 120 + 35 + (n * 80) && ty <= 120 + 35 + 45 + (n * 80)) {
          // STEPS:
          // Highlight correct box to show where entry is occuring
          // Check for numpad touches by getting float numPadReadFloat();
          // Turn float into byte for storage.

          // CODE:
          // Highlight correct box to show where entry is occuring
          tft.drawRect(20, 120 + 35 + (80 * n), 192, 45, RA8875_BLUE);
          tft.drawRect(21, 120 + 35 + (80 * n) + 1, 190, 43, RA8875_BLUE);
          // Check for numpad touches by getting float numPadReadFloat();
          placeholderFloat = numPadReadFloat(0, 25.5, 0, tft.width() - 240, 70);

          // If numPadReadFloat did not return error value of max + 1
          if (placeholderFloat != 25.5 + 1)
            // Turn float into byte and store it.
            ledProfile[1] = (unsigned char)(placeholderFloat * 10);

          placeholderFloat = -1;

          // Reset display:
          drawPatternLaunchPage(type);
          updatePatternLaunchPage(type);

          continue; // Skip to end of while loop
        }           // END ON-TIME CHANGER

        n++;
        // OFF-TIME CHANGER
        if (ty > 120 + 35 + (n * 80) && ty <= 120 + 35 + 45 + (n * 80)) {
          // Highlight correct box to show where entry is occuring
          tft.drawRect(20, 120 + 35 + (80 * n), 192, 45, RA8875_BLUE);
          tft.drawRect(21, 120 + 35 + (80 * n) + 1, 190, 43, RA8875_BLUE);

          // Check for numpad touches by getting float numPadReadFloat();
          placeholderFloat = numPadReadFloat(0, 25.5, 0, tft.width() - 240, 70);

          // If numPadReadFloat did not return error value of max + 1
          if (placeholderFloat != 25.5 + 1)
            // Turn float into byte and store it.
            ledProfile[2] = (unsigned char)(placeholderFloat * 10);

          placeholderFloat = -1;

          // Reset display:
          drawPatternLaunchPage(type);
          updatePatternLaunchPage(type);

          continue; // Skip to end of while loop
        }           // END OFF-TIME CHANGER
      }             // END FIRST COLUMN

      else if (tx > 20 + 200 && tx <= 20 + 200 + 192) { // SECOND COLUMN
        n = 0;
        n++;
        // INCREMENT CHANGER
        if (ty > 45 + 80 && ty <= 45 + 45 + 80) {
          // Highlight correct box to show where entry is occuring
          tft.drawRect(220, 35 + 80, 192, 45, RA8875_BLUE);
          tft.drawRect(221, 35 + 80 + 1, 190, 43, RA8875_BLUE);

          // Check for numpad touches by getting float numPadReadFloat();
          placeholderFloat = numPadReadFloat(
              1, (type == 0 || type == 1) ? 64 : 8, 1, tft.width() - 240, 70);

          // If numPadReadFloat did not return error value of max + 1
          if (placeholderFloat != ((type == 0 || type == 1) ? 64 : 8) + 1)
            // Turn float into byte and store it.
            ledProfile[0] = (unsigned char)(placeholderFloat);

          placeholderFloat = -1;

          // Reset display:
          drawPatternLaunchPage(type);
          updatePatternLaunchPage(type);

          continue; // Skip to end of while loop
        }           // END INCREMENT CHANGER
        n++;
        // SHUTTER-ON-TIME CHANGER
        if (ty > 120 + 35 + (80 * n) && ty <= 45 + 120 + 35 + (80 * n)) {
          // Highlight correct box to show where entry is occuring
          tft.drawRect(220, 120 + 35 + (80 * n), 192, 45, RA8875_BLUE);
          tft.drawRect(221, 120 + 35 + (80 * n) + 1, 190, 43, RA8875_BLUE);

          // Check for numpad touches by getting float numPadReadFloat();
          placeholderFloat = numPadReadFloat(0, 25.5, 0, tft.width() - 240, 70);

          // If numPadReadFloat did not return error value of max + 1
          if (placeholderFloat != 25.5 + 1)
            // Turn float into byte and store it.
            shutterProfile[0] = (unsigned char)(placeholderFloat * 10);

          placeholderFloat = -1;

          // Reset display:
          drawPatternLaunchPage(type);
          updatePatternLaunchPage(type);

          continue; // Skip to end of while loop
        }           // END SHUTTER-ON-TIME CHANGER
        n++;
        // SHUTTER-TRIGGER-TYPE LISTER
        if (!listShutterTrigger && ty > 120 + 35 + (80 * n) &&
            ty <= 45 + 120 + 35 + (80 * n)) {
          listShutterTrigger = true; // List is showing now
          listChannel = false;       // Hide other lists
          listLedProfiles = false;
          listShutterProfiles = false;
          tft.fillRect(220, 120 + 35 + (80 * n), 512, 2 * 45, RA8875_WHITE);
          tft.textMode();
          tft.textEnlarge(1);
          for (int y1 = 0; y1 < 2; y1++) { // PLACE BOXES
            tft.textSetCursor(220, 120 + 35 + (80 * n) + (y1 * 45));
            tft.drawRect(220, 120 + 35 + (80 * n) + (y1 * 45), 192, 45,
                         RA8875_RED);
            tft.textTransparent(RA8875_BLACK);
            tft.textWrite(shutterTriggerTypes[y1], 4);
          } // END PLACE BOXES
          tft.graphicsMode();

          continue; // Skip to end of while loop
        }           // END SHUTTER-TRIGGER-TYPE LISTER

        if (!listShutterProfiles && ty > 120 + 35 + 80 &&
            ty <= 120 + 35 + 80 + 45) { // SHUTTER PROFILE
          listShutterProfiles = true;   // List is showing now
          listChannel = false;          // Hide other lists
          listLedProfiles = false;
          listShutterTrigger = false;

          tft.fillRect(20 + 200, 120, 512, 8 * 45, RA8875_WHITE);
          for (int y1 = 0; y1 < 8; y1++) { // PLACE BOXES
            tft.drawRect(20 + 200, 120 + (y1 * 45), 512, 45, RA8875_RED);
            tft.textMode();
            tft.textSetCursor(20 + 200, 120 + (y1 * 45));
            tft.textTransparent(RA8875_BLACK);
            tft.textEnlarge(1);
            readProfileName(4, y1 + 1, name);
            tft.textWrite(name, 32);
            tft.graphicsMode();
          } // END PLACE BOXES
        }   // END SHUTTER PROFILE
      }     // END SECOND COLUMN
      //
      // // First box in second column is placced oddly
      // tft.drawRect(startPx + 200, 80 + 35, 192, 45, RA8875_RED);
      //
      // // Second column of boxes, except first
      // for (n = 1; n < 4; n++)
      //   tft.drawRect(startPx + 200, 120 + 35 + (80 * n), 192, 45,
      //   RA8875_RED);

    } // END FILTER TOUCH
  }   // END READING TOUCH LOOP
}

#define ESTIMATED_TIME_HEIGHT 40

void updatePatternLaunchPage(unsigned char type) {
  static char name[32];
  tft.textMode();
  tft.textSetCursor(20, 120 + 35);
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textWrite(ledProfileName, 12);

  tft.textTransparent(RA8875_BLACK);
  tft.textSetCursor(20, 120 + 35 + (2 * 80));
  timeToString(((float)ledProfile[1]) / 10, name, true);
  tft.textWrite(name, 5); // ON TIME
  timeToString(((float)ledProfile[2]) / 10, name, true);
  tft.textSetCursor(20, 120 + 35 + (3 * 80));
  tft.textWrite(name, 5); // OFF TIME
  timeToString(ledProfile[0], name, false, false);
  tft.textSetCursor(20 + 200, 80 + 35);
  tft.textWrite(name, 5); // INCREMENT

  // ETA
  unsigned char ledCount = 64;  // Number of LEDs that will be used
  if (type == 0 || type == 1) { // Scan of rings or columns
    if (USE_CUSTOM_ARRAY(patternChannel) == 0b1) {
      ledCount = 0;                  // Special array of LEDs that are usable
      for (int i = 0; i < 64; i++) { // For each LED
        if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel)*8),
                    i % 8) == 0b0) { // If LED is usable
          ledCount++;                // Add to ammount of LEDs
          // Serial.println(ledCount);
        }
      }
    }
    timeToString(
        (float)(ledCount / ledProfile[0]) *
            (float)(((float)ledProfile[1] / 10) + ((float)ledProfile[2]) / 10),
        name, true);
  } else { // Single ring or column
    ledCount = 8;
    if (USE_CUSTOM_ARRAY(patternChannel) == 0b1) {
      ledCount = 0; // Special array of LEDs that are usable
      for (int i = 8 * ((ringColNum - 1)); i < 8 * (ringColNum);
           i++) { // For each LED
        if (bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel)*8),
                    i % 8) == 0b0) { // If LED is usable
          ledCount++;                // Add to ammount of LEDs
        }
      }
    }
    timeToString(
        (float)(ledCount / ledProfile[0]) *
            (float)(((float)ledProfile[1] / 10) + ((float)ledProfile[2]) / 10),
        name, true);
    // if (ledCount == 0)
    //   name = "no LEDs";
  }

  tft.textTransparent(RA8875_BLUE);
  tft.textSetCursor(20 + 395, tft.height() - ESTIMATED_TIME_HEIGHT);
  tft.textWrite(name, 7); // ETA

  // color
  tft.textTransparent(RA8875_BLACK);
  tft.textSetCursor(20, 120 + 35 + 80);
  tft.textWrite(chNames[patternChannel], 9); // Color

  // Shutter
  tft.textSetCursor(20 + 200, 120 + 35 + 80);
  tft.textWrite(shutterProfileName, 12); // Shutter
  tft.textSetCursor(20 + 200, 120 + 35 + (2 * 80));
  timeToString(((float)shutterProfile[0]) / 10, name, true);
  tft.textWrite(name, 5); // ON TIME
  tft.textSetCursor(20 + 200, 120 + 35 + (3 * 80));
  // TRIGGER WITH
  tft.textWrite(shutterProfile[1] ? (shutterTriggerTypes[0])
                                  : (shutterTriggerTypes[1]),
                4);

  // RING/COL NUMBER
  if (type == 2 || type == 3) {
    tft.textSetCursor(20 + 395 + 58, 80 + 35);
    timeToString(ringColNum, name, false, false);
    tft.textWrite(name, 1);
  }

  tft.graphicsMode();
  // Set the shutter to the new off level
  setShutter(4, 0, (shutterProfile[1] == 0) ? true : false, true);
}

void drawPatternLaunchPage(unsigned char type) {
  static unsigned char startPx, n;
  startPx = 20;
  tft.fillRect(0, 70, tft.width(), tft.height() - 70, RA8875_WHITE);
  tft.textMode();
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textSetCursor(20, 80);
  tft.textWrite("LEDs");

  tft.textEnlarge(1);

  n = 0;

  tft.textSetCursor(20, 120 + (80 * n));
  tft.textWrite("Profile:");
  tft.textSetCursor(startPx, 120 + 35 + (80 * n));
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n++;

  tft.textSetCursor(startPx, 120 + (80 * n));
  tft.textTransparent(RA8875_RED);
  tft.textWrite("Color:");
  tft.textTransparent(RA8875_BLACK);
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n++;

  tft.textSetCursor(startPx, 120 + (80 * n));
  tft.textWrite("On Time:");
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n++;

  tft.textSetCursor(startPx, 120 + (80 * n));
  tft.textWrite("Off Time:");
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n = 0; // Rest count on new column

  tft.textSetCursor(startPx + 200, 80 + (80 * n));
  tft.textWrite("Increment:");
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n++;

  tft.textEnlarge(2);

  tft.textSetCursor(startPx + 200, 80 + (80 * n));
  tft.textWrite("Shutters");

  tft.textEnlarge(1);

  tft.textSetCursor(startPx + 200, 120 + (80 * n));
  tft.textWrite("Profile:");
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n++;

  tft.textSetCursor(startPx + 200, 120 + (80 * n));
  tft.textWrite("On Time:");
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  n++;

  tft.textSetCursor(startPx + 200, 120 + (80 * n));
  tft.textWrite("Trigger w/:");
#ifdef CHOOSE_HERE_SHOWN
  tft.textWrite(chooseHereText);
#endif

  tft.graphicsMode();

  // (192 pixel box length is 12 characters at font size 1)
  // First column of boxes
  for (n = 0; n < 4; n++)
    tft.drawRect(startPx, 120 + 35 + (80 * n), 192, 45, RA8875_RED);

  // First box in second column is placced oddly
  tft.drawRect(startPx + 200, 80 + 35, 192, 45, RA8875_RED);

  // Second column of boxes, except first
  for (n = 1; n < 4; n++)
    tft.drawRect(startPx + 200, 120 + 35 + (80 * n), 192, 45, RA8875_RED);

  // Starting info
  n = 0; // Used to lower times if ring or column # selector is shown
  if (type == 2 || type == 3) { // Is a ring or column
    n = 1;
    tft.drawRect(startPx + 395 + 58, 80 + 35, 24, 40, RA8875_RED);
    tft.textMode();
    tft.textTransparent(RA8875_RED);
    tft.textEnlarge(1);
    tft.textSetCursor(startPx + 395, 80);
    if (type == 2)
      tft.textWrite("Ring #:");
    else
      tft.textWrite("Column #");
    tft.graphicsMode();
  }

  // Start button
  tft.fillRect(startPx + 395, 80 + (n * 80), 140, 40, RA8875_GREEN);
  tft.drawRect(startPx + 395, 80 + (n * 80), 140, 40, RA8875_BLACK);
  tft.textMode();
  tft.textTransparent(RA8875_WHITE);
  tft.textEnlarge(2);
  tft.textSetCursor(startPx + 405, 74 + (n * 80));
  tft.textWrite("START");

  n++;
  if (type == 2 || type == 3)
    n++;

  if (shutterProfile[0] + shutterProfile[2] >
      ledProfile[1]) { // Shutter minimum running time longer than LED time;
                       // tell user
    tft.textTransparent(RA8875_RED);
    tft.textEnlarge(1);
    tft.textSetCursor(startPx + 395, 74 + (n * 45));
    tft.textWrite("Camera");
    tft.textSetCursor(startPx + 395, 74 + (n * 45) + 32);
    tft.textWrite("may not");
    tft.textSetCursor(startPx + 395, 74 + (n * 45) + 64);
    tft.textWrite("trigger!");
    tft.textSetCursor(startPx + 395, 74 + (n * 45) + 96);
    tft.textWrite("Make LED");
    tft.textSetCursor(startPx + 395, 74 + (n * 45) + 128);
    tft.textWrite("On Time");
    tft.textSetCursor(startPx + 395, 74 + (n * 45) + 156);
    tft.textWrite("longer.");
  } else { // Write in the LED numbers and orders
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);

    for (int i = 0; i < 64; i++)
      ledList[i] = 0; // List of all LEDs that could be used
    ledCount = 64;    // Number of LEDs that will be used
    ledListPositionCounter = 0;
    static unsigned char skipCount;
    skipCount = 0;

    if (type == 0) { // Column Scan
      ledCount = 0;  // Special array of LEDs that are usable

      for (int i = 0; i < 64; i += 1) {

        if (USE_CUSTOM_ARRAY(patternChannel) == 0b1 &&
            bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel)*8),
                    i % 8) == 0b1)
          continue;
        if (skipCount % ledProfile[0] != 0) { // Skip this LED
          skipCount++;
          continue;
        }
        skipCount++;

        ledList[ledListPositionCounter] = i + 1;
        ledListPositionCounter++;
      }
    } else if (type == 1) { // Ring scan

      for (int ring = 0; ring < 8; ring++)   // For each ring
        for (int i = ring; i < 64; i += 8) { // Loop through all LEDs in ring

          if (USE_CUSTOM_ARRAY(patternChannel) == 0b1 &&
              bitRead(
                  EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel)*8),
                  i % 8) == 0b1) // LED not usable
            continue;            // skip this LED because it cannot be used

          if (skipCount % ledProfile[0] != 0) {
            skipCount++;
            continue;
          }
          skipCount++;

          ledList[ledListPositionCounter] = i + 1;
          ledListPositionCounter++;
        }
    } else if (type == 2) {                            // Single Col
      for (int i = (ringColNum - 1); i < 64; i += 8) { // Loop through all LEDs

        if (USE_CUSTOM_ARRAY(patternChannel) == 0b1 &&
            bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel)*8),
                    i % 8) == 0b1) // LED not usable
          continue;                // skip this LED because it cannot be used

        if (skipCount % ledProfile[0] != 0) {
          skipCount++;
          continue;
        }
        skipCount++;

        ledList[ledListPositionCounter] = i + 1;
        ledListPositionCounter++;
      }

    } else if (type == 3) { // Single Ring

      for (int i = (8 * (ringColNum - 1)); i < (8 * (ringColNum - 1) + 8);
           i += 1) { // Loop through all LEDs

        if (USE_CUSTOM_ARRAY(patternChannel) == 0b1 &&
            bitRead(EEPROM.read(USABLE_IR_ARRAY + (i / 8) + (patternChannel)*8),
                    i % 8) == 0b1)
          continue; // skip this LED because it cannot be used

        if (skipCount % ledProfile[0] != 0) {
          skipCount++;
          continue;
        }
        skipCount++;

        ledList[ledListPositionCounter] = i + 1;
        ledListPositionCounter++;
      }
    }
    // if (ledCount == 0)
    //   name = "no LEDs";

    Serial.println(F("Dome LED numbers to be used:"));
    static unsigned char y, x;
    y = 0;
    ledListTextCounter = 0;
    for (int i = 0; i < 64; i++) {
      if (ledList[i] != 0) {
        if (ledListTextCounter >= 22) {
          y++;
          ledListTextCounter = 0;
        }
        // y = ledListTextCounter / 10;
        tft.textSetCursor(startPx + 395 + ((ledListTextCounter)*16),
                          74 + (n * 45) + (y * 32));
        char c[3];
        itoa(ledList[i], c, 10);
        tft.textWrite(c);
        if (ledList[i + 1] != 0 && i != 63)
          tft.textWrite(",");
        ledListTextCounter += 2;
        if (ledList[i] >= 10)
          ledListTextCounter++; // For double digit numbers
        Serial.print(ledList[i]);
        if (ledList[i + 1] != 0 && i != 63)
          Serial.print(",");
        else
          Serial.println(); // Add line to end list
      }
    }
  }

  tft.textTransparent(RA8875_BLUE);
  tft.textEnlarge(1);
  tft.textSetCursor(startPx + 395, tft.height() - ESTIMATED_TIME_HEIGHT - 35);
  tft.textWrite("Time:");
  tft.graphicsMode();
}

void ledOrderContent() {

  char title[10];
  tft.textMode();
  tft.textSetCursor(20, 70);
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textWrite("Choose a pattern type to begin:");
  unsigned char n = 0;

  // --> Full Scan
  buttons[2].width = 400;
  buttons[2].height = 50;
  buttons[2].x = 20;
  buttons[2].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[2].setText("All Columns");
  buttons[2].t = 2;
  buttons[2].action = 11; // Toggle mode is action 7
  buttons[2].drawBtn();
  // --> End full scan
  n++;
  // --> Spiral Down
  buttons[3].width = 400;
  buttons[3].height = 50;
  buttons[3].x = 20;
  buttons[3].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[3].setText("All Rings");
  buttons[3].t = 2;
  buttons[3].action = 12; // Toggle mode is action 7
  buttons[3].drawBtn();
  // --> End Spiral Down
  n++;
  // --> Single Ring
  buttons[4].width = 400;
  buttons[4].height = 50;
  buttons[4].x = 20;
  buttons[4].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[4].setText("Single Ring");
  buttons[4].t = 2;
  buttons[4].action = 13; // Toggle mode is action 7
  buttons[4].drawBtn();
  // --> End Single Ring
  n++;
  // --> Single Column
  buttons[5].width = 400;
  buttons[5].height = 50;
  buttons[5].x = 20;
  buttons[5].y = 90 + 20 + (50 * n) + (20 * n);
  buttons[5].setText("Single Column");
  buttons[5].t = 2;
  buttons[5].action = 14; // Toggle mode is action 7
  buttons[5].drawBtn();
  // --> End Single Column
  n++;
}

void settingsContent() {
  // --> First Button: Boolean (Display diagnostics)
  unsigned char n = 0;
  buttons[2].width = 400;
  buttons[2].height = 50;
  buttons[2].x = 20;
  buttons[2].y = 70 + 20 + (50 * n) + (20 * n);
  buttons[2].setText("Diagnostics");
  buttons[2].t = 3; // Boolean type
  buttons[2].m = (DISPLAY_DIAGNOSTICS_MODE == 1) ? (true) : (false); // Set mode
  buttons[2].action = 7; // Toggle mode is action 7
  buttons[2].drawBtn();
  // --> End First Button
  n++;
  // --> Restart
  buttons[3].width = 400;
  buttons[3].height = 50;
  buttons[3].x = 20;
  buttons[3].y = 70 + 20 + (50 * n) + (20 * n);
  buttons[3].setText("Restart");
  buttons[3].t = 2;
  buttons[3].action = 254; // Restart to page action
  buttons[3].drawBtn();
  // --> End Restart
  n++;
  // --> Calibrate Touch Screen
  buttons[4].width = 400;
  buttons[4].height = 50;
  buttons[4].x = 20;
  buttons[4].y = 70 + 20 + (50 * n) + (20 * n);
  buttons[4].setText("Recalibrate Touch");
  buttons[4].t = 3;
  buttons[4].m = (IS_TOUCH_CALIBRATED == 1) ? (true) : (false);
  buttons[4].action = 8; // Return to page action
  buttons[4].drawBtn();
  // --> End Calibrate Touch Screen
  n++;
  // --> Shutter active h/l
  buttons[5].width = 400;
  buttons[5].height = 50;
  buttons[5].x = 20;
  buttons[5].y = 70 + 20 + (50 * n) + (20 * n);
  buttons[5].setText("Combine Shutters");
  buttons[5].t = 3;
  buttons[5].m = (JOIN_SHUTTERS == 1) ? (true) : (false);
  buttons[5].action = 10; // Restart to page action
  buttons[5].drawBtn();
  // --> End Shutter active h/l
  n++;
  // Notice for user
  tft.textMode();
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textSetCursor(20, 70 + 20 + (50 * n) + (20 * n));
  tft.textWrite("More settings available when connected to serial via USB.");
  tft.graphicsMode();

  // Omitted due to lack of functionality. Function moved to obsolete folder
  // // --> Advanced settings (page handled differently)
  // buttons[6].width = 400;
  // buttons[6].height = 50;
  // buttons[6].x = 20;
  // buttons[6].y = 70 + 20 + (50 * n) + (20 * n);
  // buttons[6].setText("Advanced");
  // buttons[6].t = 2;
  // buttons[6].action = 31; // Restart to page action
  // buttons[6].drawBtn();
  // // --> End Advanced settings
}

#define RADIAL_X 595
#define RADIAL_Y 240
#define RADIAL_TRIG_BASE_FUNC(x, y)                                            \
  ((y - ((x % 2) * (3.14159 / 7)) - ((3.14259) / 2) + (3 * 3.14159 / 16)) *    \
   3.14159) /                                                                  \
      4
#define RADIAL_SIN_FUNC(x, y)                                                  \
  (RADIAL_X + ((x + 1) * 24) * sin(RADIAL_TRIG_BASE_FUNC(x, y)))
#define RADIAL_COS_FUNC(x, y)                                                  \
  (RADIAL_Y + ((x + 1) * 24) * -cos(RADIAL_TRIG_BASE_FUNC(x, y)))

void drawRadialPattern(char *positionHolder) {
  tft.fillCircle(RADIAL_X, RADIAL_Y, (9 * 24) + 5, RA8875_BLACK);
  for (unsigned char y = 0; y < 64; y++) {
    if (y % 8 == 0)
      tft.drawCircle(RADIAL_X, RADIAL_Y, (((y / 8) + 1) * 24), RA8875_WHITE);
    tft.fillCircle(RADIAL_SIN_FUNC((y % 8), (y / 8)),
                   RADIAL_COS_FUNC((y % 8), (y / 8)), 12,
                   (bitRead(positionHolder[(y / 8)], (y % 8)) == 0b1)
                       ? (RA8875_RED)
                       : (CUSTOM_GREEN));
    tft.textMode();
    tft.setTextSize(1);
    if (y >= 10)
      tft.textSetCursor(RADIAL_SIN_FUNC((y % 8), (y / 8)) - 15,
                        RADIAL_COS_FUNC((y % 8), (y / 8)) - 17);
    else
      tft.textSetCursor(RADIAL_SIN_FUNC((y % 8), (y / 8)) - 7,
                        RADIAL_COS_FUNC((y % 8), (y / 8)) - 17);
    tft.textTransparent(RA8875_CYAN);
    char c[4];
    itoa(y, c, 10);
    tft.textWrite(c);
    tft.graphicsMode();
  }

  tft.fillCircle(RADIAL_X - (9 * 24), RADIAL_Y, 20, RA8875_WHITE);
  while (tft.touched()) // empty touch buffer
    tft.touchRead(&tx, &ty);
}

void updateRadialPattern(unsigned char num, bool color) {
  unsigned char x = (((num + 1) % 8 == 0) ? 8 : (num + 1) % 8);
  unsigned char y = ((num + 1) + (((num + 1) % 8 != 0) ? 8 : 0)) / 8;
  Serial.println(x);
  Serial.println(y);
  Serial.println();
  x--;
  y--;
  tft.fillCircle(RADIAL_SIN_FUNC(x, y), RADIAL_COS_FUNC(x, y), 12,
                 (color) ? (RA8875_RED) : (CUSTOM_GREEN));
  tft.textMode();
  tft.setTextSize(1);
  if (num >= 10)
    tft.textSetCursor(RADIAL_SIN_FUNC(x, y) - 15, RADIAL_COS_FUNC(x, y) - 17);
  else
    tft.textSetCursor(RADIAL_SIN_FUNC(x, y) - 7, RADIAL_COS_FUNC(x, y) - 17);
  tft.textTransparent(RA8875_CYAN);
  char c[4];
  itoa(num, c, 10);
  tft.textWrite(c);
  tft.graphicsMode();
  while (tft.touched()) // empty touch buffer
    tft.touchRead(&tx, &ty);
}

unsigned char checkTouchRadial(int tx, int ty) {
  unsigned char ledNum = 255; // Set to error case return
  for (unsigned char y = 0; y < 64; y++) {
    if (abs(RADIAL_SIN_FUNC((y % 8), (y / 8)) - tx) < 12 &&
        abs(RADIAL_COS_FUNC((y % 8), (y / 8)) - ty) < 12)
      ledNum = y;
    // ledNum = X_Y_TO_NUMBER(x, y);
  }

  Serial.println(ledNum);
  while (tft.touched()) // empty touch buffer
    tft.touchRead(&tx, &ty);
  return ledNum;
}

void LEDPosition() {
  // Allows user to select for certain LEDs which LED's are populated.

  resetButtons();
  unsigned char n = 0; // Counter variable
  // Place the top banner:
  tft.fillScreen(RA8875_WHITE);
  tft.fillRect(0, 0, tft.width(), 70, RA8875_CYAN);
  buttons[0].setFromType(0);
  buttons[1].setFromType(1);
  buttons[0].drawBtn();
  buttons[1].drawBtn();
  if (DISPLAY_DIAGNOSTICS_MODE == 1) {
    tft.textMode();
    tft.textSetCursor(0, 0);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);
    char c[5];
    itoa(freeMemory(), c, 10);
    tft.textWrite(c);
    tft.textSetCursor(tft.width() - 50, tft.height() - 30);
    itoa(currentPage, c, 10);
    tft.textWrite(c);
    tft.graphicsMode();
  }

  // Individual bits represent whether an LED position is used.
  unsigned char positionHolder[8] = {0};

  // Holds which color is being modified. Invalid value preset
  unsigned char channel = 3;

  tft.textMode();
  tft.textSetCursor(20, 70);
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textWrite("Choose a channel/color to begin:");
  tft.graphicsMode();

  tft.drawRect(20, 90 + 20 + (50 * n) + (20 * n), 400, 50, RA8875_RED);
  tft.textMode();
  tft.textSetCursor(20, 90 + 20 + (50 * n) + (20 * n));
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textWrite(chNames[n]);
  tft.graphicsMode();
  n++;
  tft.drawRect(20, 90 + 20 + (50 * n) + (20 * n), 400, 50, RA8875_RED);
  tft.textMode();
  tft.textSetCursor(20, 90 + 20 + (50 * n) + (20 * n));
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textWrite(chNames[n]);
  tft.graphicsMode();
  n++;
  tft.drawRect(20, 90 + 20 + (50 * n) + (20 * n), 400, 50, RA8875_RED);
  tft.textMode();
  tft.textSetCursor(20, 90 + 20 + (50 * n) + (20 * n));
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textWrite(chNames[n]);
  tft.graphicsMode();

  while (channel == 3) {

    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        return;
      } // Home button

      n = 0;
      if (tx >= 20 && tx <= 20 + 400 && ty >= 90 + 20 + (50 * n) + (20 * n) &&
          ty <= 90 + 20 + (50 * n) + (20 * n) + 50) {
        channel = 0;
      }
      n++;
      if (tx >= 20 && tx <= 20 + 400 && ty >= 90 + 20 + (50 * n) + (20 * n) &&
          ty <= 90 + 20 + (50 * n) + (20 * n) + 50) {
        channel = 1;
      }
      n++;
      if (tx >= 20 && tx <= 20 + 400 && ty >= 90 + 20 + (50 * n) + (20 * n) &&
          ty <= 90 + 20 + (50 * n) + (20 * n) + 50) {
        channel = 2;
      }
      Serial.print(chNames[channel]);
      Serial.println(F(" chosen."));
    }
  }

  tft.fillRect(0, 70, 800, 350, RA8875_WHITE); // Clear screen
  tft.textMode();
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textSetCursor(30, 80);
  tft.textWrite("Use this grid to set whether an individual LED  will be used. "
                "If the dot is red, then the LED    will not be turned on "
                "while running an LED order. If disabled, all LEDs will be "
                "used but the grid   pattern will be saved.");
  tft.textSetCursor(280, 300);
  tft.textWrite("Tap to view grid.");
  tft.graphicsMode();

  while (!filterTouch()) { // Wait for any touch on the screen
  }

  tft.fillRect(0, 70, 800, 350, RA8875_WHITE); // Clear screen

  for (unsigned char i = 0; i < 8; i++)
    positionHolder[i] = EEPROM.read(USABLE_IR_ARRAY + (8 * channel) +
                                    i); // Set variable from EEPROM
  for (unsigned char y = 0; y < 64; y++) {
    Serial.print(bitRead(positionHolder[y % 8], y / 8));
    if (y % 8 == 7)
      Serial.println();
  }

  Serial.println();
  Serial.println();
  for (unsigned char y = 0; y < 64; y++) {
    Serial.print(
        bitRead(EEPROM.read(USABLE_IR_ARRAY + (8 * channel) + y / 8), y % 8));
    if (y % 8 == 7)
      Serial.println();
  }

  // Draw the array of buttons
  drawRadialPattern(positionHolder);

  // Disable button
  tft.fillRect(10, 160, 210, 60,
               (USE_CUSTOM_ARRAY(channel) == 0b1) ? (CUSTOM_GREEN)
                                                  : (RA8875_RED));

  // Save button
  tft.fillRect(10, 230, 210, 60, CUSTOM_GREEN);

  // All on
  tft.drawRect(10, 300, 210, 60, CUSTOM_GREEN);

  // All off
  tft.drawRect(10, 370, 210, 60, RA8875_RED);

  // Info and button text
  tft.textMode();
  tft.textTransparent(RA8875_BLACK);
  tft.textSetCursor(10, 80);
  tft.textWrite(chNames[channel]);

  tft.textSetCursor(10, 110);
  tft.textWrite("Tap an LED to toggle.");
  tft.textTransparent(RA8875_WHITE);

  tft.textSetCursor(50, 160);
  tft.textWrite("USE THIS");
  tft.textSetCursor(10, 185);
  tft.textWrite("CUSTOM ARRAY?");

  tft.textSetCursor(80, 240);
  tft.textWrite("SAVE");

  tft.textTransparent(RA8875_BLACK);

  tft.textSetCursor(60, 310);
  tft.textWrite("ALL ON");

  tft.textSetCursor(40, 380);
  tft.textWrite("ALL OFF");
  tft.graphicsMode();

  // Loop for modifying data
  while (true) {
    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        return;
      } // Home button

      // Check array
      if (tx > RADIAL_X - (9 * 24)) {
        // For rectangular selector
        // for (unsigned char x = 0; x < 8; x++) {
        //   for (unsigned char y = 0; y < 8; y++) {
        //     if (tx > 395 + (x * 50) && tx < 395 + (x * 50) + 46 &&
        //         ty > 74 + (y * 50) && ty < 74 + (y * 50) + 46) {
        // Serial.println("running");
        unsigned char num = checkTouchRadial(tx, ty); // Reurns bit for changing
        // num--;
        if (num != 255) { // if there was a touch
          // unsigned char y = ((num % 8 == 0) ? (8) : ((num % 8)));
          // unsigned char x = (num) / 8;
          unsigned char y = (((num + 1) % 8 == 0) ? 8 : (num + 1) % 8);
          unsigned char x = ((num + 1) + (((num + 1) % 8 != 0) ? 8 : 0)) / 8;
          x--;
          y--;
          for (unsigned char i = 0; i < 8;
               i++) {     // go through each bit in this variable
            if (i == y) { // if i is the returned bit
              positionHolder[x] ^= _BV(i); // change bit i in the variable
              updateRadialPattern(num, (bitRead(positionHolder[x], i) == 0b1));
            } // i == y
          }   // i loop
          // drawRadialPattern(positionHolder);
        }
        //     }                                    // touch check
        //   }                                      // y loop
        // }                                        // x loop
      } // END check array

      if (tx > 10 && tx < 220) { // BUTTONS
        // Disable button
        if (ty > 160 && ty < 160 + 60) {
          TOGGLE_USE_CUSTOM_ARRAY(channel);
          tft.fillRect(10, 160, 210, 60,
                       (USE_CUSTOM_ARRAY(channel) == 0b1) ? (CUSTOM_GREEN)
                                                          : (RA8875_RED));
          tft.textMode();
          tft.textTransparent(RA8875_WHITE);
          tft.textSetCursor(50, 160);
          tft.textWrite("USE THIS");
          tft.textSetCursor(10, 185);
          tft.textWrite("CUSTOM ARRAY?");
          tft.graphicsMode();
        }

        // Save button
        if (ty > 230 && ty < 230 + 60) {
          tft.fillRect(10, 230, 210, 60, RA8875_WHITE);

          // for (unsigned char y = 0; y < 64; y++) {
          //   if (bitRead(positionHolder[y % 8], y / 8) == 0b1)
          //     EEPROM.write(USABLE_IR_ARRAY + (8 * channel) + y % 8,
          //                  EEPROM.read(USABLE_IR_ARRAY + (8 * channel)) |
          //                      0b1 << y / 8);
          //   else
          //     EEPROM.write(USABLE_IR_ARRAY + (8 * channel) + y % 8,
          //                  EEPROM.read(USABLE_IR_ARRAY + (8 * channel)) &
          //                      ~(0b1 << y / 8));
          //
          //   Serial.print(bitRead(
          //       EEPROM.read(USABLE_IR_ARRAY + (8 * channel) + y / 8), y %
          //       8));
          //   if (y % 8 == 7)
          //     Serial.println();
          // }

          for (unsigned char y = 0; y < 8; y++) {
            EEPROM.write(USABLE_IR_ARRAY + (8 * channel) + y,
                         positionHolder[y]);
          }

          for (unsigned char y = 0; y < 64; y++) {
            Serial.print(bitRead(
                EEPROM.read(USABLE_IR_ARRAY + (8 * channel) + y / 8), y % 8));
            if (y % 8 == 7)
              Serial.println();
          }

          tft.fillRect(10, 230, 210, 60, CUSTOM_GREEN);
          tft.textMode();
          tft.textTransparent(RA8875_WHITE);
          tft.textSetCursor(80, 240);
          tft.textWrite("SAVE");
          tft.graphicsMode();
        }

        // All on
        if (ty > 300 && ty < 300 + 60) {
          for (unsigned char x = 0; x < 8; x++)
            positionHolder[x] = 0; // All bits == 0 (array inverted)

          drawRadialPattern(positionHolder);
        }

        // All off
        if (ty > 370 && ty < 370 + 60) {
          for (unsigned char x = 0; x < 8; x++)
            positionHolder[x] = 255; // All bits == 1 (array inverted)
          drawRadialPattern(positionHolder);
        }
      } // END BUTTONS
    }
  }
}

void displaySingleLed() {
  // Allows user to turn on or off specific LEDs by location.
  char name[32]; // Used as placeholder

  resetButtons();
  // static unsigned char n; // Counter variable
  // n = 0;
  // Place the top banner:
  // tft.fillScreen(RA8875_WHITE);
  // tft.fillRect(0, 0, tft.width(), 70, RA8875_CYAN);
  buttons[0].setFromType(0);
  buttons[1].setFromType(1);
  buttons[0].drawBtn();
  buttons[1].drawBtn();
  if (DISPLAY_DIAGNOSTICS_MODE == 1) {
    tft.textMode();
    tft.textSetCursor(0, 0);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);
    itoa(freeMemory(), name, 10);
    tft.textWrite(name);
    tft.textSetCursor(tft.width() - 50, tft.height() - 30);
    itoa(currentPage, name, 10);
    tft.textWrite(name);
    tft.graphicsMode();
  }

  // Holds which color is being modified. Channel 1 preset.
  static unsigned char channel = 0, previousChannel = 0, ledNumber = 255,
                       previousLedNumber = 255,
                       positionHolder[8] = {255, 255, 255, 255,
                                            255, 255, 255, 255};

  channel = 0;
  previousChannel = 0;
  ledNumber = 255;
  previousLedNumber = 255;
  for (int i = 0; i < 8; i++)
    positionHolder[i] = 255;

  // static bool shutterHigh = true;
  static unsigned char profileValues[3];

  // tft.fillRect(0, 70, 800, 350, RA8875_WHITE); // Clear screen
  tft.textMode();
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  tft.textSetCursor(30, 80);
  tft.textWrite("Use this grid to activate an LED. Only one LED  can be active "
                "at one time.");
  tft.textSetCursor(280, 300);
  tft.textWrite("Tap to view grid.");
  tft.graphicsMode();

  while (!filterTouch()) { // Wait for any touch on the screen
  }

  tft.fillRect(0, 70, 800, 350, RA8875_WHITE); // Clear screen
  //
  // for (unsigned char i = 0; i < 8; i++)
  //   positionHolder[i] = EEPROM.read(USABLE_IR_ARRAY + (8 * channel) +
  //                                   i); // Set variable from EEPROM

  // Draw the array of buttons
  drawRadialPattern(positionHolder);

  // Shutter profile
  tft.drawRect(10, 90, 210, 60, RA8875_BLACK);
  // Channel 1
  tft.fillRect(10, 160, 210, 60,
               (channel == 0) ? (CUSTOM_GREEN) : (RA8875_RED));

  // Channel 2
  tft.fillRect(10, 230, 210, 60,
               (channel == 1) ? (CUSTOM_GREEN) : (RA8875_RED));

  // Channel 3
  tft.fillRect(10, 300, 210, 60,
               (channel == 2) ? (CUSTOM_GREEN) : (RA8875_RED));
  // Shutter control
  tft.drawRect(10, 370, 210, 60, RA8875_BLACK);

  // Info and button text
  tft.textMode();
  tft.textTransparent(RA8875_BLACK);
  tft.textSetCursor(20, 100);
  tft.textWrite("Shutter Prof");
  tft.textTransparent(RA8875_WHITE);
  tft.textSetCursor(20, 170);
  tft.textWrite(chNames[0]);
  tft.textSetCursor(20, 240);
  tft.textWrite(chNames[1]);
  tft.textSetCursor(20, 310);
  tft.textWrite(chNames[2]);
  tft.textTransparent(RA8875_BLACK);
  tft.textSetCursor(20, 380);
  tft.textWrite("Active: ");
  tft.textWrite(shutterTriggerTypes[(profileValues[1]) ? 0 : 1]);

  tft.setTextSize(1);
  tft.textSetCursor(10, 450);
  tft.textWrite("Dome LED#:");
  tft.textSetCursor(200, 450);
  tft.textWrite(", LED#:");
  tft.graphicsMode();

  // Loop for modifying data
  while (true) {
    if (filterTouch()) {
      if (DISPLAY_DIAGNOSTICS_MODE == 1)
        tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
      // Touch is now filtered, find what to do and do it.
      if (buttons[0].checkTouch(tx, ty)) {
        disableAllLEDs();
        return;
      } // Home button

      else if (buttons[1].checkTouch(tx, ty)) {
        disableAllLEDs();
        return;
      } // Home button

      // Check array
      if (tx > RADIAL_X - (9 * 24)) {
        unsigned char num = checkTouchRadial(tx, ty); // Reurns bit for changing
        if (num != 255) {                             // if there was a touch
          updateRadialPattern(num, 0b0);
          if (previousLedNumber != 255)
            updateRadialPattern(previousLedNumber, 0b1);
          ledNumber = num;

          tft.fillRect(170, 450, 50, 29, RA8875_WHITE);
          tft.fillRect(320, 450, 50, 29, RA8875_WHITE);

          tft.textMode();
          tft.textTransparent(RA8875_BLACK);
          tft.setTextSize(1);
          tft.textSetCursor(170, 450);
          itoa(num, name, 10);
          tft.textWrite(name);
          tft.textWrite(",");
          tft.textSetCursor(320, 450);
          itoa(num + (channel * 64), name, 10);
          tft.textWrite(name);
          tft.graphicsMode();
        }
      } // END check array

      if (tx > 10 && tx < 220) { // BUTTONS
        // Shutter Profiles
        if (ty > 90 && ty < 90 + 60) {
          tft.fillRect(10, 90, 512, 8 * 45, RA8875_WHITE);
          for (int y1 = 0; y1 < 8; y1++) { // PLACE BOXES
            tft.drawRect(10, 90 + (y1 * 45), 512, 45, RA8875_BLACK);
            tft.textMode();
            tft.textSetCursor(10, 90 + (y1 * 45));
            tft.textTransparent(RA8875_BLACK);
            tft.textEnlarge(1);
            readProfileName(4, y1 + 1, name);
            tft.textWrite(name, 32);
            tft.graphicsMode();
          }
          static boolean checkShutterChannel;
          checkShutterChannel = true;
          while (checkShutterChannel) {
            if (filterTouch()) {
              if (DISPLAY_DIAGNOSTICS_MODE == 1)
                tft.fillCircle((tx), (ty), 4, RA8875_BLUE);
              if (buttons[0].checkTouch(tx, ty)) {
                disableAllLEDs();
                return;
              } // Home button

              else if (buttons[1].checkTouch(tx, ty)) {
                disableAllLEDs();
                return;
              }                                // Home button
              for (int y1 = 0; y1 < 8; y1++) { // PLACE BOXES
                if (ty > 90 + (y1 * 45) && ty < 90 + (y1 * 45) + 45)
                  if (tx > 10 && tx < 10 + 512) {
                    readProfile(4, y1 + 1, profileValues);
                    Serial.println(y1);
                    tft.fillRect(0, 70, 800, tft.height() - 70,
                                 RA8875_WHITE); // Clear screen

                    drawRadialPattern(positionHolder);
                    tft.drawRect(10, 90, 210, 60, RA8875_BLACK);
                    tft.fillRect(10, 160, 210, 60,
                                 (channel == 0) ? (CUSTOM_GREEN)
                                                : (RA8875_RED));
                    tft.fillRect(10, 230, 210, 60,
                                 (channel == 1) ? (CUSTOM_GREEN)
                                                : (RA8875_RED));
                    tft.fillRect(10, 300, 210, 60,
                                 (channel == 2) ? (CUSTOM_GREEN)
                                                : (RA8875_RED));
                    tft.drawRect(10, 370, 210, 60, RA8875_BLACK);

                    tft.textMode();
                    tft.textTransparent(RA8875_BLACK);
                    tft.textSetCursor(20, 100);
                    tft.textWrite("Shutter Prof");
                    tft.textTransparent(RA8875_WHITE);
                    tft.textSetCursor(20, 170);
                    tft.textWrite(chNames[0]);
                    tft.textSetCursor(20, 240);
                    tft.textWrite(chNames[1]);
                    tft.textSetCursor(20, 310);
                    tft.textWrite(chNames[2]);
                    tft.textTransparent(RA8875_BLACK);
                    tft.textSetCursor(20, 380);
                    tft.textWrite("Active: ");
                    tft.textWrite(
                        shutterTriggerTypes[(profileValues[1]) ? 0 : 1]);
                    tft.setTextSize(1);
                    tft.textSetCursor(10, 450);
                    tft.textWrite("Dome LED#:");
                    tft.textSetCursor(200, 450);
                    tft.textWrite(", LED#:");
                    tft.graphicsMode();
                    tft.graphicsMode();
                    checkShutterChannel = false;
                    break;
                  }
              }
            }
          }
        }

        // Channel 1
        if (ty > 160 && ty < 160 + 60) {
          channel = 0;
          ledNumber = 255;
        }

        // Channel 2
        if (ty > 230 && ty < 230 + 60) {
          channel = 1;
          ledNumber = 255;
        }

        // Channel 3
        if (ty > 300 && ty < 300 + 60) {
          channel = 2;
          ledNumber = 255;
        }

        // Active shutter level
        if (ty > 380 && ty < 380 + 60) {
          profileValues[1] = !profileValues[1];
          ledArray[previousLedNumber + (64 * previousChannel)].trigger(
              0, 0, profileValues[1]); // Disable any LEDs and ensure that the
                                       // shutter is correctly set
          tft.fillRect(10, 370, 210, 60, RA8875_WHITE);
          tft.drawRect(10, 370, 210, 60, RA8875_BLACK);
          tft.textMode();
          tft.textTransparent(RA8875_BLACK);
          tft.textSetCursor(20, 380);
          tft.textWrite("Active: ");
          tft.textWrite(shutterTriggerTypes[(profileValues[1]) ? 0 : 1]);
          tft.graphicsMode();
        }

        // Channel 1
        tft.fillRect(10, 160, 210, 60,
                     (channel == 0) ? (CUSTOM_GREEN) : (RA8875_RED));

        // Channel 2
        tft.fillRect(10, 230, 210, 60,
                     (channel == 1) ? (CUSTOM_GREEN) : (RA8875_RED));

        // Channel 3
        tft.fillRect(10, 300, 210, 60,
                     (channel == 2) ? (CUSTOM_GREEN) : (RA8875_RED));

        // Info and button text
        tft.textMode();
        tft.textTransparent(RA8875_WHITE);
        tft.textSetCursor(20, 170);
        tft.textWrite(chNames[0]);
        tft.textSetCursor(20, 240);
        tft.textWrite(chNames[1]);
        tft.textSetCursor(20, 310);
        tft.textWrite(chNames[2]);
        tft.graphicsMode();

        updateRadialPattern(previousLedNumber, 0b1);
      } // END BUTTONS
      Serial.println(ledNumber);
      Serial.println(previousLedNumber);
      if (ledNumber != previousLedNumber) {
        if (ledNumber != 255) {
          Serial.print(F("Running LED #"));
          Serial.println(ledNumber + (64 * channel));
        }
        if (previousLedNumber != 255)
          ledArray[previousLedNumber + (64 * previousChannel)].trigger(
              0, 0, profileValues[1]);
        delay(100); // If the shutter has not been turned off yet from last
                    // lighting, give .1s for it to be turned off.
        if (ledNumber != 255)
          ledArray[ledNumber + (64 * channel)].trigger(
              1, (profileValues[0] > 0) ? profileValues[0] : 10,
              profileValues[1]);
        previousLedNumber = ledNumber;
        previousChannel = channel;
      } else
        ledArray[previousLedNumber + (64 * previousChannel)].trigger(
            0, 0, profileValues[1]);
    }
    checkShutters(profileValues[1]);
  }
}

bool updateDisplay() {
  if (filterTouch()) {
    if (DISPLAY_DIAGNOSTICS_MODE == 1)
      tft.fillCircle((uint16_t)(tx), (uint16_t)(ty), 4, RA8875_CYAN);

    // Touch is now filtered, find what to do and do it.
    if (tx >= STOPBUTTON_X && tx <= STOPBUTTON_X + STOPBUTTON_W)
      if (ty >= STOPBUTTON_Y && ty <= STOPBUTTON_Y + STOPBUTTON_H) {
        // stopPattern = true; // Stops any pattern currently executing
        return true;
      }
  }
  return false;
}

void updateDisplayOBSOLETE() {
  if (filterTouch()) {
    if (DISPLAY_DIAGNOSTICS_MODE == 1)
      tft.fillCircle((uint16_t)(tx), (uint16_t)(ty), 4, RA8875_CYAN);

    // Touch is now filtered, find what to do and do it.
    if (tx >= STOPBUTTON_X && tx <= STOPBUTTON_X + STOPBUTTON_W)
      if (ty >= STOPBUTTON_Y && ty <= STOPBUTTON_Y + STOPBUTTON_H) {
        // stopPatternOLD = true; // Stops any pattern currently executing
        // testChar = 2;
        // Serial.println(testChar);
      }
  }
}

void timeToString(float val, char *ch, bool include_s = false,
                  bool addPeriod = true) {
  // tens = (int)val/10
  // ones = (int)(val - (((int)(val / 10)) * 10))
  // tenths = (int)((val-((int)val))*10)
  for (int i = 0; i < 7; i++)
    ch[i] = 0;
  dtostrf(val, 1, addPeriod ? 1 : 0, ch);
  if (include_s)
    for (int i = 0; i < 7; i++)
      if (ch[i] == 0) {
        ch[i] = 's';
        return;
      }
  // if (val != 0) {
  //   char c;
  //   itoa((int)val / 10, &c, 10);
  //   ch[0] = c;
  //   itoa((int)(val - (((int)(val / 10)) * 10)), &c, 10);
  //   ch[1] = c;
  //   if (addPeriod) {
  //     ch[2] = '.';
  //     itoa((int)((val - ((int)val)) * 10), &c, 10);
  //     ch[3] = c;
  //   } else {
  //     ch[2] = ' ';
  //     ch[3] = ' ';
  //   }
  //   ch[4] = include_s ? 's' : ' ';
  // } else {
  //   ch[0] = '0';
  //   ch[1] = include_s ? 's' : ' ';
  //   ch[2] = ' ';
  //   ch[3] = ' ';
  //   ch[4] = ' ';
  // }
}

void beginDisplay() {
  assignCHNamesDisplayFile();
  // Start the display
  if (!tft.begin(RA8875_800x480)) // If display begins
    Serial.print(F("Beiginning display via RA8875..."));
  else { // Display startup may have failed; write this to the serial and
         // continue in case it does work
    // Failure mode seems to always trip despite display working, so no
    // warning
    // is given (commented out):
    // Serial.println(F("RA8875 display interface not found! Touch display
    // input
    // "
    //                  "and/or output are unlikely to work."));
  }

  tft.displayOn(true);
  tft.GPIOX(true); // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);                             // Always at full brightness

  // Scales are to scale touches to the screen pixel counts; is obsolete
  // xScale = 1024.0F / tft.width();
  // yScale = 1024.0F / tft.height();

  // Test diplay colors
  tft.fillScreen(RA8875_RED);
  delay(150);
  tft.fillScreen(RA8875_GREEN);
  delay(150);
  tft.fillScreen(RA8875_CYAN);
  delay(150);

  pinMode(RA8875_INT, INPUT);
  digitalWrite(RA8875_INT, HIGH);

  tft.touchEnable(true);
  Serial.println(F("Initialized Display."));
  while (tft.touched()) // Clear any touches in touch buffer
    tft.touchRead(&tx, &ty);

  // Set up calibration
  Serial.println(IS_TOUCH_CALIBRATED);
  if (IS_TOUCH_CALIBRATED) {
    EEPROM_readAnything(TOUCH_CAL_X1_ADDR, cal[0]);
    EEPROM_readAnything(TOUCH_CAL_X2_ADDR, cal[1]);
    EEPROM_readAnything(TOUCH_CAL_Y1_ADDR, cal[2]);
    EEPROM_readAnything(TOUCH_CAL_Y2_ADDR, cal[3]);
  } else {
    Serial.println(
        F("Touch screen was not calibrated. Starting Calibration.."));
    calTouch();
  }
}

// void (*resetFunc)(void) = 0; // Software reset of arduino.

void preformAction(unsigned char action) {
  // Preforms an action from the touch of a button. Used for simple actions,
  // such as page and single variable chages
  switch (action) {

  // Pages from home

  case 0: // BEGIN HOME
    enterPage(0);
    break; // END HOME
  case 1:  // BEGIN HELP
    enterPage(6);
    break; // END HELP
  case 3:  // BEGIN MULTI LED
    enterPage(3);
    break; // END MULTI LED
  case 4:  // BEGIN SINGLE LED
    enterPage(4);
    break; // END SINGLE LED
  case 5:  // BEGIN SETTINGS
    enterPage(2);
    break; // END SETTINGS
  case 6:  // BEGIN PROFILES
    enterPage(5);
    break; // END PROFILES

  // Settings

  case 7:
    TOGGLE_DISPLAY_DIAGNOSTICS_MODE; // Toggle mode
    enterPage(currentPage);          // Retuen to page
    break;
  case 8:                 // BEGIN CALIBRATE
    delay(100);           // Delay to avoid mis-taps
    while (tft.touched()) // Clear touch buffer
      tft.touchRead(&tx, &ty);
    calTouch();             // Calibrate
    enterPage(currentPage); // Retuen to page
    break;                  // END CALIBRATE
  case 9:                   // BEGIN UNSET
    break;                  // END UNSET
  case 10:                  // JOIN SHUTTERS
    TOGGLE_JOIN_SHUTTERS;   // Toggle mode
    enterPage(currentPage); // Retuen to page
    break;                  // END JOIN SHUTTERS

  // LED Patterns

  case 11: // BEGIN FULL SCAN
    enterPage(7);
    break; // END FULL SCAN
  case 12: // BEGIN SPIRAL SCAN
    enterPage(8);
    break; // END SPIRAL SCAN
  case 13: // BEGIN RING
    enterPage(9);
    break; // END RING
  case 14: // BEGIN COLUMN
    enterPage(10);
    break; // END COLUMN

  case 20: // BEGIN PROFILE: COL SCAN
    setProfile(0);
    break; // BEGIN PROFILE: COL SCAN
  case 21: // BEGIN PROFILE: RING SCAN
    setProfile(1);
    break; // BEGIN PROFILE: RING SCAN
  case 22: // BEGIN PROFILE: SINGLE RING
    setProfile(2);
    break; // BEGIN PROFILE: SIGNLE RING
  case 23: // BEGIN PROFILE: SINGLE COL
    setProfile(3);
    break; // BEGIN PROFILE: SINGLE COL
  case 24: // BEGIN PROFILE: SHUTTERS
    setProfile(4);
    break; // BEGIN PROFILE: SHUTTERS
  case 25:
    setProfile(5);
    break;

  // Additional Pages

  case 30: // BEGIN SELF TEST
    selfTest();
    break; // END SELF TEST
  case 31: // BEGIN LED POSITIONS
    LEDPosition();
    break; // END SELF TEST

  // General/multi purpose

  case 254: // BEGIN RESET
    Serial.println("\n\n\n\n\t\tSERIAL RESET ~~~~~~~~~~~~~~~~~~~~~~~\n");
    delay(200);  // Wait for stray touches and Serial messages to process
    resetFunc(); // Reset
    break;       // END RESET
  case 255:      // RETURN TO PAGE
    enterPage(currentPage);
    break; // END PROFILES
  default:
    return;
    break;
  }
}

bool filterTouch() {
  // Function that uses global variables tx and ty to read and calibrate a
  // touch. If a circle is to be drawn, it must be done externally
  if (tft.touched()) { // If the tft was touched
    if (millis() - lastTouchTime >= touchDebounceDelay) {
      lastTouchTime = millis();
      tft.touchRead(&tx, &ty);
      // Calibration is a linear change based on two preselected points
      tx = map(tx, cal[0], cal[1], 0, 1024);
      ty = map(ty, cal[2], cal[3], 0, 1024);
      // Limit max touch; if touch is higher than 1023 it will roll over ot
      // start of diplay
      if (tx >= 1024)
        tx = 1023;
      if (ty >= 1024)
        ty = 1023;
      // Set touch to a pixel locaiton
      tx *= tft.width() / 1024.0F;
      ty *= tft.height() / 1024.0F;
      // If wanted by user, update free RAM
      if (DISPLAY_DIAGNOSTICS_MODE == 1) {
        tft.fillRect(0, 0, 64, 32, RA8875_WHITE);
        tft.textMode();
        tft.textSetCursor(0, 0);
        tft.textTransparent(RA8875_BLACK);
        tft.textEnlarge(1);
        char c[5];
        itoa(freeMemory(), c, 10);
        tft.textWrite(c);
        tft.graphicsMode();
      }

      // If verbose serial is enabled, touch calibrated locations are written
      if (VERBOSE_SERIAL) {
        Serial.print(F("Touch coord = "));
        Serial.print(tx);
        Serial.print(F(", "));
        Serial.println(ty);
      }
      tbi(PORTB, PB7);
      return true; // Touch vars now filtered; return true
    }
    // Touch happened too fast for the debounce delay
    while (tft.touched()) // Clear any double touches in touch buffer
      tft.touchRead(&tx, &ty);
    tx = 0; // Do not allow touch vars to be used
    ty = 0;
    return false; // Return failure
  }
  return false; // Return failure
}

// Merged into void checkTouch();
// void checkTouchLocation(uint16_t x, uint16_t y) {
//   // Gets the touch location and checks if it is assiciated with any
//   // button objects.
//   if (DISPLAY_DIAGNOSTICS_MODE == 1)
//     tft.fillCircle((uint16_t)(x), (uint16_t)(y), 4, RA8875_RED);
//   for (int i = 0; i < 10; i++)
//     buttons[i].checkTouch(x, y);
// }

// Checks touches against buttons that are universally set.
void checkTouch() {
  if (!digitalRead(RA8875_INT)) {
    if (tft.touched()) {
      if (filterTouch()) {
        if (DISPLAY_DIAGNOSTICS_MODE == 1)
          tft.fillCircle((tx), (ty), 4, RA8875_RED);
        for (int i = 0; i < 10; i++)
          buttons[i].checkTouch(tx, ty);
        lastTouchTime = millis();
      }
    }
  }
}

void calTouch() { // Touch screen calibration

  // Multiple touches might have been registered when the user tapped to
  // engage
  // calibration; these must be cleared by manually clearing the buffer
  while (tft.touched()) {    // While buffer is not empty
    tft.touchRead(&tx, &ty); // Remove touch
    delay(50); // Program would not function well without this delay
  }
  lastTouchTime =
      millis(); // Set the start time as the last touch time for filtering
  Serial.println(
      F("Beginning display calibration. Follow the instructions on "
        "the display, or press 'c' to cancel (press 's' to prevent further "
        "attempts to calibrate until calibration is reset in serial "
        "settings.)"));
  tft.fillScreen(RA8875_WHITE);
  tft.textMode();
  tft.textSetCursor(0, 220);
  tft.textTransparent(RA8875_RED);
  tft.textEnlarge(1);
  tft.textWrite("Tap on the red circles as accurately as possible.");
  tft.graphicsMode();
  tft.fillCircle(20, 20, 8, RA8875_RED);   // Draw first circle
  tft.fillCircle(20, 20, 2, RA8875_WHITE); // Draw inner first circle
  int i = 0;                               // Counter variable
  while (i < 2) {                          // Two circles will be placed
    if (!digitalRead(RA8875_INT)) {
      Serial.println(F("Touch detected while calibrating."));
      if (tft.touched()) {       // If touch is detected
        tft.touchRead(&tx, &ty); // Get the values
        if (VERBOSE_SERIAL) {
          Serial.print(F("Calibration coord = "));
          Serial.print(tx);
          Serial.print(F(", "));
          Serial.println(ty);
        }
        if (millis() - lastTouchTime >=
            touchDebounceDelay) {                 // Filter input with delay
          if (i == 0) {                           // First circle was tapped
            tx -= (20 / (tft.width() / 1024.0F)); // Scale points to pixels
            ty -= (20 / (tft.height() / 1024.0F));
            cal[0] = tx; // Set calibration values tx #1 and ty #1
            cal[2] = ty;
            // cal[0] = tx - 10 / (float)(1024 / tft.height()); // Leftmost
            // cal[2] = ty - 10 / (float)(1024 / tft.width());  // Topmost
            tft.fillScreen(RA8875_WHITE);
            tft.textMode();
            tft.textSetCursor(0, 220);
            tft.textEnlarge(2);
            tft.textTransparent(RA8875_RED);
            tft.textWrite("Tap on the red circles as accurately as possible.");
            tft.graphicsMode();
            tft.fillCircle(tft.width() - 20, tft.height() - 20, 8,
                           RA8875_RED); // Draw second circle
            tft.fillCircle(tft.width() - 20, tft.height() - 20, 2,
                           RA8875_WHITE); // Draw inner second circle
          }
          if (i == 1) {                           // Second circle was tapped
            tx += (20 / (tft.width() / 1024.0F)); // Scale points to pixels
            ty += (20 / (tft.height() / 1024.0F));
            cal[1] = tx; // Set calibration values tx #2 and ty #2
            cal[3] = ty;
          }
          i++; // Add to the couter variable regardless of which circle is
               // touched
          lastTouchTime =
              millis(); // Set at the end to avoid any double touches
        }
      }
    }
    if (Serial.available()) {
      static char calTouchSerialRead;
      calTouchSerialRead = Serial.read();
      Serial.print(F("Recieved: "));
      Serial.println(calTouchSerialRead);
      if (calTouchSerialRead == 'c') {
        Serial.println("Cancelled");
        return;
      }
      if (calTouchSerialRead == 's') {
        Serial.println(F("Cancelled; will not re-enter calibration until "
                         "calibration is reset."));
        TOGGLE_TOUCH_CALIBATED; // toggle calibration to not run again
        return;
      }
    }
  }
  Serial.println(F("Saving calibration..."));
  // Write the calibration values to the EEPROM address. Writes integers (2
  // bytes,) so EEPROM_writeAnyting is used.
  EEPROM_writeAnything(TOUCH_CAL_X1_ADDR, cal[0]);
  EEPROM_writeAnything(TOUCH_CAL_X2_ADDR, cal[1]);
  EEPROM_writeAnything(TOUCH_CAL_Y1_ADDR, cal[2]);
  EEPROM_writeAnything(TOUCH_CAL_Y2_ADDR, cal[3]);

  // Values are read from the EEPROM again for serial validation.
  EEPROM_readAnything(TOUCH_CAL_X1_ADDR, cal[0]);
  EEPROM_readAnything(TOUCH_CAL_X2_ADDR, cal[1]);
  EEPROM_readAnything(TOUCH_CAL_Y1_ADDR, cal[2]);
  EEPROM_readAnything(TOUCH_CAL_Y2_ADDR, cal[3]);

  // Serial validation
  Serial.println(cal[0]);
  Serial.println(cal[1]);
  Serial.println(cal[2]);
  Serial.println(cal[3]);

  // Write the single bit that defines touch as calibrated.
  TOGGLE_TOUCH_CALIBATED;
  // tft.fillScreen(RA8875_WHITE);
  Serial.println(F("Display Calibration Complete."));
  enterPage(0); // Show the home page
}

void patternModeDisplay(float percentageComplete, unsigned char ledNum,
                        unsigned char channel = 1) {
  // Draws a progress bar, run time, LED number, and stop button ot the
  // display
  // while a pattern is being run.

  // Start the progress bar on the display at percentage 0 (first LED)
  // NOTE: This may need to be engaged before pattern starts.
  tft.fillRect(PROGBAR_X - 15, PROGBAR_Y, PROGBAR_W + 30, PROGBAR_H + 40,
               RA8875_BLACK);
  // Changes the progress bar color based on the channel
  if (channel == 1)
    tft.fillRect(PROGBAR_X, PROGBAR_Y, PROGBAR_W * percentageComplete,
                 PROGBAR_H, RA8875_RED);
  if (channel == 2)
    tft.fillRect(PROGBAR_X, PROGBAR_Y, PROGBAR_W * percentageComplete,
                 PROGBAR_H, RA8875_WHITE);
  if (channel == 3)
    tft.fillRect(PROGBAR_X, PROGBAR_Y, PROGBAR_W * percentageComplete,
                 PROGBAR_H, RA8875_MAGENTA);
  tft.fillRect(PROGBAR_X - 15, PROGBAR_Y + PROGBAR_H, PROGBAR_W + 30, 100,
               RA8875_BLACK);
  // Write LED number and run time
  tft.textMode();
  tft.textTransparent(RA8875_WHITE);
  tft.textEnlarge(1);
  tft.textSetCursor(PROGBAR_X - 15, PROGBAR_Y + PROGBAR_H);
  tft.textWrite("Dome #");
  static char c[6];
  for (int i = 0; i < 6; i++)
    c[i] = 0;
  itoa(ledNum + 1 - (64 * (channel - 1)), c, 10);
  tft.textWrite(c, 3);

  tft.textSetCursor(PROGBAR_X - 15, PROGBAR_Y + PROGBAR_H + 32);
  tft.textWrite("Time: "); // patterStartTime defined by the pattern starter
  timeToString(((float)(millis() - patternStartTime)) / 1000, c, true, true);
  tft.textWrite(c, 6);

  tft.textSetCursor(PROGBAR_X - 15, PROGBAR_Y + PROGBAR_H + 64);
  tft.textWrite("LED #");
  for (int i = 0; i < 6; i++)
    c[i] = 0;
  itoa(ledNum, c, 10);
  tft.textWrite(c, 3);
}
