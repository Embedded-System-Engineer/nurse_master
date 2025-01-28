
#include "appRes.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Variables>                                                       |
 --------------------------------------------------------------------------------------------------------
 */
/*
 *<@var : load Ip state
 */
static uint8_t gu8LoadIpState;
/*
 * <@var : current address select
 */
static uint8_t gu8CurrentAddressSelect;
/*
 * <@var Wait Fro Response Command
 */
static stTimer_TimeOut_t gsLoadConfigTimeOut;
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  loadIpErrorCencel>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   loadIpErrorCencel                                                      |
 | < @Description       : load Ip Error Cencel                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void loadIpErrorCencel();

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  loadIpCallBack>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   loadIpCallBack                                                         |
 | < @Description       : run this callback to active data                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t loadIpCallBack() {
    uint8_t funCationStateCallBack;
    uint8_t start;
    uint8_t buf[3];
    uint8_t lcdbuf[15];
    uint8_t strlength;
    uint8_t setIpState;
    if (lcdIsBusy()) {
        return (0);
    }
    switch (gu8LoadIpState) {
        case 0:
            lcdClear();
            start = u8TOASII(buf, (csmaGetMaxAddress() - 1));
            strlength = appPrintMessage(lcdbuf, 0, 23);
            copyBuff(lcdbuf + strlength, buf + start, 3 - start);
            lcdwritebuf(0, 0, lcdbuf, strlength + 3 - start);
            RegisterTypeAs3DigitOr5Digit(3, gu8CurrentAddressSelect);
            lcdUpdateNow();
            gu8LoadIpState = 1;
            break;
        case 1:
            funCationStateCallBack = TypeCallBack();
            if (funCationStateCallBack == 1) {
                gu8LoadIpState = 0;
                return (1);
            }
            if (funCationStateCallBack == 2) {
                if (!InvalidIpMesssage(TypeGetValue16Bit(), csmaGetMaxAddress())) {
                    gu8LoadIpState = 3;
                    CommanEventFunctions(NULL, NULL, NULL, NULL, loadIpErrorCencel);
                } else {
                    gu8CurrentAddressSelect = (uint8_t) TypeGetValue16Bit();
                    RegisterAfterError(loadIpErrorCencel);
                    gu8LoadIpState = 2;
                }
            }
            break;
        case 2:
            /*request start config*/
            if (StartConfig(gu8CurrentAddressSelect, 0)) {/*go to wait state For ResPonse*/
                gu8LoadIpState = 4;
                sysSetPeriodMS(&gsLoadConfigTimeOut, 100);
            }
            break;
        case 3:
            break;
        case 4:
            /*wait for ResPonse*/
            if (sysIsTimeoutMs(&gsLoadConfigTimeOut) == 0) {
                ReturnMenuCallBack();
                CommanEventFunctions(NULL, NULL, NULL, NULL, loadIpErrorCencel);
                gu8LoadIpState = 3;
                lcdNoBlink();
                lcdClear();
                WriteMessage(0, 21);
                WriteMessage(1, 22);
            }
            break;
        case 5:
            setIpState = selectIpCallback();
            if (setIpState == 1) {
                gu8LoadIpState = 7;
                return (0);
            }

            if (setIpState == 2) {
                gu8LoadIpState = 6;
            }
            break;
        case 6:/*loadIp Command*/
            if (LoadIpRequest(gu8CurrentAddressSelect, getCurrentIpSelect())) {
                gu8LoadIpState = 0;
                resetCurrentIP();
                gu8CurrentAddressSelect = 0;
                return (1);
            }
            break;
        case 7:
            if (StartConfig(gu8CurrentAddressSelect, 1)) {/*go to wait state For ResPonse*/
                gu8CurrentAddressSelect = 0;
                resetCurrentIP();
                gu8LoadIpState = 0;
            }
            break;

        default:
            break;
    }

    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  loadIpErrorCencel>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   loadIpErrorCencel                                                      |
 | < @Description       : load Ip Error Cencel                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void loadIpErrorCencel() {
    gu8CurrentAddressSelect = 0;
    gu8LoadIpState = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  loadIpGetIpShowWithIp>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   loadIpGetIpShowWithIp                                                      |
 | < @Description       : Get Message                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void loadIpGetIpShowWithIp(uint8_t Ip) {
    SetCurrentIpSelect(Ip);
    gu8LoadIpState = 5;
}
