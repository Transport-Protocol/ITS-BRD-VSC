/**
 * @file stack.h
 * @brief Schnittstelle für das Stack-Modul.
 *
 * Dieses Modul stellt eine einfache Stack-Verwaltung für Ganzzahlen bereit.
 * Es unterstützt grundlegende Operationen wie push, pop, peek, 
 * sowie Zusatzfunktionen wie clear_stack, duplicate, swap und output_entire_stack.
 *
 * @date Okt  2025
 * @authors Esmat Rabaki und Raphael Pfeiffer  
 */

 
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>   ///< Für bool, true, false

/** @def STACK_SIZE
 *  @brief Maximale Größe des Stacks.
 */
#define STACK_SIZE 10

// ===========================================================
// Funktionsprototypen
// ===========================================================

/**
 * @brief Initialisiert den Stack.
 *
 */
void stack_init(void);

/**
 * @brief Legt eine Zahl auf den Stack.
 *
 * Fügt das übergebene Element oben auf dem Stack hinzu.
 *
 * @param value Die Zahl, die auf den Stack gelegt werden soll.
 * @return int 0 bei Erfolg, -1 bei Overflow.
 */

int push(int data);

/**
 * @brief Holt das oberste Element vom Stack herunter.
 *
 * Liest das oberste Element und entfernt es vom Stack.
 *
 * @param data ist das wert was wir von stack holen
 * @return int 0 bei Erfolg, -1 bei Underflow.
 */
int pop(int *data);

/**
 * @brief Zeigt das oberste Element an, ohne es zu entfernen.
 * @param data ist das wert was auf der oberste von stack ist
 */
int peek(int *data);

/**
 * @brief Löscht den gesamten Stack.
 * Setzt den Stack-Zeiger zurück und entfernt alle gespeicherten Werte.
 */
void clear_stack(void);

/**
 * @brief Dupliziert den obersten Wert auf dem Stack.
 *
 * Wenn mindestens ein Wert vorhanden ist, wird der oberste Wert kopiert und erneut oben abgelegt.
 */
int duplicate(void);

/**
 * @brief Vertauscht die beiden obersten Werte auf dem Stack.
 *@param valA Der erste Wert zum Vertauschen.
 *@param valB Der zweite Wert zum Vertauschen.
 * Wenn mindestens zwei Werte vorhanden sind, werden sie in ihrer Reihenfolge vertauscht.
 */
int swap(int valA, int valB);

/**
 * @brief Gibt den gesamten Stack-Inhalt auf dem Display aus.
 *@param stack_data Zeiger auf das Stack-Array.
 *@param stack_size Zeiger auf die aktuelle Größe des Stacks.
 * Alle gespeicherten Werte werden von oben nach unten angezeigt.
 */
int output_entire_stack(int **stack_data, int *stack_size);

#endif // STACK_H
