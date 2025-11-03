#include "operations.h"
#include "stack.h"
#include "msg_handler.h"

void printOps(char all) {
    int value;
    int depth = 0;
    int state = stackPeek(&value, depth);

    if (state != 0) { printMessage(state); return; }
    
    printNumber(value);
    
    if (all == 'P') {
        depth++;
        state = stackPeek(&value, depth);

        while (state == 0) {
            printNumber(value);

            depth++;
            state = stackPeek(&value, depth);
        }
    }
}
