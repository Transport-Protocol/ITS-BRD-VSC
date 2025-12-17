/**
 * @file umwandeln.c
 * @authors Esmat Rabaki undRaphael Pfeiffer  
 * @brief Enthält Funktionen zur Umwandlung von Integer-Werten
 * in Strings und deren Anzeige auf dem Display.
 *
 * @date Okt  2025
 */

#include "display.h"
#include <stdbool.h> // Für den booleschen Wert
#include <stddef.h> // Für NULL



static char str[12]; 

/**
 * @brief Gibt einen String in umgekehrter Reihenfolge auf dem Display aus.
 * @param str Zeiger auf den String, der umgekehrt ausgegeben werden soll.
 * @param length Länge des Strings 
 */
void reverse_string(char str[], int length) {
    if (str == NULL || length <= 0) return;
    
    char tmp[length+1];  // Nutze die gleiche Größe wie str
    int s = 0;
    
   
    for (int t = length - 1; t >= 0; t--) {
        tmp[s++] = str[t];
    }
    tmp[s] = '\0';
    printStdout(tmp);
} 

/**
 * @brief Wandelt eine Ganzzahl in einen String um.
 * @param num Der zu konvertierende Ganzzahlwert.
 *
 */

int integer_to_string(int num) {

    int i = 0;
    bool negative = false;
    
     // 1. Sonderfall Null
    if (num == 0) 
    {
        str[i++] = '0';   //Konvertiere die Ziffer
        str[i] = '\0';    //String-Ende
        reverse_string(str, i);
        return 0;
    }   

    // Sonderfall INT_MIN
    if (num == -2147483648) {
        printStdout("-2147483648");
        return 0;
    }

    // Sonderfall negative Zahlen 
    if (num < 0) 
    {
        negative = true;
        num = num * (-1); // Arbeite mit dem positiven Wert
    }
    // 2. Konvertiere jede Ziffer in den String
    while (num != 0 ) 
    {
        int digit = num % 10;
        str[i++] = digit + '0';
        num = num / 10;  // Entfernt die letzte Ziffer
    }

    //Füge das Minuszeichen hinzu, falls nötig
    if (negative) 
    {
       str[i++] = '-';
    }

    //String-Ende (Null-Terminator)
    str[i] = '\0';
   
     printStdout(" \n"); // leer zwischen zahlen
     
    // String umkehren, da Ziffern in umgekehrter Reihenfolge gespeichert wurden
    reverse_string(str, i);
    return i;

}




