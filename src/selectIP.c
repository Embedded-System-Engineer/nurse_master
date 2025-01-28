#include "appRes.h"
/*
 * <@var select Ip state
 */
static uint8_t gu5SelectIpState;
/*
 * <@var current Select Ip
 */
static uint8_t gu8CurrentSelectIP;



/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SelectIpCencelErrorMessage >                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SelectIpCencelErrorMessage                                               |
 | < @Description       : run when Error message event                                                  |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SelectIpCencelErrorMessage();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < selectIpCallback >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void selectIpCallback                                                         |
 | < @Description       : run at any selct Ip System                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t selectIpCallback() {
    uint8_t TypeCallState = 0;
      if(lcdIsBusy()){
        return(0);
    }
    switch (gu5SelectIpState) {
        case 0:

            lcdClear();
            WriteMessage(0, 0);
            RegisterTypeAs3DigitOr5Digit(3, (uint16_t) gu8CurrentSelectIP);
            gu5SelectIpState = 1;
            break;
        case 1:
            TypeCallState = TypeCallBack();
            if (TypeCallState == 1) {
                /*exeuate cencel of the current*/
                gu5SelectIpState = 0;
                gu8CurrentSelectIP = 0;
                return (1);
            }

            if (TypeCallState == 2) {
                gu5SelectIpState = 0;
                if (!InvalidIpMesssage(TypeGetValue16Bit(), MAX_DEVICE_USED)) {
                    gu8CurrentSelectIP = 0;
                    CommanEventFunctions(NULL, NULL, NULL, NULL, SelectIpCencelErrorMessage);
                    gu5SelectIpState = 2;
                } else {
                    gu8CurrentSelectIP = (uint8_t) TypeGetValue16Bit();
                    return (2);
                }
            }
            break;
        case 2:
            break;
        default:
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < InvalidIpMesssage >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InvalidIpMesssage                                                             |
 | < @Description       : get Ip is Valid Or Not and write Message                                                   |      
 | < @return            : 0 write Error Message , 1 Ip is valid                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t InvalidIpMesssage(uint16_t Ip, uint8_t Max) {
    uint8_t start;
    uint8_t buf[3];
    if (Ip > 0 && Ip < Max) {
        return (1);
    } else {
        lcdNoBlink();
        lcdClear();
        start = u8TOASII(buf, Max - 1);
        lcdwritebuf(1, 11, buf + start, 3 - start);
        LcdWriteIndex((30 - start), ']');
        WriteMessage(0, 1);
        WriteMessage(1, 2);
        return (0);
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < selectIpInit >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void selectIpInit                                                             |
 | < @Description       : initall variables of the f                                                    |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void selectIpInit() {
    gu5SelectIpState = 0;
    gu8CurrentSelectIP = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SelectIpCencelErrorMessage >                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SelectIpCencelErrorMessage                                               |
 | < @Description       : run when Error message event                                                  |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void SelectIpCencelErrorMessage() {
    gu8CurrentSelectIP = 0;
    ReturnMenuCallBack();
    gu5SelectIpState = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCurrentIpSelect >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void getCurrentIpSelect                                                       |
 | < @Description       : get current Ip Select From User                                               |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getCurrentIpSelect() {
    return gu8CurrentSelectIP;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCurrentIpSelect >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void getCurrentIpSelect                                                       |
 | < @Description       : get current Ip Select From User                                               |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void resetCurrentIP() {
    gu8CurrentSelectIP = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < SetCurrentIpSelect >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SetCurrentIpSelect                                                       |
 | < @Description       : set value of the currentIp                                              |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void SetCurrentIpSelect(uint8_t Ip) {
    gu8CurrentSelectIP = Ip;
}

