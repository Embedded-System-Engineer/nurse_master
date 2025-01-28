/* 
 * File:   selectIp.h
 * Author: hassa
 *
 * Created on April 30, 2023, 9:07 PM
 */

#ifndef SELECTIP_H
#define	SELECTIP_H
#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < selectIpInit >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void selectIpInit                                                             |
 | < @Description       : initall variables of the f                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void selectIpInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < selectIpCallback >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void selectIpCallback                                                         |
 | < @Description       : run at any selct Ip System                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t selectIpCallback();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCurrentIpSelect >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void getCurrentIpSelect                                                       |
 | < @Description       : get current Ip Select From User                                               |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getCurrentIpSelect();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < InvalidIpMesssage >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InvalidIpMesssage                                                             |
 | < @Description       : get Ip is Valid Or Not and write Message                                                   |      
 | < @return            : 0 write Error Message , 1 Ip is valid                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t InvalidIpMesssage(uint16_t Ip, uint8_t Max);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SetCurrentIpSelect >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SetCurrentIpSelect                                                       |
 | < @Description       : set value of the currentIp                                              |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void SetCurrentIpSelect(uint8_t Ip);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCurrentIpSelect >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void getCurrentIpSelect                                                       |
 | < @Description       : get current Ip Select From User                                               |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void resetCurrentIP();

#endif	/* SELECTIP_H */

