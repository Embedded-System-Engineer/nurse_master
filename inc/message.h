/* 
 * File:   message.h
 * Author: hassa
 *
 * Created on February 26, 2023, 9:24 PM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "Memory.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WriteMessage  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WriteMessage                                                   |
 | < @Description       : Write Message From message Buffer                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void WriteMessage(uint8_t lin, uint8_t Index);

/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintMessage  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintMessage                                                       |
  | < @Description       : Print Message Into Buffer Array                                                    |
  |                      : PrintMessage                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t appPrintMessage(uint8_t *buf, uint8_t start, uint8_t MsgIndex);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < messageCompareString  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  messageCompareString                                                      |
  | < @Description       : compare buffer with string                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t messageCompareString(uint8_t *buf, uint8_t Index, uint8_t length);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < messageCompareString  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  messageCompareString                                                      |
  | < @Description       : compare buffer with string                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t getMessageLength(uint8_t Index);
#endif	/* MESSAGE_H */

