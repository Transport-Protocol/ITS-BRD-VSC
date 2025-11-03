/**
  * @file token.h
  * @author Franz Korf, HAW Hamburg 
  * @date Mar 2016
  * @brief This file stores all token returned by the scanner. 
  */

#ifndef TOKEN_H
#define TOKEN_H

// All token for input and stack commands
#define NUMBER     'n'    //!< Token for an int number 
#define PLUS       '+'    //!< Token for + operator 
#define MINUS      '-'    //!< Token for - operator 
#define MULT       '*'    //!< Token for * operator 
#define DIV        '/'    //!< Token for / operator 
#define PRT        'p'    //!< Token for print command 
#define SWAP       'r'    //!< Token for swap command 
#define PRT_ALL    'P'    //!< Token for print total stack command
#define CLEAR      'C'    //!< Token for clear command
#define DOUBLE     'd'    //!< Token for double top of stack command 
#define ENTER      ' '    //!< Token for ENTER button
#define UNEXPECTED 'U'    //!< Token for an unexpected command / button
#define OVERFLOW   'O'    //!< Overflow during input of a number

typedef struct{   //!< This structure stores a token
    char tok;
    int  val; // value of NUMBER token
} T_token;

#endif /* TOKEN_H */
// EOF
