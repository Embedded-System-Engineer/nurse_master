/* 
 * File:   switchCallbacks.h
 * Author: hassa
 *
 * Created on May 2, 2023, 2:48 AM
 */

#ifndef SWITCHCALLBACKS_H
#define	SWITCHCALLBACKS_H
#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchIDCallBack >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchIDCallBack                                                         |
 | < @Description       : mcall back run in any Option system                                           |      
 | < @return            : 0 is runing , 1 is done                                                       |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchIDCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RoomIdCallBack >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void RoomIdCallBack                                                        |
 | < @Description       : write room id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t RoomIdCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchRoomIpCallBack >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchRoomIpCallBack                                                        |
 | < @Description       : write switch room Ip in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchRoomIpCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchDeActiveByIp >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchDeActiveByIp                                                        |
 | < @Description       : write switch id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchActiveByIp();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Display1IPReuest >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Display1IPReuest                                                        |
 | < @Description       : write display 1 id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t Display1IPReuest();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Display1IPReuest >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Display1IPReuest                                                        |
 | < @Description       : write display 1 id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t Display2IPReuest();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Display1IPReuest >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Display1IPReuest                                                        |
 | < @Description       : write display 1 id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t Display3IPReuest();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Display1IPReuest >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Display1IPReuest                                                        |
 | < @Description       : write display 1 id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t Display4IPReuest();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < sw1Type >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void sw1Type                                                                 |
 | < @Description       : Frist switch type                                                            |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t sw1Type();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchBuzzerState >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchBuzzerState                                                           |
 | < @Description       : switch buzzer state                                                     |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchBuzzerState() ;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchDisabledSystem >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchDisabledSystem                                                           |
 | < @Description       : switchDisabledSystem                                                     |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchDisabledSystem();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < sw2Type >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void sw2Type                                                                 |
 | < @Description       : second switch type                                                            |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t sw2Type();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < sw3Type >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void sw3Type                                                                 |
 | < @Description       : Threed switch type                                                            |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t sw3Type();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchBuzzerTime >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchBuzzerTime                                                        |
 | < @Description       : switch buzer time                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchBuzzerTime();
#endif	/* SWITCHCALLBACKS_H */

