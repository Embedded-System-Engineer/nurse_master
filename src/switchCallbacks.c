#include "appRes.h"

static uint8_t gu8SwStateCallbacksState;
/*
 * <@var system Call Point Config 
 */
/*this config is saved in memory address by address about call backs*/
static stCallPointConfig_t gstCallPointConfig;
/*
 * Call Point User show Data with saved Time
 */
static stCallPointData_t gsCallPointData;
/*
 * Call Point User show Data with saved Time
 */
static uint8_t gu8LastIpSelect;
/*
 * First Call Back
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SelectIpCencelErrorMessage >                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SelectIpCencelErrorMessage                                               |
 | < @Description       : run when Error message event                                                  |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void afterErrorComm();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchIps >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchIps                                                        |
 | < @Description       :switch                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t switchIps(uint8_t *IpEdit, uint8_t MemPos);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchIps >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchIps                                                        |
 | < @Description       :switch                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t switchIDs(uint16_t *IDEdit, uint8_t MemPos);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SelectIpCencelErrorMessage >                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SelectIpCencelErrorMessage                                               |
 | < @Description       : run when Error message event                                                  |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void afterErrorComm() {
    ReturnMenuCallBack();
    gu8SwStateCallbacksState = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchIps >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchIps                                                        |
 | < @Description       :switch                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t switchIDs(uint16_t *IDEdit, uint8_t MemPos) {
    uint8_t funCationStateCallBack;
    memAddresst_t address;
    if (lcdIsBusy()) {
        return (0);
    }
    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t);
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
            }
            break;
        case 1:
            address = MEMORY_START_SWITCH_DATA + (getCurrentIpSelect() - 1) * sizeof (stCallPointData_t);
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                lcdClear();
                WriteMessage(0, 3);
                RegisterTypeAs3DigitOr5Digit(5, *IDEdit);
                gu8SwStateCallbacksState = 2;
            }
            break;
        case 2:
            funCationStateCallBack = TypeCallBack();
            if (funCationStateCallBack == 1) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            if (funCationStateCallBack == 2) {
                *IDEdit = TypeGetValue16Bit();
                gu8SwStateCallbacksState = 3;
            }
            break;
        case 3:
            address = MEMORY_START_SWITCH_DATA + (getCurrentIpSelect() - 1) * sizeof (stCallPointData_t) + MemPos;
            if (SaveIntoMemory(address, (uint8_t *) IDEdit, sizeof (uint16_t))) {
                gu8SwStateCallbacksState = 4;
                RegisterAfterError(afterErrorComm);
                return (0);
            }
            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;
    }
    return (0);
}
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchTypeing >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchTypeing                                                           |
 | < @Description       : switch type two Response                                                     |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t switchTypeing(uint8_t *EditSwitch, uint8_t memPos);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RoomIdCallBack >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void RoomIdCallBack                                                        |
 | < @Description       : write room id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t RoomIdCallBack() {
    return switchIDs(&gsCallPointData.RID, 2);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchIDCallBack >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchIDCallBack                                                        |
 | < @Description       : write switch id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchIDCallBack() {
    return switchIDs(&gsCallPointData.SWID, 0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchIps >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchIps                                                        |
 | < @Description       :switch                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t switchIps(uint8_t *IpEdit, uint8_t MemPos) {
    memAddresst_t address;
    uint8_t IpCancelState = 0;

    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t);
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
                gu8LastIpSelect = getCurrentIpSelect();
            }
            break;
        case 1:
            address = MEMORY_START_SWITCH_DATA + (getCurrentIpSelect() - 1) * sizeof (stCallPointData_t);
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                gu8SwStateCallbacksState = 2;
                SetCurrentIpSelect(*IpEdit);
            }
            break;
        case 2:
            IpCancelState = selectIpCallback();
            if (IpCancelState == 1) {
                resetCurrentIP();
                gu8SwStateCallbacksState = 0;
                SetCurrentIpSelect(gu8LastIpSelect);
                return (1);
            }
            if (IpCancelState == 2) {
                gu8SwStateCallbacksState = 3;
                *IpEdit = getCurrentIpSelect();
                resetCurrentIP();
            }
            break;
        case 3:
            address = MEMORY_START_SWITCH_CONFIG + (gu8LastIpSelect - 1) * sizeof (stCallPointConfig_t) + MemPos;
            if (SaveIntoMemory(address, IpEdit, 1)) {
                gu8SwStateCallbacksState = 4;
            }
            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, gu8LastIpSelect, &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                SetCurrentIpSelect(gu8LastIpSelect);
                return (1);
            }
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;

    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchRoomIpCallBack >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchRoomIpCallBack                                                        |
 | < @Description       : write switch room Ip in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchRoomIpCallBack() {
    return switchIps(&gstCallPointConfig.Rip, 0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < sw1Type >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void sw1Type                                                                 |
 | < @Description       : Frist switch type                                                            |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t sw1Type() {
    return switchTypeing(&gstCallPointConfig.SwitchHwType[0], 1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < sw2Type >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void sw2Type                                                                 |
 | < @Description       : second switch type                                                            |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t sw2Type() {
    return switchTypeing(&gstCallPointConfig.SwitchHwType[1], 2);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < sw3Type >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void sw3Type                                                                 |
 | < @Description       : three switch type                                                            |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t sw3Type() {
    return switchTypeing(&gstCallPointConfig.SwitchHwType[2], 3);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchDeActiveByIp >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchDeActiveByIp                                                        |
 | < @Description       : write switch id in config call Point                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchActiveByIp() {
    memAddresst_t address;
    uint8_t OptionCallBackState;
    OptionCallBackState = 0;
    if (lcdIsBusy()) {
        return (0);
    }
    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
            }
            break;
        case 1:
            /*load current switch state */
            address = MEMORY_START_SWITCH_DATA + (((getCurrentIpSelect() - 1) * sizeof (stCallPointData_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                lcdClear();
                WriteMessage(0, 48);
                if (gsCallPointData.State == SYSTEM_DEFALUT_EVENT) {
                    systemOptionRegisterData(2, 1, 24);
                } else {
                    systemOptionRegisterData(2, 0, 24);
                }
                gu8SwStateCallbacksState = 2;
            }
            break;
        case 2:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                if (SystemGetCurrentOption() == 0) {
                    gsCallPointData.State = SYSTEM_CANCEL_EVENT;

                } else {

                    gsCallPointData.State = SYSTEM_DEFALUT_EVENT;
                }
                gu8SwStateCallbacksState = 3;
                return (0);
            }

            break;
        case 3:
            address = MEMORY_START_SWITCH_DATA + (((getCurrentIpSelect() - 1) * sizeof (stCallPointData_t)) + 4);
            if (SaveIntoMemory(address, (uint8_t *) & gsCallPointData.State, 1)) {
                gu8SwStateCallbacksState = 4;
            }

            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchTypeing >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchTypeing                                                           |
 | < @Description       : switch type two Response                                                     |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t switchTypeing(uint8_t *EditSwitch, uint8_t memPos) {
    memAddresst_t address;
    uint8_t OptionCallBackState;
    OptionCallBackState = 0;
      if(lcdIsBusy()){
        return(0);
    }
    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
            }
            break;
        case 1:
            /*load current switch state */
            address = MEMORY_START_SWITCH_DATA + (((getCurrentIpSelect() - 1) * sizeof (stCallPointData_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                lcdClear();
                WriteMessage(0, 49);
                systemOptionRegisterData(6, *EditSwitch, 42);
                gu8SwStateCallbacksState = 2;
            }
            break;
        case 2:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                *EditSwitch = SystemGetCurrentOption();
                gu8SwStateCallbacksState = 3;
                return (0);
            }

            break;
        case 3:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t)) + memPos);
            if (SaveIntoMemory(address, EditSwitch, 1)) {
                gu8SwStateCallbacksState = 4;
            }

            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchBuzzerState >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchBuzzerState                                                           |
 | < @Description       : switch buzzer state                                                     |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchBuzzerState() {
    memAddresst_t address;
    uint8_t OptionCallBackState;
    OptionCallBackState = 0;
      if(lcdIsBusy()){
        return(0);
    }
    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
            }
            break;
        case 1:
            /*load current switch state */
            address = MEMORY_START_SWITCH_DATA + (((getCurrentIpSelect() - 1) * sizeof (stCallPointData_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                lcdClear();
                WriteMessage(0, 50);
                systemOptionRegisterData(2, gstCallPointConfig.Option.buzzerState, 40);
                gu8SwStateCallbacksState = 2;
            }
            break;
        case 2:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                gstCallPointConfig.Option.buzzerState = SystemGetCurrentOption();
                gu8SwStateCallbacksState = 3;
                return (0);
            }

            break;
        case 3:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t))) + 4;
            if (SaveIntoMemory(address, (uint8_t *) & gstCallPointConfig.Option, 1)) {
                gu8SwStateCallbacksState = 4;
            }

            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchDisabledSystem >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchDisabledSystem                                                           |
 | < @Description       : switchDisabledSystem                                                     |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchDisabledSystem() {
    memAddresst_t address;
    uint8_t OptionCallBackState;
    OptionCallBackState = 0;
      if(lcdIsBusy()){
        return(0);
    }
    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
            }
            break;
        case 1:
            /*load current switch state */
            address = MEMORY_START_SWITCH_DATA + (((getCurrentIpSelect() - 1) * sizeof (stCallPointData_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                lcdClear();
                WriteMessage(0, 51);
                systemOptionRegisterData(2, gstCallPointConfig.Option.DisapledSystem, 40);
                gu8SwStateCallbacksState = 2;
            }
            break;
        case 2:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                gstCallPointConfig.Option.DisapledSystem = SystemGetCurrentOption();
                gu8SwStateCallbacksState = 3;
                return (0);
            }

            break;
        case 3:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t))) + 4;
            if (SaveIntoMemory(address, (uint8_t *) & gstCallPointConfig.Option, 1)) {
                gu8SwStateCallbacksState = 4;
            }

            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < switchBuzzerTime >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void switchBuzzerTime                                                        |
 | < @Description       : switch buzer time                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t switchBuzzerTime() {
    uint8_t funCationStateCallBack;
    memAddresst_t address;
    if (lcdIsBusy()) {
        return (0);
    }
    switch (gu8SwStateCallbacksState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gstCallPointConfig, sizeof (stCallPointConfig_t))) {
                gu8SwStateCallbacksState = 1;
            }
            break;
        case 1:
            /*load current switch state */
            address = MEMORY_START_SWITCH_DATA + (((getCurrentIpSelect() - 1) * sizeof (stCallPointData_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsCallPointData, sizeof (stCallPointData_t))) {
                lcdClear();
                WriteMessage(0, 52);
                RegisterTypeAs3DigitOr5Digit(2, gstCallPointConfig.Option.buzzerTimeFactor);
                gu8SwStateCallbacksState = 2;
            }
            break;
        case 2:
            funCationStateCallBack = TypeCallBack();
            if (funCationStateCallBack == 1) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            if (funCationStateCallBack == 2) {
                if (!InvalidIpMesssage(TypeGetValue8Bit(), 60)) {
                    gu8SwStateCallbacksState = 5;
                    lcdClear();
                    WriteMessage(0, 57);
                    WriteMessage(1, 58);
                    CommanEventFunctions(NULL, NULL, NULL, NULL, afterErrorComm);
                } else {
                    gstCallPointConfig.Option.buzzerTimeFactor = TypeGetValue8Bit();
                    gu8SwStateCallbacksState = 3;
                }

            }
            break;

        case 3:
            address = MEMORY_START_SWITCH_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stCallPointConfig_t))) + 4;
            if (SaveIntoMemory(address, (uint8_t *) & gstCallPointConfig.Option, 1)) {
                gu8SwStateCallbacksState = 4;
            }
            break;
        case 4:
            if (SWOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gstCallPointConfig, &gsCallPointData, true)) {
                gu8SwStateCallbacksState = 0;
                return (1);
            }
            break;
        case 5:
            break;
        default:
            gu8SwStateCallbacksState = 0;
            break;
    }
    return (0);
}