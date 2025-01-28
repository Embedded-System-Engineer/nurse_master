/* 
 * File:   SystemGenralOption.h
 * Author: hassa
 *
 * Created on May 30, 2023, 5:58 AM
 */

#ifndef SYSTEMGENRALOPTION_H
#define	SYSTEMGENRALOPTION_H
#include "appRes.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < OptionSystemInit >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void OptionSystemInit                                                         |
 | < @Description       : init variables in all files                                                   |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void OptionSystemInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < systemOptionRegisterData >                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void systemOptionRegisterData                                                 |
 | < @Description       : define system Option by three variable                                        |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void systemOptionRegisterData(uint8_t MAX, uint8_t StartPos, uint8_t startMessageIndex) ;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemGetCurrentOption >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemGetCurrentOption                                                       |
 | < @Description       : get current option                                                      |      
 | < @return            : option Index                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemGetCurrentOption();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < systemOptionCallBack >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void systemOptionCallBack                                                     |
 | < @Description       : mcall back run in any Option system                                           |      
 | < @return            : 0 is run , 1 is cencel , 2 is Enter                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t systemOptionCallBack();

#endif	/* SYSTEMGENRALOPTION_H */

