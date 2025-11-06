/**
  ******************************************************************************
  * @file    main.c
  * @author  René Rudzki
  * @brief   RPN Taschenrechner über Touch-Display des ITS-Boards.
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
	initITSboard();    // Initialisierung des ITS-Boards	
	initDisplay();    // Initialisierung des Displays
	
	// Ausführung in Endlosschleife
	while(1) {
		input = nextToken();

		switch (input.tok) {
			case NUMBER:
				state = stackPush(input.val); break;
			
			case OVERFLOW:
				state = -1; break;
			
			case PLUS: case MINUS: case MULT: case DIV: case SWAP:
				state = calculate(input.tok); break;
			
			case DOUBLE:
				state = duplicate(); break;

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
