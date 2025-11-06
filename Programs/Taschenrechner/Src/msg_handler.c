#include "msg_handler.h"
#include "display.h"
#include "limits.h"
#include "token.h"
#include "scanner.h"

int sizeofInt(int value) {
    int count = 2;    // Allocate for '\n' + '\0'
    if (value <= 0) { count++; }    // Allocate for '0' || '-'
    while (value != 0) {
        count++;
        value = value / 10;
    }
    return count;
}

void printNumber(int value) {
    int i = sizeofInt(value);
    char str[i]; i--;

    str[i] = '\0'; i--;
    str[i] = '\n'; i--;

    if (value == 0) { str[0] = '0'; }
    else {
        if (value < 0) {
            if (value == INT_MIN) {
                str[i] = '8';
                value = value / 10;
                i--;
            }
            str[0] = '-';
            value = -value;
        }
        
        while (value > 0) {
            str[i] = value % 10 + '0';
            value = value / 10;
            i--;
        }
    }
    
    if (isBottomLine()) {
        printStdout("Mit P fortfahren...");
        T_token input = nextToken();
        while (input.tok != PRT_ALL) { input = nextToken(); }
        clearStdout();
    }
    printStdout(str);
}

void printMessage(int num) {
    switch (num) {
        case 1:
            printStdout("Stack leer."); break;
        case -1:
            printStdout("Stack Overflow!\n(Reset mit C)"); break;
        case -2:
            printStdout("Stack Underflow!\n(Reset mit C)"); break;
        case -3:
            printStdout("Arithmetic Overflow!\n(Reset mit C)"); break;
        case -4:
            printStdout("Durch 0 geteilt!\n(So moege Sie der\nBlitz treffen.)"); break;
        case -5:
            printStdout("Unexpected Input!\n(Reset mit C)");
    }
}

//EOF
