/* 
 * File:   loadip.h
 * Author: hassa
 *
 * Created on June 1, 2023, 3:08 AM
 */

#ifndef LOADIP_H
#define	LOADIP_H
#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  loadIpCallBack>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   loadIpCallBack                                                         |
 | < @Description       : run this callback to active data                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t loadIpCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  loadIpGetIpShowWithIp>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   loadIpGetIpShowWithIp                                                      |
 | < @Description       : Get Message                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void loadIpGetIpShowWithIp(uint8_t Ip);
#endif	/* LOADIP_H */

