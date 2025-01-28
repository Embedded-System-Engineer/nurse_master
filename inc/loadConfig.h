/* 
 * File:   loadConfig.h
 * Author: mosta
 *
 * Created on May 8, 2023, 9:03 PM
 */

#ifndef LOADCONFIG_H
#define	LOADCONFIG_H
#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < LoadConfigRequestFromMem >                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void LoadConfigRequestFromMem                                            |
 | < @Description       : load number of byte of of ip is contains a new config
 | < @Param ConfigData   : active Ip to Load Config                                                    |                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void LoadConfigRequestFromMem(uint8_t *ConfigData);

#endif	/* LOADCONFIG_H */

