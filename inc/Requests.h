/* 
 * File:   Requests.h
 * Author: hassa
 *
 * Created on April 19, 2023, 12:46 PM
 */

#ifndef REQUESTS_H
#define	REQUESTS_H
#include "appRes.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < StartConfig >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void StartConfig                                                            |
 | < @Description       : save state into save unit                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t StartConfig(uint8_t address, uint8_t Request);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < ConfigDisplay >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void ConfigDisplay                                                            |
 | < @Description       : Request the State to update room state                                        |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ConfigDisplay(stDisplayConfig_t *display, uint8_t Ip);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < PowerOnRequest >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PowerOnRequest                                                           |
 | < @Description       : request data from save unit                                                   |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ConfigRoom(stRoomConfig_t *room, uint8_t Ip);


/*
 --------------------------------------------------------------------------------------------------------
 |                                 < External Functions >                                    |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RequestesInit >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void RequestesInit                                                            |
 | < @Description       : Init all Var in this file                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void RequestesInit();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RegisterAfterError >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void RegisterAfterError                                                            |
 | < @Description       : after error action                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void RegisterAfterError(pFunc_t Error);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < LoadIpRequest >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void LoadIpRequest                                                            |
 | < @Description       : Load Ip To Point                                                              |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t LoadIpRequest(uint8_t DA, uint8_t Ip);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < CommErrorSwConfigORSuceessCencel >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void CommErrorSwConfigORSuceessCencel                                                            |
 | < @Description       : system Error Or Sucess Sw Config Frame                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void CommErrorSwConfigORSuceessCencel();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < CommErrorDisplayConfigORSuceessCencel >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void CommErrorDisplayConfigORSuceessCencel                                                            |
 | < @Description       : system Error Or Sucess Sw Config Frame                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void CommErrorDisplayConfigORSuceessCencel();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SWOnReq>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void SWOnReq                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SWOnReq(uint8_t RequestType, uint8_t PointAddress, uint8_t Ip, stCallPointConfig_t *config, stCallPointData_t *Data, bool error_messgae);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <swReqData>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void swReqData                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <swReqData>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void swReqData                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t swReqData(uint8_t PointAddress, uint8_t Ip, uint8_t State);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SWOnReq>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void SWOnReq                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t DisplayOnReq(uint8_t RequestType, uint8_t PointAddress, uint8_t Ip, stDisplayConfig_t *config);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < AcceptAllRequest >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void AcceptAllRequest                                                         |
 | < @Description       : Request Frame This Frame is borad casting for all                             |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t AcceptPointRequest(uint8_t ip);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < ResForConfig >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void ResForConfig                                                             |
 | < @Description       : Response for Start Flash with select address                                  |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t updateDisplayRequest(QueueItem *item, uint8_t type);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < update displays requests >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void AcceptAllRequest                                                         |
 | < @Description       : Request Frame This Frame is borad casting for all                             |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ClearDisplay();
#endif	/* REQUESTS_H */

