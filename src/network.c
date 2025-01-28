
#include "appRes.h"
/*
 *<@var :gu8Network State to Request Or Response 
 */
static uint8_t gu8NetworkState;
/*
 *<@var :currnt response of the address
 */
static uint8_t gu8CurrentAddress;
/*
 *<@var :currnt response of the address
 */
static uint8_t gu8CurrentIp;
/*
 *<@var :currnt current call Point Data Load From Memeory
 */
static stCallPointData_t gsCurrentCallPointData;
/*
 *<@var :currnt current call point Config Data Load From Memeory
 */
static stCallPointConfig_t gsCurrentCallPointConfig;
/*
 *<@var :currnt current call point Config Data Load From Memeory
 */
static stDisplayConfig_t gsCurrentDisplayConfig;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkClientSystem>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkClientSystem                                                    |
 | < @Description         : any Response can be handel from this function                               |   
 | < @Param DA            : received address from other station                                         |
 | < @PAram len           : Data received Length                                                        |
 | < @Param Data          : Data received                                                               |
 | < @return              : 0 is run , 1 is done                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t NetworkClientSystem(uint8_t SA, uint8_t DA, uint8_t len, uint8_t *Data);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkHostSystem>                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkHostSystem                                                      |
 | < @Description         : any request can be handel from this function                                |
 | < @Param DA            : received address from other station                                         |
 | < @PAram len           : Data received Length                                                        |
 | < @Param Data          : Data received                                                               |
 | < @return              : 0 is run , 1 is done                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t NetworkHostSystem(uint8_t SA, uint8_t DA, uint8_t len, uint8_t *Data);


/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkInit>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkInit                                                            |
 | < @Description         : Init all data into this file                                                |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void NetworkInit() {
    gu8NetworkState = 0;
    OnClientFrameCh0(NetworkClientSystem);
    OnHostFrameCh0(NetworkHostSystem);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkClientSystem>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkClientSystem                                                    |
 | < @Description         : any Response can be handel from this function                               |   
 | < @Param DA            : received address from other station                                         |
 | < @PAram len           : Data received Length                                                        |
 | < @Param Data          : Data received                                                               |
 | < @return              : 0 is run , 1 is done                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t NetworkClientSystem(__unused uint8_t SA, __unused uint8_t DA, __unused uint8_t len, uint8_t *Data) {
    if (Data[0] == SET_IP_RES) {
        loadIpGetIpShowWithIp(Data[1]);
        return (1);
    }

    if (Data[0] == SW_CONFIG_RES) {
        sendFreeFrame();
        CommErrorSwConfigORSuceessCencel();
        return (1);
    }

    if (Data[0] == DISPLAY_CONFIG_RES) {
        sendFreeFrame();
        CommErrorDisplayConfigORSuceessCencel();
        return (1);
    }

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkHostSystem>                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkHostSystem                                                      |
 | < @Description         : any request can be handel from this function                                |
 | < @Param DA            : received address from other station                                         |
 | < @PAram len           : Data received Length                                                        |
 | < @Param Data          : Data received                                                               |
 | < @return              : 0 is run , 1 is done                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t NetworkHostSystem(__unused uint8_t SA, uint8_t DA, __unused uint8_t len, uint8_t *Data) {

    if (gu8NetworkState) {
        return (0);
    }






    if (Data[0] == SW_POWER_ON_REQ) {
        if (Data[1] >= MAX_DEVICE_USED || Data[1] == 0) {
            return (1);
        }
        gu8CurrentAddress = DA;
        gu8CurrentIp = Data[1];
        gu8NetworkState = 1;

        return (1);
    }

    if (Data[0] == SW_SAVE_STATE_REQ) {
        if (Data[1] >= MAX_DEVICE_USED || Data[1] == 0) {
            return (1);
        }
        if (systemInactive() == false) {
            return (1);
        }

        gu8CurrentAddress = DA;
        gu8CurrentIp = Data[1];
        gsCurrentCallPointData.State = Data[2];
        copyBuff(&gsCurrentCallPointData.SWID, Data + 3, 4);
        gsCurrentCallPointData.Time = systemNow();
        gu8NetworkState = 2;
        return (1);
    }


    if (Data[0] == DISPLAY_POWER_ON_REQ) {
        gu8CurrentAddress = DA;
        gu8CurrentIp = Data[1];
        gu8NetworkState = 4;
        return (1);
    }

    if (Data[0] == ROOM_POWER_ON_REQ) {
        gu8CurrentAddress = DA;
        gu8CurrentIp = Data[1];
        gu8NetworkState = 5;
        return (1);
    }


    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkCallback>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkCallback                                                            |
 | < @Description         : run in background task                                               |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void NetworkCallback() {
    /*mem*/


    memAddresst_t address;
    switch (gu8NetworkState) {
        case 0:
            break;
        case 1:
            /*call Point Power On Res*/
            if (SWOnReq(ResponseFrame, gu8CurrentAddress, gu8CurrentIp, &gsCurrentCallPointConfig, &gsCurrentCallPointData, false)) {
                gu8NetworkState = 0;
            }
            break;
        case 2:
            address = MEMORY_START_SWITCH_DATA + (((gu8CurrentIp - 1) * sizeof (stCallPointData_t)));
            if (SaveIntoMemory(address, (uint8_t *) & gsCurrentCallPointData, sizeof (stCallPointData_t))) {
                gu8NetworkState = 3;
            }
            break;
        case 3:
            if (swReqData(gu8CurrentAddress, gu8CurrentIp, gsCurrentCallPointData.State)) {
                QueueItem item;
                item.address = gu8CurrentIp;
                item.State = getCurrentState(gsCurrentCallPointData.State);
                item.swId = gsCurrentCallPointData.SWID;
                item.RId = gsCurrentCallPointData.RID;
                item.timestamp = gsCurrentCallPointData.Time;
                ATOMIC_BEGIN
                putIntoQueue(item);
                ATOMIC_END
                gu8NetworkState = 0;
            }
            break;
        case 4:
            if (DisplayOnReq(ResponseFrame, gu8CurrentAddress, gu8CurrentIp, &gsCurrentDisplayConfig)) {
                gu8NetworkState = 0;
            }
            break;
        case 5:

            break;
        default:
            gu8NetworkState = 0;
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <NetworkCallback>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void NetworkCallback                                                            |
 | < @Description         : run in background task                                               |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
 CommandType getCurrentState(uint8_t state) {
    if (state == SYSTEM_CALL_EVENT || state == SYSTEM_ASSISSET_EVENT) {
        return CALL_STATE;
    }

    if (state == SYSTEM_EMG_EVENT) {
        return URGENT_STATE;
    }
    return CANCEL_STATE;
}

