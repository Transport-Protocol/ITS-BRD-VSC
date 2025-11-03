/**
  * @file display.c
  * @author Franz Korf, HAW Hamburg 
  * @date Mar 2016
  * @brief This modules implements a simple output module. 
  *        It places two terminals in the terminal area of keypad.
  *        One terminal will be used for standard output. The other one
  *        echos pressed digit keys.
  */

#include "display.h"
#include <stdlib.h>
#include "terminal.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "keypad.h"

static Terminal stdoutTerm = INVALID_TERM;
static Terminal echoTerm   = INVALID_TERM;

void clearStdout(void){
   clearTerm(&stdoutTerm);
}

void clearEchoTerm(void){
   clearTerm(&echoTerm);
}

void printStdout(char *m){
   printTerm(m, &stdoutTerm);
}

void initDisplay(void) {
   GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
   TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	Terminal term = makeKeyPad();
   // Replace terminal by two terminals. One for standard output and
   // one to echo entered digits.   
   Coordinate c = term.bottomRight;
   c.y = c.y - term.font->Height - 1; 
   stdoutTerm = genTerm(term.topLeft, c, term.bgColor, term.fgColor, term.font);
   c = term.topLeft;
   c.y = term.bottomRight.y - term.font->Height;
   echoTerm = genTerm(c, term.bottomRight, BLUE, YELLOW, term.font);   
   clearEchoTerm();
   clearStdout();
}

void printToEchoLine(char c){
   char buf[2] = {'\0', '\0'};
   buf[0] = c;
   printTerm(buf, &echoTerm);
}

void setErrMode(void) {
	clearTerm(&stdoutTerm);
	setTextColorTerm(RED, &stdoutTerm);
}

void setNormalMode(void) {
	clearTerm(&stdoutTerm);
	setTextColorTerm(BLACK, &stdoutTerm);
}

bool isBottomLine(void) {
	 return getCurRow(&stdoutTerm) + 1 == getNoOfRows(&stdoutTerm);
}

// EOF
