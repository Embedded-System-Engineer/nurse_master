/* 
 * File:   ResetSystem.c
 * Author: mosta
 *
 * Created on May 9, 2023, 1:53 AM
 */

#include "appRes.h"

/**/
static uint16_t gu16ResetIndex;
static uint8_t gu8ResetConfiramedKey;
static uint8_t gu8ResetModuleState;
static bool gu8SytemInactive = false;
static stTimer_TimeOut_t gstResetDataTimeOut;
/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemPorgressBar  >                                                    |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemPorgressBar                                                       |
  | < @Description       : update progress bar                                                            |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static void SystemPorgressBar(uint16_t Ip, uint16_t Max, uint8_t MSGIndex);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetIp  >                                                         |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetIp                                                           |
  | < @Description       : Reset Modeule bu Ip                                                           |
  |                      : PrintMessage                                                                  |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static uint8_t SystemResetIp(uint16_t Ip, uint8_t Module);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetModule  >                                                         |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetModule                                                           |
  | < @Description       : Reset Modeule                                                            |
  |                      : PrintMessage                                                                  |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static uint8_t SystemResetModule(uint16_t max, uint8_t Module);
static uint8_t ResetSystemSwitchConfig(uint8_t Ip);
static uint8_t ResetSystemSwitchData(uint8_t Ip);

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetIp  >                                                         |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetIp                                                           |
  | < @Description       : Reset Modeule bu Ip                                                           |
  |                      : PrintMessage                                                                  |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static uint8_t SystemResetIp(uint16_t Ip, uint8_t Module) {
    tm_t Date;
    memAddresst_t address;
    stDisplayConfig_t stDisplayConfig;
    stRoomConfig_t stRoomConfig;
    stCallPointLog_t stCallPointLog;
    uint8_t Byte = NO_MODULE_SELECT;
    if (lcdIsBusy()) {
        return (0);
    }
    switch (Module) {

        case NO_MODULE_SELECT:
            return (1);
            break;
        case NO_MODULE_ON_SELECT:
            return (1);
            break;
        case DISPLAY_MODULE_SELECT:/*2*/
            address = MEMORY_START_DISPLAY_CONFIG + (Ip * (sizeof (stDisplayConfig_t)));
            stDisplayConfig.Option.Options = 0x00;
            stDisplayConfig.Option.MainView = 1; //switch id is active
            setBuff(stDisplayConfig.activeIps, 0x00, MAX_DEVICE_USED >> 3);
            bitSet(stDisplayConfig.activeIps[0], 0);
            if (SaveIntoMemory(address, (uint8_t *) & stDisplayConfig, sizeof (stDisplayConfig_t))) {
                return (1);
            }
            break;
        case ROOM_MODULE_SELECT:/*3*/
            address = MEMORY_START_ROOM_CONFIG + (Ip * (sizeof (stRoomConfig_t)));
            stRoomConfig.scollerTime = 1;
            stRoomConfig.option.Options = 0;
            if (SaveIntoMemory(address, (uint8_t *) & stRoomConfig, sizeof (stRoomConfig_t))) {
                return (1);
            }
            break;
        case SWCONFIG_MODULE_SELECT/*4*/:
            if (ResetSystemSwitchConfig(Ip)) {
                return (1);
            }
            break;
        case SWDATA_MODULE_SELECT:/*5*/
            if (ResetSystemSwitchData(Ip)) {
                return (1);
            }
            break;
        case LOG_MODULE_SELECT:/*6*/
            address = MEMORY_START_SWITCH_LOG + (Ip * sizeof (stCallPointLog_t));
            stCallPointLog.Ip = 0x00;
            stCallPointLog.State = SYSTEM_CANCEL_EVENT;
            stCallPointLog.Time = systemNow();
            if (SaveIntoMemory(address, (uint8_t *) & stCallPointLog, sizeof (stCallPointLog_t))) {
                return (1);
            }
            break;
        case RESET_SERRIAL_SELECT:
            address = MEMORY_START_SERAIL_NUMBER;
            SystemSerial_t serial;
            setBuff(&serial, 0x00, sizeof (SystemSerial_t));
            if (SaveIntoMemory(address, (uint8_t *) & serial, sizeof (SystemSerial_t))) {
                ConfigurationInit();
                return (1);
            }
            break;
        case WORKING_TIME_SELECT:/*7*/
            DateTimeFromTimeStamp(&Date, systemNow());
            Date.tm_min = 0;
            Date.tm_sec = 0;
            Date.tm_hour = 0;
            gstWorkingTime.StartTime = DateTimeUnixtime(&Date);
            Date.tm_hour = 23;
            gstWorkingTime.EndTime = DateTimeUnixtime(&Date);
            if (SaveIntoMemory(CURRENT_WORKINGTIME_ADDRESS, (uint8_t *) & gstWorkingTime, sizeof (stWorkingtime_t))) {
                return (1);
            }
            break;
        case RESET_LOAD_CONFIG_SELECT:
            if (SaveIntoMemory(MEMORY_START_LOAD_CONFIG + Ip, &Byte, 1)) {
                return (1);
            }
            break;
        default:
            return (1);
            break;
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetInit  >                                                      |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetInit                                                         |
  | < @Description       : default values of this file variables                                         |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void SystemResetInit() {
    gu16ResetIndex = 0;
    gu8ResetConfiramedKey = 0;
    gu8ResetModuleState = 0;

}

static uint8_t ResetSystemSwitchConfig(uint8_t Ip) {
    static uint8_t state = 0;
    memAddresst_t address;
    static stCallPointData_t stCallPointData;
    static stCallPointConfig_t stCallpointConfig;
    switch (state) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (Ip * (sizeof (stCallPointConfig_t)));
            stCallpointConfig.Rip = 1;
            stCallpointConfig.Option.Options = 0;
            stCallpointConfig.Option.buzzerState = 1;
            stCallpointConfig.Option.buzzerTimeFactor = 5;
            stCallpointConfig.SwitchHwType[0] = SYSTEM_SWITCH_TYPE_EMG;
            stCallpointConfig.SwitchHwType[1] = SYSTEM_SWITCH_TYPE_CALL;
            stCallpointConfig.SwitchHwType[2] = SYSTEM_SWITCH_TYPE_CENECEL;
            if (SaveIntoMemory(address, (uint8_t *) & stCallpointConfig, sizeof (stCallPointConfig_t))) {
                state = 1;
            }
            break;
        case 1:
            address = MEMORY_START_SWITCH_DATA + (Ip * (sizeof (stCallPointData_t)));
            stCallPointData.RID = 1;
            stCallPointData.SWID = 101;
            if (Ip == 0) {
                stCallPointData.State = SYSTEM_CANCEL_EVENT;
            } else {
                stCallPointData.State = SYSTEM_DEFALUT_EVENT;
            }
            stCallPointData.Time = systemNow();
            if (SaveIntoMemory(address, (uint8_t *) & stCallPointData, sizeof (stCallPointData_t))) {
                state = 2;
            }
            break;
        case 2:
            if (SWOnReq(RequestFrame, 0xFF, Ip, &stCallpointConfig, &stCallPointData, false)) {
                state = 3;
                sysSetPeriodMS(&gstResetDataTimeOut, 100);
            }
            break;
        case 3:
            if (sysIsTimeoutMs(&gstResetDataTimeOut) == 0) {
                state = 0;
                return (1);
            }
            break;
        default:
            state = 0;
            break;
    }
    return (0);
}

static uint8_t ResetSystemSwitchData(uint8_t Ip) {
    static uint8_t state = 0;
    memAddresst_t address;
    static stCallPointData_t stcallpointData;
    static stCallPointConfig_t stConfig;
    switch (state) {
        case 0:
            address = MEMORY_START_SWITCH_DATA + (Ip * (sizeof (stCallPointData_t)));

            if (LoadFromMemory(address, (uint8_t *) & stcallpointData, sizeof (stCallPointData_t))) {
                if (stcallpointData.State != SYSTEM_DEFALUT_EVENT) {
                    stcallpointData.State = SYSTEM_CANCEL_EVENT;
                    stcallpointData.Time = systemNow();
                    state = 1;
                    return (0);
                }
                return (1);
            }
            break;
        case 1:
            address = MEMORY_START_SWITCH_DATA + (Ip * (sizeof (stCallPointData_t)));
            if (SaveIntoMemory(address, (uint8_t *) & stcallpointData, sizeof (stCallPointData_t))) {
                QueueItem item;
                item.address = Ip + 1;
                item.State = CANCEL_STATE;
                ATOMIC_BEGIN
                putIntoQueue(item);
                ATOMIC_END
                state = 2;
            }
            break;
        case 2:
            address = MEMORY_START_SWITCH_CONFIG + (Ip * (sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & stConfig, sizeof (stCallPointConfig_t))) {
                state = 3;
            }
            break;
        case 3:
            if (SWOnReq(RequestFrame, 0xFF, (Ip + 1), &stConfig, &stcallpointData, false)) {
                state = 4;
                sysSetPeriodMS(&gstResetDataTimeOut, 100);
            }
            break;
        case 4:
            if (sysIsTimeoutMs(&gstResetDataTimeOut) == 0) {
                state = 0;
                return (1);
            }
            break;
        default:
            state = 0;
            break;
    };
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetDisplayCallBack  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetDisplayCallBack                                                       |
  | < @Description       : reset display Module                                                    |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetDisplayCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            return (0);
        }
        return (0);
    }

    if (SystemResetDisplayModule()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetRoomCallBack  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetRoomCallBack                                                       |
  | < @Description       : reset rooms Module                                                    |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetRoomCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            return (0);
        }
        return (0);
    }

    if (SystemResetRoomModule()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSwConfigCallBack  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSwConfigCallBack                                                       |
  | < @Description       : reset switch config Module                                                    |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetSwConfigCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            return (0);
        }
        return (0);
    }

    if (SystemResetSwConfigModule()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSwDataCallBack  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSwDataCallBack                                                       |
  | < @Description       : reset switch data Module                                                    |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetSwDataCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            gu16ResetIndex = 0;
            return (0);
        }
        return (0);
    }

    if (SystemResetSwDataModule()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSwDataCallBack  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSwDataCallBack                                                       |
  | < @Description       : reset switch data Module                                                    |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetLogCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            return (0);
        }
        return (0);
    }

    if (SystemResetLogDataModule()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSerialCallBack  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSerialCallBack                                                       |
  | < @Description       : reset serial Module                                                    |                                 |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetSerialCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            return (0);
        }
        return (0);
    }

    if (SystemResetSerail()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetInit  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetInit                                                       |
  | < @Description       : Print Message Into Buffer Array                                                    |
  |                      : PrintMessage                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetDisplayModule() {
    if (SystemResetModule(MAX_DEVICE_USED, DISPLAY_MODULE_SELECT)) {
        return (1);
    }
    return (0);

}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetRoomModule  >                                                |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetRoomModule                                                   |
  | < @Description       : Reset System of the Modul Room                                                |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetRoomModule() {
    if (SystemResetModule(MAX_DEVICE_USED, ROOM_MODULE_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSwConfigModule  >                                            |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSwConfigModule                                               |
  | < @Description       : Reset System of the Modul switch conguration                                  |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetSwConfigModule() {
    if (SystemResetModule(MAX_DEVICE_USED, SWCONFIG_MODULE_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSwDataModule  >                                              |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSwDataModu                                                   |
  | < @Description       : Reset System of the Modul switch data                                         |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetSwDataModule() {
    if (SystemResetModule(MAX_DEVICE_USED, SWDATA_MODULE_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetModule  >                                                         |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetModule                                                           |
  | < @Description       : Reset Modeule                                                            |
  |                      : PrintMessage                                                                  |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static uint8_t SystemResetModule(uint16_t max, uint8_t Module) {
    if (gu16ResetIndex < max) {
        if (SystemResetIp(gu16ResetIndex, Module)) {
            gu16ResetIndex++;
            SystemPorgressBar(gu16ResetIndex, max, Module - 2 + 7);
        }
    } else {
        gu16ResetIndex = 0;
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetLogDataModule  >                                              |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetLogDataModule                                                   |
  | < @Description       : Reset System of the Modul log data                                         |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetLogDataModule() {
    uint16_t max;
    max = ((uint16_t) (END_MEMORY - 1) - ((uint16_t) MEMORY_START_SWITCH_LOG));
    max /= (sizeof (stCallPointLog_t));
    if (SystemResetModule(max, LOG_MODULE_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetLoadConfig  >                                              |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetLoadConfig                                                   |
  | < @Description       : Reset System of the Modul log data                                         |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetLoadConfig() {
    if (SystemResetModule(MAX_DEVICE_USED, RESET_LOAD_CONFIG_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetWorkingTime  >                                              |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetWorkingTime                                                   |
  | < @Description       : Reset System of the Modul log data                                         |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetWorkingTime() {
    if (SystemResetIp(0, WORKING_TIME_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemResetSerail  >                                              |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemResetSerail                                                   |
  | < @Description       : Reset System of the Modul log data                                         |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemResetSerail() {
    if (SystemResetIp(0, RESET_SERRIAL_SELECT)) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < SystemPorgressBar  >                                                    |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  SystemPorgressBar                                                       |
  | < @Description       : update progress bar                                                            |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static void SystemPorgressBar(uint16_t Ip, uint16_t Max, uint8_t MSGIndex) {
    uint8_t buf[LCD_NUMBER_OF_BYTE];
    setBuff(buf, ' ', LCD_NUMBER_OF_BYTE);
    uint8_t Index = 0;
    lcdClear();
    Index = map(Ip, 0, Max, 0, 100);
    buf[15] = '%';
    appPrintMessage(buf, 0, MSGIndex);
    print2d(Index, buf + LCD_NUMBER_OF_BYTE - 3, 0);
    lcdupdateProgressBar(Index, 100, 1);
    lcdwritebuf(0, 0, buf, LCD_NUMBER_OF_BYTE);
    lcdUpdateNow();
}

static uint8_t SystemInActive() {
    static uint8_t systemState = 0;
    static uint8_t gu8DisplayCallBacksState = 0;
    uint8_t OptionCallBackState = 0;
    switch (gu8DisplayCallBacksState) {
        case 0:
            if (LoadFromMemory((memAddresst_t) SYSTEM_INACTIVE_ADDRESS, (uint8_t *) & systemState, 1)) {
                gu8DisplayCallBacksState = 1;
                lcdClear();
                WriteMessage(0, 38);
                if (systemState == 0) {
                    systemState = false;
                } else {
                    systemState = true;
                }
                systemOptionRegisterData(2, systemState, 36);
            }
            break;
        case 1:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8DisplayCallBacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                systemState = SystemGetCurrentOption();
                gu8DisplayCallBacksState = 2;
                return (0);
            }

            break;
        case 2:
            if (SaveIntoMemory((memAddresst_t) SYSTEM_INACTIVE_ADDRESS, (uint8_t *) & systemState, 1)) {
                gu8SytemInactive = systemState;
                gu8DisplayCallBacksState = 0;
                return (1);
            }
            break;
        default:
            gu8DisplayCallBacksState = 0;
            break;
    }
    return (0);
}

uint8_t inactiveSytemCallBack() {
    uint8_t ConfirmedKey = 0;
    if (!gu8ResetModuleState) {
        ConfirmedKey = CustomPasswordCallback();
        if (ConfirmedKey == 2) {
            return (1);
        }

        if (ConfirmedKey == 1) {
            gu8ResetModuleState = 1;
            return (0);
        }
        return (0);
    }

    if (SystemInActive()) {
        gu8ResetModuleState = 0;
        return (1);
    }

    return (0);
}

bool systemInactive() {
    return gu8SytemInactive;
}

void setSystemInactive(bool value) {
    gu8SytemInactive = value;
}