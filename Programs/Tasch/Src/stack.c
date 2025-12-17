/**
 * @file stack.c
 * @author Esmat Rabaki und Raphael Pfeiffer
 * @date Oktober 2025
 * @brief Implementierung eines einfachen Integer-Stacks.
 *
 * Dieses Modul kapselt die Stack-Datenstruktur für Ganzzahlen und bietet 
 * Operationen wie push pop, peek, clear, duplicate, swap.
 */
 
 
#include "stack.h"
#include "display.h"


#define SIZE 10

static int stack[SIZE];
static int top = -1; 


/**
 * @brief Prüft, ob der Stack voll ist.
 * 
 * @return int 1, wenn der Stack voll ist, sonst 0.
 */
int isFull(void) 
{ 
    return top == SIZE - 1; 
}

/**
 * @brief Prüft, ob der Stack leer ist.
 */
int isEmpty(void) 
{ 
    return top == -1; 
}

/**
 * @brief Fügt ein neues Element oben auf den Stack hinzu.
 *
 * @param data Wert, der auf den Stack gelegt wird.
 * @return int 0 bei Erfolg, -1 bei Stack Overflow.
 */
int push(int data) 
{
    if (isFull()) 
    {
        return -1;
    }
    stack[++top] = data; 
    return 0;
}

/**
 * @brief Entfernt das oberste Element des Stacks.
 * @param data ist das wert was wir von stack holen
 * @return int 0 bei Erfolg, -1 bei Stack Underflow.
 */

int pop(int *data) 
{
    if (isEmpty()) 
    {
        return -1; 
    }
    *data = stack[top--]; 
    return 0;
}

/**
 * @brief Gibt das oberste Element aus, ohne es zu entfernen.
 *@param data ist das wert was auf dem oberste von stack ist
 * @return int 0 bei Erfolg, -1 wenn der Stack leer ist.
 */

int peek(int *data) 
{
    if (isEmpty()) {
        return -1;
    }
     *data = stack[top]; 
    return 0;
}

/**
 * @brief Löscht alle Elemente des Stacks.
 */
void clear_stack(void) 
{
    if (isEmpty()) {
        setNormalMode();
        printStdout("Stack ist bereits leer.\n");
        return;
    }
    top = -1;
    clearStdout();
}

/**
 * @brief Dupliziert das oberste Element des Stacks.
 * @return int 0 bei Erfolg, -1 bei Stack Overflow oder wenn der Stack leer ist.
 */
int duplicate(void) 
{
    if (isEmpty()) {
        return -1;
    }
    int v = stack[top];
    push(v);
    return 0;
}

/**
 * @brief Vertauscht die beiden obersten Elemente des Stacks.
 * @return int 0 bei Erfolg, -1 wenn der Stack weniger als zwei Elemente hat.    
 *@param valA ist das oberste wert von stack
 *@param valB ist das zweit oberste wert von stack
 */
int swap(int valA, int valB) 
{
    if (top < 1) 
    {
        return -1;
    }
    valA = stack[top]; 
    valB = stack[top - 1]; 

    stack[top] = valB;
    stack[top - 1] = valA;
    return 0;
}

/**
 * @brief Gibt den gesamten Inhalt des Stacks auf dem Display aus.
 * 
 * @param stack_data Zeiger auf ein Array, das die Stack-Daten enthält.
 * @param stack_size Zeiger auf eine Variable, die die Größe des Stacks enthält.
 * @return int 0 bei Erfolg, -1 wenn der Stack leer ist.
 */
int output_entire_stack(int **stack_data, int *stack_size)
{
    if (isEmpty()) {

        return -1;
    }
    *stack_data = stack;
    *stack_size = top + 1;
    return 0;
}