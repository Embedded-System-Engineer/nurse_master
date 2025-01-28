/* 
 * File:   type3DigitOr5Digit.h
 * Author: hassa
 *
 * Created on April 30, 2023, 8:12 PM
 */

#ifndef TYPE3DIGITOR5DIGIT_H
#define	TYPE3DIGITOR5DIGIT_H
#include "appRes.h"

#define TYPE_3DIGIT   0
#define TYPE_5DIGIT   1
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeInit>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeInit                                                            |
 | < @Description       : Init all data Into file                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void TypeInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeCallBack>                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeCallBack                                                           |
 | < @Description       : call this function when write uint8 data or uint16Data                        |                                                  |                                                           
 | < @return            : retun Case if 0 is ruuning , 1 is cencel , 2 is Enter                         |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t TypeCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  RegisterTypeAs3DigitOr5Digit>                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   RegisterTypeAs3DigitOr5Digit                                           |
 | < @Description       : define max digit show in LCD nad casting to                                   |       
 | < @Param MaxDigit    : max Digit show in LCD                                                         |
 | < @Param StartShow   : Inialize the Edit data                                                        |                                                             
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void RegisterTypeAs3DigitOr5Digit(uint8_t MaxDigit, uint16_t StartshowData);

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeGetValue8Bit >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeGetValue8Bit                                                           |
 | < @Description       : get type in LCD with 3 Digit                                            |                                                  |                                                           
 | < @return            : return 0 to 255                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t TypeGetValue8Bit();

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeGetValue16Bit >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeGetValue16Bit                                                           |
 | < @Description       : get type in LCD with 5 Digit                                            |                                                  |                                                           
 | < @return            : return 0 to 2^16 -1                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
uint16_t TypeGetValue16Bit() ;

#endif	/* TYPE3DIGITOR5DIGIT_H */

