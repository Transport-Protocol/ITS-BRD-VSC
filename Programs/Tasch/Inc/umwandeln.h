/**
 * @file umwandeln.h
 * @brief Header-Datei für   Funktionen zur Umwandlung von Ganzzahlen in Strings und deren Display-Ausgabe.
 *
 *
 * @date Oktober 2025
 * @authors Esmat Rabaki, Raphael Pfeiffer, HAW Hamburg
 *
 */

#ifndef UMWANDELN_H
#define UMWANDELN_H

#include <stdbool.h>  ///< Für bool, true, false

/**
 * @brief Wandelt eine Ganzzahl in einen String um 
 *
 * @param num Die Zahl, die umgewandelt werden soll.
 */
int integer_to_string(int num);

/**
 * @brief Gibt einen String rückwärts aus und für die korrekte Display-Ausgabe.
 *
 * @param str Zeiger auf den String, der ausgegeben werden soll.
 * @param length Länge des Strings
 */
void reverse_string(const char str[], int length);

#endif // UMWANDELN_H
