#include "operations.h"
#include "stack.h"
#include "limits.h"
#include "token.h"
#include "msg_handler.h"

static int num_a;
static int num_b;
static int state;

int add(void) {
    if  (  (num_a > 0) && (num_b > 0) && (num_b > INT_MAX - num_a)
        || (num_a < 0) && (num_b < 0) && (num_b < INT_MIN - num_a)
        ) {
            return -3;
        }
    int result = num_b + num_a;
    stackPush(result);
    return 0;
}

int subtract(void) {
    if  (  (num_a < 0) && (num_b > -1) && (num_b > INT_MAX + num_a)
        || (num_a > 0) && (num_b < -1) && (num_b < INT_MIN + num_a)
        ) {
            return -3;
        }
    int result = num_b - num_a;
    stackPush(result);
    return 0;
}

int multiply(void) {
    if  (  (num_a > 1) && (num_b > 1) && (num_b > INT_MAX / num_a)
        || (num_a < 0) && (num_b < 0) && (num_b < INT_MAX / num_a)    // > wird zu < wegen Teilung durch Minuszahl

        || (num_a > 1) && (num_b < 0) && (num_b < INT_MIN / num_a)
        || (num_a < 0) && (num_b > 1) && (num_b > INT_MIN / num_a)    // < wird zu > wegen Teilung durch Minuszahl
        ) {
            return -3;
        }
    int result = num_b * num_a;
    stackPush(result);
    return 0;
}

int divide(void) {
    if (num_a == 0) {
        return -4;
    }
    if ( (num_b == INT_MIN) && (num_a == -1) ) {
        return -3;
    }
    int result = num_b / num_a;
    stackPush(result);
    return 0;
}

int calculate(char token) {
    state = stackPop(&num_a);
    if (state != 0) { return state; }
    state = stackPop(&num_b);
    if (state != 0) { return state; }

    switch (token) {
        case PLUS:
            state = add(); break;
        case MINUS:
            state = subtract(); break;
        case MULT:
            state = multiply(); break;
        case DIV:
            state = divide(); break;
        case SWAP:
            stackPush(num_a);
            stackPush(num_b);
            state = 0;
            break;
        default:
            state = -5;
    }
    return state;
}

int duplicate(void) {
    state = stackPop(&num_a);
    if (state != 0) { return state; }

    stackPush(num_a);
    stackPush(num_a);
    return 0;
}

void printOps(char token) {
    int depth = 0;
    
    state = stackPeek(&num_a, depth);
    if (state != 0) { printMessage(state); return; }

    printNumber(num_a);
    
    if (token == PRT_ALL) {
        depth++;
        state = stackPeek(&num_a, depth);

        while (state == 0) {
            printNumber(num_a);
            depth++;
            state = stackPeek(&num_a, depth);
        }
    }
}

//EOF
