/**
  * @file rechnen.c
  * @author Esmat Rabaki, Raphael Pfeiffer
  * @date Okt 2025
  * @brief Dieses Modul stellt eine einfache Stack-Verwaltung für Ganzzahlen bereit.
  * Es unterstützt grundlegende Operationen wie push, pop, peek, 
  * sowie zusatzfunktionen wie clear_stack, duplicate, swap und output_entire_stack.
  *
  */
  
#include "stack.h"
#include "token.h"
#include "display.h"
#include <limits.h>
#include "umwandeln.h"

/**
 * @brief Führt die im Token  Operation aus.
 *
 * @param token Token, das den Operator und den Wert enthält.
 * @return Bei bei 0 ist es Erfolg, -1 ist dann  Fehler.
 */
 
 
int rechnen(T_token token){
    int a, b, result;

    switch (token.tok)
    {
        case NUMBER:
            if (push(token.val) == -1) 
            {
                setErrMode();
                printStdout("FEHLER: Stack overflow.\n");
                return -1;
            }
            return 0;

        case PLUS:
            if (pop(&a) != 0 || pop(&b) != 0) 
            {
                setErrMode();
                printStdout("FEHLER: Stack underflow bei Addition.\n");
                return -1;
            }

            // Overflow-Check für Addition
            if ((a > 0 && b > INT_MAX - a) || (a < 0 && b < INT_MIN - a)) 
            {
                setErrMode();
                printStdout("FEHLER: Integer Overflow bei Addition.\n");
                return -1;
            }

            result = b + a;
            push(result);
            return 0;

        case MINUS:
            if (pop(&a) != 0 || pop(&b) != 0)
            {
                setErrMode();
                printStdout("FEHLER: Stack underflow bei Subtraktion.\n");
                return -1;
            }

            // Overflow-Check für Subtraktion
            if ((a < 0 && b > INT_MAX + a) || (a > 0 && b < INT_MIN + a)) 
            {
                setErrMode();
                printStdout("FEHLER: Integer Overflow bei Subtraktion.\n");
                return -1;
            }

            result = b - a;
            push(result);
            return 0;

        case MULT:
            if (pop(&a) != 0 || pop(&b) != 0) 
            {
                setErrMode();
                printStdout("FEHLER: Stack underflow bei Multiplikation.\n");
                return -1;
            }

            if (a == 0 || b == 0) {
                push(0);
                return 0;
            }

            // Overflowprüfung Multiplikation
            if ((a > 0 && b > INT_MAX / a) || (a < 0 && b < INT_MIN / a) ) 
            {
                setErrMode();
                printStdout("FEHLER: Integer Overflow bei Multiplikation.\n");
                return -1;
            }

            result = b * a;
            push(result);
            return 0;

        case DIV:
            if (pop(&a) != 0 || pop(&b) != 0) 
            {
                setErrMode();
                printStdout("FEHLER: Stack underflow bei Division.\n");
                return -1;
            }

            if (a == 0) 
            {
                setErrMode();
                printStdout("FEHLER: Division durch Null.\n");
                return -1;
            }

            result = b / a;
            push(result);
            return 0;

        case PRT:
            clearStdout();
            if (peek(&result) != 0) {
                setErrMode();
                printStdout("FEHLER: Stack ist leer.\n");
                return -1;  
            }
            integer_to_string(result);
            return 0;

        case PRT_ALL:
        {
            clearStdout();
            int *stack;
            int count;
            
            if (output_entire_stack(&stack, &count) != 0) {
                setNormalMode();
                printStdout("stack ist leer.\n");
                return -1;
            }
            
            setNormalMode();
            for (int i = count - 1; i >= 0; i--) 
            {
                integer_to_string(stack[i]);
            }
            return 0;
        }

        case CLEAR:
            clear_stack();
            return 0;

        case DOUBLE:
            clearStdout();
            if (duplicate() != 0) 
            {
                setErrMode();
                printStdout("FEHLER: Stack underflow beim Duplizieren (min. 1 Element benötigt).\n");
                return -1;
            }
           
            peek(&result);
            integer_to_string(result);
            return 0;

        case SWAP:
            clearStdout();
            if (swap(a, b) != 0) 
            {
                setErrMode();
                printStdout("FEHLER: Stack underflow beim Tauschen (min. 2 Elemente benötigt).\n");
                return -1;
            }
            integer_to_string(a);
            integer_to_string(b);   
            return 0;

        default:
            setErrMode();
            printStdout("FEHLER: Unbekannter Operator.\n");
            return -1;
    }
}
