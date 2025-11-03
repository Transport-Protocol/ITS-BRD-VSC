/**
 * @file scanner.c
 * @author Franz Korf, HAW Hamburg 
 * @date Mar 2016
 * 
 * @brief This module implements a simple scanner for keypad input.
 */
 
#include "scanner.h"
#include "display.h"
#include "keypad.h"
#include "token.h"

/*
 ****************************************************************************************
 * @brief : read next character from Touch Pad 
 *
 *  @return Character read from touch pad. 
 ****************************************************************************************/
inline static char nextChar(void) {
    return getKeyPadInput();
}

T_token nextToken(void) {
   // This scanner needs a lookahead of 1 to detect the end of a number token.
	// ' ' / ENTER will be handled as whitespace
   static char c = ENTER;  // next character according to lookahead
   clearEchoTerm();
   while (ENTER == c) { c = nextChar();};
		
	T_token erg = {UNEXPECTED, 0};
   // analyse input character
	switch (c) {
      case PLUS: case MINUS: case MULT:    case DIV:
      case PRT:  case SWAP:  case PRT_ALL: case DOUBLE:
		case CLEAR:
         erg.tok = c; 
			c = ENTER;
			break;
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9': 
         erg.tok = NUMBER; // scan a number
         while (('0' <= c) && (c <= '9')) {
				printToEchoLine(c);
				erg.val = erg.val * 10 + (c - '0');
				if (erg.val < 0) { // Overflow 
               erg.tok = OVERFLOW;
               erg.val = 0;
				   return erg;
			   }				 
            c = nextChar();
         }
			break;
      default: // unexpected input
			c = ENTER;
   }	
	return erg;
}
// EOF
