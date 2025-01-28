/* 
 * File:   Configuration.h
 * Author: hassa
 *
 * Created on April 22, 2023, 11:23 PM
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H
#include "appRes.h"


/*
 --------------------------------------------------------------------------------------------------------
 |                                 <ConfigurationInit>                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void ConfigurationInit                                                      |
 | < @Description         : get Init all data in this File                                              |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void ConfigurationInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveConfiguration>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveConfiguration                                                    |
 | < @Description         : save serail Number On extranleeprom section this function reboot system              |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void OnSaveSerialCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <noSerial>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void noSerial                                                               |
 | < @Description         : system have serial or not                                                   |   
 | < @return              : 0 is not have a serial and  1 system have a serial                          |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemIsSerial();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SystemLoadSerail>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void SystemLoadSerail                                                       |
 | < @Description         : load serial number from eeprom                                              |   
 | < @return              : void                                                                         |          
 --------------------------------------------------------------------------------------------------------
 */
void SystemLoadSerail(SystemSerial_t *serail);
#endif	/* CONFIGURATION_H */

