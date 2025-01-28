
#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Variables>                                                |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t gu8RequestDisplay;
/*
 * < @var Function State
 */
static uint8_t gu8ReqFunState;
/*
 * < @var Function State
 */
static uint8_t gu8CommuincationError;
/*
 * < @var Function State
 */
static pFunc_t gpAfterErrorCallback;
/*
 @var switch Request
 */
static uint8_t gu8SwRequest;
/*
 <@var Dipslay Reques
 */
static uint8_t gu8DisplayRequest;
/*
 @var switch Request
 */
static stTimer_TimeOut_t gsRequestTimeOut;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Definitions>                                    |
 --------------------------------------------------------------------------------------------------------
 */

static void CommErrorCencel();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < StartConfigError >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void StartConfigError                                                           |
 | < @Description       : start Config Error                |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t CommunicationError();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Implements>                                    |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < StartConfig >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t StartConfig                                                            |
 | < @Description       : Sends a start configuration request to a specific address and handles          |
 |                         state transitions based on the response.                                        |      
 | < @Param             : uint8_t address - The address to which the configuration request is sent.     |
 |                         uint8_t request - The configuration request data.                              |
 | < @return            : uint8_t - Returns 1 if successful, 0 otherwise.                                |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t StartConfig(uint8_t address, uint8_t request) {
    uint8_t buf[2];
    uint8_t frameState;
    switch (gu8ReqFunState) {
        case 0:
            buf[0] = SW_START_CONFIG_REQ;
            buf[1] = request;
            frameState = putDataCh0(buf, sizeof (buf), address, RequestFrame);
            if (frameState == DATA_FRAME_SUCESS) {
                gu8ReqFunState = 0;
                return 1;
            } else if (frameState == DATA_FRAME_ERROR) {
                gu8ReqFunState = 1;
                return 0;
            }
            break;

        case 1:
            if (CommunicationError()) {
                gu8ReqFunState = 0;
                return 1;
            }
            break;

        default:
            gu8ReqFunState = 0;
            break;
    }

    return 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < LoadIpRequest >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void LoadIpRequest                                                            |
 | < @Description       : Load Ip To Point                                                              |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t LoadIpRequest(uint8_t DA, uint8_t Ip) {
    uint8_t buf[2];
    uint8_t FrameState;
    switch (gu8ReqFunState) {
        case 0:
            buf[0] = SET_IP_REQ;
            buf[1] = Ip;
            FrameState = putDataCh0(buf, 2, DA, RequestFrame);
            if (FrameState == DATA_FRAME_SUCESS) {
                gu8ReqFunState = 1;
                return (0);
            }
            if (FrameState == DATA_FRAME_ERROR) {
                gu8ReqFunState = 2;
                return (0);
            }
            break;
        case 1:
            if (sendFreeFrame()) {
                gu8ReqFunState = 0;
                return (1);
            }
            break;
        case 2:
            if (CommunicationError()) {
                gu8ReqFunState = 0;
                return (1);
            }
            break;
        default:
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < PowerOnRequest >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PowerOnRequest                                                           |
 | < @Description       : request data from save unit                                                   |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ConfigRoom(stRoomConfig_t *room, uint8_t Ip) {
    uint8_t buf[sizeof (stRoomConfig_t) + 1];
    uint8_t FrameState;
    switch (gu8ReqFunState) {
        case 0:
            buf[0] = SW_CONFIG_REQ;
            copyBuff(buf + 1, room, sizeof (stRoomConfig_t));
            FrameState = putDataCh0(buf, sizeof (stRoomConfig_t) + 1, Ip, RequestFrame);
            if (FrameState == DATA_FRAME_SUCESS) {
                gu8ReqFunState = 1;
                return (0);
            }
            if (FrameState == DATA_FRAME_ERROR) {
                gu8ReqFunState = 2;
                return (0);
            }
            break;
        case 1:
            if (sendFreeFrame()) {
                gu8ReqFunState = 0;
                return (1);
            }
            break;
        case 2:
            if (CommunicationError()) {
                gu8ReqFunState = 0;
                return (1);
            }
            break;
        default:
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <swReqData>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void swReqData                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t swReqData(uint8_t PointAddress, uint8_t Ip, uint8_t State) {
    uint8_t buf[3];
    uint8_t FrameState;
    buf[0] = SW_SAVE_STATE_RES;
    buf[1] = Ip;
    buf[2] = State;
    FrameState = putDataCh0(buf, 3, PointAddress, ResponseFrame);
    if (FrameState == DATA_FRAME_SUCESS) {
        return (1);
    }
    if (FrameState == DATA_FRAME_ERROR) {
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SWOnReq>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void SWOnReq                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SWOnReq(uint8_t RequestType, uint8_t PointAddress, uint8_t Ip, stCallPointConfig_t *config, stCallPointData_t *Data, bool error_messgae) {
    memAddresst_t address;
    uint8_t buf[12];
    uint8_t FrameState;
    if (Ip == 0) {
        return (1);
    }
    switch (gu8SwRequest) {
        case 0:/*load current Configurations*/
            if (RequestType == RequestFrame) {
                gu8SwRequest = 2;
                return (0);
            }

            address = MEMORY_START_SWITCH_CONFIG + ((Ip - 1) * (sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) config, sizeof (stCallPointConfig_t))) {
                /*unready*/
                gu8SwRequest = 1;
            }
            break;
        case 1:
            address = MEMORY_START_SWITCH_DATA + ((Ip - 1) * (sizeof (stCallPointData_t)));
            if (LoadFromMemory(address, (uint8_t *) Data, sizeof (stCallPointData_t))) {
                gu8SwRequest = 2;
            }
            break;
        case 2:
            if (RequestType == ResponseFrame) {
                buf[0] = SW_POWER_ON_RES;
            } else {
                buf[0] = SW_CONFIG_REQ;
            }
            buf[1] = Ip;
            copyBuff(buf + 2, config, sizeof (stCallPointConfig_t)); //5 byte 2+5=7
            copyBuff(buf + 2 + sizeof (stCallPointConfig_t), Data, 4); //4 byte
            buf[11] = Data->State;
            FrameState = putDataCh0(buf, 12, PointAddress, RequestType);

            if (FrameState == DATA_FRAME_SUCESS) {
                if (RequestType == ResponseFrame) {
                    gu8SwRequest = 0;
                    return (1);
                }
                gu8SwRequest = 3;
                sysSetPeriodMS(&gsRequestTimeOut, 50);
                return (0);
            }
            if (FrameState == DATA_FRAME_ERROR) {

                gu8SwRequest = 4;
            }
            break;
        case 3:/*wait Fro Response*/
            if (sysIsTimeoutMs(&gsRequestTimeOut) == 0) {
                /*show Error Message*/
                gu8SwRequest = 4;
            }
            break;
        case 4:
            if (!error_messgae) {
                gu8SwRequest = 0;
                return (1);
            }
            ReturnMenuCallBack();
            CommanEventFunctions(NULL, NULL, NULL, NULL, CommErrorSwConfigORSuceessCencel);
            lcdNoBlink();
            lcdClear();
            WriteMessage(0, 21);
            WriteMessage(1, 22);
            gu8SwRequest = 6;
            break;
        case 5:
            if (sendFreeFrame()) {
                ReturnMenuCallBack();
                gu8SwRequest = 0;
                return (1);
            }

            break;
        case 6:/*wait state*/
            break;
        default:
            gu8SwRequest = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SWOnReq>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void SWOnReq                                                            |
 | < @Description         : response handle of switch Power on                                              |   
 | < @return              : 0 is running , 1 is done                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t DisplayOnReq(uint8_t RequestType, uint8_t PointAddress, uint8_t Ip, stDisplayConfig_t *config) {
    memAddresst_t address;
    uint8_t buf[19];
    uint8_t FrameState;
    if (Ip == 0) {
        return (1);
    }
    switch (gu8DisplayRequest) {
        case 0:/*load current Configurations*/
            if (RequestType == RequestFrame) {
                gu8DisplayRequest = 1;
                return (0);
            }
            address = MEMORY_START_DISPLAY_CONFIG + ((Ip - 1) * (sizeof (stDisplayConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) config, sizeof (stDisplayConfig_t))) {
                /*unready*/
                gu8DisplayRequest = 1;
            }
            break;
        case 1:
            if (RequestType == ResponseFrame) {
                buf[0] = DISPLAY_POWER_ON_RES;
            } else {
                buf[0] = DISPLAY_CONFIG_REQ;
            }
            buf[1] = Ip;
            copyBuff(buf + 2, config, sizeof (stDisplayConfig_t));
            FrameState = putDataCh0(buf, 19, PointAddress, RequestType);

            if (FrameState == DATA_FRAME_SUCESS) {
                if (RequestType == ResponseFrame) {
                    gu8DisplayRequest = 0;
                    return (1);
                }
                gu8DisplayRequest = 2;
                sysSetPeriodMS(&gsRequestTimeOut, 50);
                return (0);
            }
            if (FrameState == DATA_FRAME_ERROR) {
                gu8DisplayRequest = 3;
            }
            break;
        case 2:/*wait Fro Response*/
            if (sysIsTimeoutMs(&gsRequestTimeOut) == 0) {
                /*show Error Message*/
                gu8DisplayRequest = 3;
            }
            break;
        case 3:
            ReturnMenuCallBack();
            CommanEventFunctions(NULL, NULL, NULL, NULL, CommErrorDisplayConfigORSuceessCencel);
            lcdNoBlink();
            lcdClear();
            WriteMessage(0, 21);
            WriteMessage(1, 22);
            gu8DisplayRequest = 5;
            break;
        case 4:
            if (sendFreeFrame()) {
                ReturnMenuCallBack();
                gu8DisplayRequest = 0;
                return (1);
            }
            break;
        case 5:/*wait state*/
            break;
        default:
            gu8DisplayRequest = 0;
            break;
    }
    return (0);
}




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
void RequestesInit() {
    gu8CommuincationError = 0;
    gu8ReqFunState = 0;
    gpAfterErrorCallback = NULL;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RegisterAfterError >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void RegisterAfterError                                                            |
 | < @Description       : after error action                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void RegisterAfterError(pFunc_t Error) {
    gpAfterErrorCallback = Error;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < StartConfigError >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void StartConfigError                                                           |
 | < @Description       : start Config Error                |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t CommunicationError() {
    switch (gu8CommuincationError) {
        case 0:
            lcdNoBlink();
            lcdClear();
            ReturnMenuCallBack();
            CommanEventFunctions(NULL, NULL, NULL, NULL, CommErrorCencel);
            WriteMessage(0, 21);
            WriteMessage(1, 22);
            gu8CommuincationError = 1;
            break;
        case 1:
            break;
        case 2:
            /*execuate callback*/
            if (gpAfterErrorCallback != NULL) {
                ReturnMenuCallBack();
                gu8CommuincationError = 0;
                gpAfterErrorCallback();
                return (1);
            }
            break;
        default:
            break;
    }
    return (0);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < CommErrorDisplayConfigORSuceessCencel >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void CommErrorDisplayConfigORSuceessCencel                                                            |
 | < @Description       : system Error Or Sucess Sw Config Frame                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void CommErrorDisplayConfigORSuceessCencel() {
    gu8DisplayRequest = 4;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < CommErrorSwConfigORSuceessCencel >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void CommErrorSwConfigORSuceessCencel                                                            |
 | < @Description       : system Error Or Sucess Sw Config Frame                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void CommErrorSwConfigORSuceessCencel() {
    gu8SwRequest = 5;
}

static void CommErrorCencel() {
    gu8CommuincationError = 2;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Implements>                                    |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < AcceptAllRequest >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void AcceptAllRequest                                                         |
 | < @Description       : Request Frame This Frame is borad casting for all                             |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t AcceptPointRequest(uint8_t ip) {
    uint8_t buf[2];
    uint8_t FrameState;
    switch (gu8ReqFunState) {
        case 0:
            buf[0] = SW_ACCEPT_STATE_REQ;
            buf[1] = ip;
            FrameState = putDataCh0(buf, 2, 0xFF, RequestFrame);
            if (FrameState == DATA_FRAME_SUCESS) {
                gu8ReqFunState = 1;
                return (0);
            }
            if (FrameState == DATA_FRAME_ERROR) {
                gu8ReqFunState = 1;
                return (0);
            }
            break;
        case 1:
            if (sendFreeFrame()) {
                gu8ReqFunState = 0;
                return (1);
            }
            break;
        default:
            gu8ReqFunState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < update displays requests >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void AcceptAllRequest                                                         |
 | < @Description       : Request Frame This Frame is borad casting for all                             |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t updateDisplayRequest(QueueItem *item, uint8_t type) {
    //load point display 
    if (gu8RequestDisplay == 0) {
        uint8_t buf[8];
        buf[0] = SW_UPDATE_DISPLAYS_REQ;
        buf[1] = item->address;
        buf[2] = item->State;
        copyBuff(buf + 3, (uint8_t *) & item->swId, 4);
        buf[7] = type;
        uint8_t framestate = putDataCh0(buf, 8, 0xFF, RequestFrame);
        if (framestate == DATA_FRAME_SUCESS) {
            gu8RequestDisplay = 1;
            return (0);
        }
        if (framestate == DATA_FRAME_ERROR) {
            gu8RequestDisplay = 1;
            return (0);
        }
        return (0);
    }
    if (sendFreeFrame()) {
        gu8RequestDisplay = 0;
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < update displays requests >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void AcceptAllRequest                                                         |
 | < @Description       : Request Frame This Frame is borad casting for all                             |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ClearDisplay() {
    //load point display 
    if (gu8RequestDisplay == 0) {
        uint8_t buf;
        buf = SW_UPDATE_DISPLAY_REQ;
        uint8_t framestate = putDataCh0(&buf, 1, 0xFF, RequestFrame);
        if (framestate == DATA_FRAME_SUCESS) {
            gu8RequestDisplay = 1;
            return (0);
        }
        if (framestate == DATA_FRAME_ERROR) {
            gu8RequestDisplay = 1;
            return (0);
        }
        return (0);
    }
    if (sendFreeFrame()) {
        gu8RequestDisplay = 0;
        return (1);
    }
    return (0);
}