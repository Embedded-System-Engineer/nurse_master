
#include "appRes.h"
/*
 * <@var OptionPos
 */
static int8_t gu8OptionPos;
/*
 *<@var max option
 */
static uint8_t gu8MaxOptions;
/*
 * <@var start messgae Index
 */
static uint8_t gu8StartMessgaeIndex;
/*
 * <@var start messgae Index
 */
static uint8_t gu8StartMessageState;

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionF1 >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionF1                                                           |
 | < @Description       : Increment                                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionF1();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionF1 >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionF2                                                           |
 | < @Description       : decment the index Option                                                      |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionF2();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionCencel >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionCencel                                                       |
 | < @Description       : cencel the change Option                                                      |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionCencel();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionEnter >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionEnter                                                           |
 | < @Description       : Enter Action to save Option n memory or other action                                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionEnter();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < OptionSystemInit >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void OptionSystemInit                                                         |
 | < @Description       : init variables in all files                                                   |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void OptionSystemInit() {
    gu8MaxOptions = 0;
    gu8OptionPos = 0;
    gu8StartMessgaeIndex = 0;
    gu8StartMessageState = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < systemOptionRegisterData >                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void systemOptionRegisterData                                                 |
 | < @Description       : define system Option by three variable                                        |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void systemOptionRegisterData(uint8_t MAX, uint8_t StartPos, uint8_t startMessageIndex) {
    gu8MaxOptions = MAX;
    gu8OptionPos = StartPos;
    gu8StartMessgaeIndex = startMessageIndex;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < systemOptionCallBack >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void systemOptionCallBack                                                     |
 | < @Description       : mcall back run in any Option system                                           |      
 | < @return            : 0 is run , 1 is cencel , 2 is Enter                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t systemOptionCallBack() {
    switch (gu8StartMessageState) {
        case 0:
            ReturnMenuCallBack();
            CommanEventFunctions(SystemOptionF1, SystemOptionF2, NULL, SystemOptionEnter, SystemOptionCencel);
            gu8StartMessageState = 1;
            break;
        case 1:
            lcdNoBlink();
            lcdClearlines(1);
            WriteMessage(1, gu8StartMessgaeIndex + gu8OptionPos);
            gu8StartMessageState = 2;
            break;
        case 2:
            break;
        case 3:
            ReturnMenuCallBack();
            gu8OptionPos = 0;
            gu8StartMessageState = 0;
            return (0x01);
            break;
        case 4:
            ReturnMenuCallBack();
            gu8StartMessageState = 0;
            return (0x02);
            break;
        default:
            SystemOptionCencel();
            break;


    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionF1 >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionF1                                                           |
 | < @Description       : Increment the Otion to reach a max                                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionF1() {
    gu8OptionPos++;
    if (gu8OptionPos >= gu8MaxOptions) {
        gu8OptionPos = 0;
    }
    gu8StartMessageState = 1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionF1 >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionF2                                                           |
 | < @Description       : decment the index Option                                                      |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionF2() {
    gu8StartMessageState = 1;
    if (gu8OptionPos != 0) {
        gu8OptionPos--;
        return;
    }
    gu8OptionPos = gu8MaxOptions - 1;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemGetCurrentOption >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemGetCurrentOption                                                       |
 | < @Description       : get current option                                                      |      
 | < @return            : option Index                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemGetCurrentOption() {
    uint8_t currentPos;
    currentPos = gu8OptionPos;
    gu8OptionPos = 0;
    return currentPos;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionCencel >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionCencel                                                       |
 | < @Description       : cencel the change Option                                                      |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionCencel() {
    gu8OptionPos = 0;
    gu8StartMessageState = 3;
    gu8StartMessgaeIndex = 0;
    gu8MaxOptions = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SystemOptionEnter >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemOptionEnter                                                           |
 | < @Description       : Enter Action to save Option n memory or other action                                                                     |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SystemOptionEnter() {
    gu8StartMessgaeIndex = 0;
    gu8MaxOptions = 0;
    gu8StartMessageState = 4;
}

