/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "init.h"
#include "display.h"
#include "scanner.h"
#include "token.h"
#include "stack.h"
#include "operations.h"
#include "msg_handler.h"

static T_token input = {UNEXPECTED, 0};
static int state = 0;

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards	
	initDisplay();    // Initialisierung des Displays
	
	// Test in Endlosschleife
	while(1) {
		input = nextToken();

		switch (input.tok) {
			case NUMBER:
				state = stackPush(input.val); break;
			
			case OVERFLOW:
				state = -1; break;
			
/* 			case PLUS:
				state = add(); break;

			case MINUS:
				state = subtract(); break;

			case MULT:
				state = multiply(); break;

			case DIV:
				state = divide(); break;

			case DOUBLE:
				state = duplicate(); break;

			case SWAP:
				state = roleswap(); break; */

			case PRT: case PRT_ALL:
				clearStdout();
				printOps(input.tok); break;

			case CLEAR:
				clearStack();
				clearStdout(); break;

			case UNEXPECTED:
				state = -5;
		}

		if (state != 0) {
			setErrMode();
			printMessage(state);

			while (input.tok != CLEAR) { input = nextToken(); }

			clearStack();
			setNormalMode();
			state = 0;
		}
	}
}

// EOF
