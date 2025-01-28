#include "appRes.h"


/*
 <@var displayState
 */
static uint8_t gu8DisplayCallBacksState;
/*
 <@var display config status
 */
static stDisplayConfig_t gsDisplayConfig;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < DisplayErrorCencel >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void DisplayErrorCencel                                                        |
 | < @Description       : display error case                                          |      
 | < @return             : void                                                    |
 --------------------------------------------------------------------------------------------------------
 */
static void DisplayErrorCencel();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < DispalyMainID >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void DispalyMainID                                                        |
 | < @Description       : main view of the display                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t DispalyMainID() {
    memAddresst_t address;
    uint8_t OptionCallBackState;
    OptionCallBackState = 0;
    if (lcdIsBusy()) {
        return (0);
    }

    switch (gu8DisplayCallBacksState) {
        case 0:
            address = MEMORY_START_DISPLAY_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stDisplayConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsDisplayConfig, sizeof (stDisplayConfig_t))) {
                gu8DisplayCallBacksState = 1;
                lcdClear();
                WriteMessage(0, 56);
                systemOptionRegisterData(2, gsDisplayConfig.Option.MainView, 33);
            }
            break;
        case 1:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8DisplayCallBacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                gsDisplayConfig.Option.MainView = SystemGetCurrentOption();
                gu8DisplayCallBacksState = 2;
                return (0);
            }

            break;
        case 2:
            address = MEMORY_START_DISPLAY_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stDisplayConfig_t)));
            if (SaveIntoMemory(address, (uint8_t *) & gsDisplayConfig.Option, 1)) {
                gu8DisplayCallBacksState = 3;
            }
            break;
        case 3:
            if (DisplayOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gsDisplayConfig)) {
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

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < DISPLAYTimeScoller >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void DISPLAYTimeScoller                                                        |
 | < @Description       : dispaly set scoller message                                          |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t DISPLAYTimeScoller() {
    uint8_t funCationStateCallBack;
    uint8_t OptionCallBackState = 0;
    static uint8_t currentIp = 0;
    memAddresst_t address;
    if (lcdIsBusy()) {
        return (0);
    }
    switch (gu8DisplayCallBacksState) {
        case 0:
            address = MEMORY_START_DISPLAY_CONFIG + (getCurrentIpSelect() - 1) * sizeof (stDisplayConfig_t);
            if (LoadFromMemory(address, (uint8_t *) & gsDisplayConfig, sizeof (stDisplayConfig_t))) {
                gu8DisplayCallBacksState = 1;
                RegisterTypeAs3DigitOr5Digit(3, 0);
                lcdClear();
                WriteMessage(0, 35); /**/
            }
            break;
        case 1:
            funCationStateCallBack = TypeCallBack();
            if (funCationStateCallBack == 1) {
                gu8DisplayCallBacksState = 0;
                return (1);
            }
            if (funCationStateCallBack == 2) {
                if (!InvalidIpMesssage(TypeGetValue8Bit(), MAX_DEVICE_USED)) {
                    gu8DisplayCallBacksState = 3;
                    lcdClear();
                    WriteMessage(0, 59);
                    WriteMessage(1, 60);
                    CommanEventFunctions(NULL, NULL, NULL, NULL, DisplayErrorCencel);
                } else {
                    currentIp = TypeGetValue8Bit() - 1;
                    systemOptionRegisterData(2, bitRead(gsDisplayConfig.activeIps[currentIp >> 3], currentIp & 7), 68);
                    gu8DisplayCallBacksState = 2;
                }

            }
            break;
        case 2:
            //show option
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8DisplayCallBacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                uint8_t value = SystemGetCurrentOption();

                if (value) {
                    bitSet(gsDisplayConfig.activeIps[currentIp >> 3], currentIp & 7);
                } else {
                    bitClear(gsDisplayConfig.activeIps[currentIp >> 3], currentIp & 7);
                }
                gu8DisplayCallBacksState = 4;
                return (0);
            }

            break;
        case 3:/*valid*/
            break;
        case 4:
            address = MEMORY_START_DISPLAY_CONFIG + (getCurrentIpSelect() - 1) * sizeof (stDisplayConfig_t);
            if (SaveIntoMemory(address, (uint8_t *) & gsDisplayConfig, sizeof (stDisplayConfig_t))) {
                gu8DisplayCallBacksState = 5;
            }
            break;
        case 5:
            if (DisplayOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gsDisplayConfig)) {
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

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < DisplayErrorCencel >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void DisplayErrorCencel                                                        |
 | < @Description       : display error case                                          |      
 | < @return             : void                                                    |
 --------------------------------------------------------------------------------------------------------
 */
static void DisplayErrorCencel() {
    ReturnMenuCallBack();
    gu8DisplayCallBacksState = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < DispalyDandogState >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void DispalyDandogState                                                        |
 | < @Description       : main view of the display                                         |      
 | < @return            : 0 is ruun and 1 is done                                                      |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t DispalyDandogState() {
    memAddresst_t address;
    uint8_t OptionCallBackState;
    OptionCallBackState = 0;
      if(lcdIsBusy()){
        return(0);
    }
    switch (gu8DisplayCallBacksState) {
        case 0:
            address = MEMORY_START_DISPLAY_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stDisplayConfig_t)));
            if (LoadFromMemory(address, (uint8_t *) & gsDisplayConfig, sizeof (stDisplayConfig_t))) {
                gu8DisplayCallBacksState = 1;
                lcdClear();
                WriteMessage(0, 55);
                systemOptionRegisterData(2, gsDisplayConfig.Option. dangdongState, 40);
            }
            break;
        case 1:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8DisplayCallBacksState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                gsDisplayConfig.Option.dangdongState = SystemGetCurrentOption();
                gu8DisplayCallBacksState = 2;
                return (0);
            }

            break;
        case 2:
            address = MEMORY_START_DISPLAY_CONFIG + (((getCurrentIpSelect() - 1) * sizeof (stDisplayConfig_t))) + 1;
            if (SaveIntoMemory(address, (uint8_t *) & gsDisplayConfig.Option, 1)) {
                gu8DisplayCallBacksState = 3;
            }
            break;
        case 3:
            if (DisplayOnReq(RequestFrame, 0xFF, getCurrentIpSelect(), &gsDisplayConfig)) {
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