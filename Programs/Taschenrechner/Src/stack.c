#include "stack.h"
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int array[MAX_SIZE];
    int top;
} Stack;

static Stack stack = {.top = -1};

bool isEmpty(void) {
    return stack.top == -1;
}

bool isFull(void) {
    return stack.top == (MAX_SIZE - 1);
}

int stackPush(int value) {
    if (isFull()) { return -1; }

    stack.top++;
    stack.array[stack.top] = value;
    return 0;
}

int stackPop(int *value) {
    if (isEmpty()) { return -2; }

    *value = stack.array[stack.top];
    stack.top--;
    return 0;
}

int stackPeek(int *value, int depth) {
    if (isEmpty()) { return 1; }

    int index = stack.top - depth;
    if ( (index < 0) || (stack.top < index) ) { return -5; }

    *value = stack.array[index];
    return 0;
}

void clearStack(void) {
    stack.top = -1;
}

// EOF
