/**
  * @file display.h
  * @author Franz Korf, HAW Hamburg 
  * @date Mar 2016
  * @brief Header file of display module. 
  */

#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdbool.h>

/*
 ****************************************************************************************
 *  @brief      This function initialize the output function.
 *
 *  @return     void 
 ****************************************************************************************/
void initDisplay(void);

/*
 ****************************************************************************************
 *  @brief      This function sets error mode colors for stdout terminal.
 *
 *  @return     void 
 ****************************************************************************************/
extern void setErrMode(void);

/*
 ****************************************************************************************
 *  @brief      This function sets normal mode colors for stdout terminal.
 *
 *  @return     void 
 ****************************************************************************************/
extern void setNormalMode(void);

/*
 ****************************************************************************************
 *  @brief      This function prints a string to stdout terminal.
 *
 *  @param      msg The value that will be printed on on the terminal.
 *
 *  @return     void 
 ****************************************************************************************/
extern void printStdout(char * msg);

/*
 ****************************************************************************************
 *  @brief      This function prints a character to echo terminal.
 *
 *  @param      c The character to be printed.
 *
 *  @return     void 
 ****************************************************************************************/
extern void printToEchoLine(char c);

/*
 ****************************************************************************************
 *  @brief      This function clears echo terminal.
 *
 *  @return     void 
 ****************************************************************************************/
extern void clearEchoTerm(void);

/*
 ****************************************************************************************
 *  @brief      This function clears stdout terminal.
 *
 *  @return     void 
 ****************************************************************************************/
extern void clearStdout(void);

/*
 ****************************************************************************************
 *  @brief      If the current line of stdout terminal is its bottom line, this 
 *              function returns true.
 *
 *  @return     true <=> current line == bottom line 
 ****************************************************************************************/
extern bool isBottomLine(void);

#endif /* OUTPUT_H */
// EOF
