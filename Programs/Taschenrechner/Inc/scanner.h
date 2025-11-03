/**
  * @file scanner.h
  * @author Franz Korf, HAW Hamburg 
  * @date Mar 2016
  * @brief Header file of input module. 
  */

#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

/*
 ****************************************************************************************
 * @brief : This function returns the next token, defined in token.h
 *
 * @return Next token will be returned. In case of an error the UNEXPTECTED token will
 *         be returned.
 ****************************************************************************************/
T_token nextToken(void);

#endif /* SCANNER_H */
// EOF
