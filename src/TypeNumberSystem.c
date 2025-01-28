
/*
 
 */
#include "appRes.h"



/*
 * <@var IpSelected by Inpt user
 */
static uint16_t gu16Type;
/*
 * <@var IP select State
 */
static uint8_t gu8TypeState;
/*
 * <@var typeing select IP
 */
static uint16_t gu16TypeEdit;
/*
 * <@var typeing select IP
 */
static uint16_t gu16LastDataEdit;
/*
 * <@var typeing select IP
 */
static uint8_t gu8TypeLCDPOS;
/*
 * <@var typeing select IP
 */
static uint8_t gu8TypeLCDMAXDIGIT;
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeCencel >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeCencel                                                      |
 | < @Description       : cencel event when select your IP                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeCencel();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeEnter >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeEnter                                                           |
 | < @Description       : saved select Ip and open options                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeEnter();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeF1 >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeF1                                                           |
 | < @Description       : move blinking of the IP to next                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeF1();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeF2 >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeF2                                                           |
 | < @Description       : move blinking of the IP to Pervious                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeF2();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeF3>                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeF3                                                              |
 | < @Description       : remove Last Index                                                             |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeF3();

/*
 * Functions
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeCencel >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeCencel                                                      |
 | < @Description       : cencel event when select your IP                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeCencel() {
    gu8TypeState = 3;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeEnter >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeEnter                                                           |
 | < @Description       : saved select Ip and open options                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeEnter() {
    if (gu16TypeEdit == 0) {
        gu16Type = gu16LastDataEdit;
    } else {
        gu16Type = gu16TypeEdit;
    }
    gu8TypeState = 2;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeNumber >                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeNumber                                                             |
 | < @Description       : write number and show In LCD                                                  |    
 | < @Param State       : number Put In 5 Digit                                                         |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeNumber(uint8_t s) {
    uint8_t start;
    uint8_t buf[5];
    if (gu8TypeLCDPOS >= gu8TypeLCDMAXDIGIT) {
        gu8TypeLCDPOS = 0;
        gu16TypeEdit = 0;
    }

    lcdClearlines(1);
    gu16TypeEdit = gu16TypeEdit * 10 + (s - '0');
    start = u16TOASII(buf, gu16TypeEdit);
    lcdwritebuf(1, 0, buf + start, 5 - start);
    gu8TypeLCDPOS++;
    lcdBlink(1, gu8TypeLCDPOS);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeF1 >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeF1                                                           |
 | < @Description       : move blinking of the IP to next                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeF1() {
    if (gu16TypeEdit == 0) {
        return;
    }
    gu8TypeLCDPOS++;
    if (gu8TypeLCDPOS >= gu8TypeLCDMAXDIGIT) {
        gu8TypeLCDPOS = 0;
    }
    lcdBlink(1, gu8TypeLCDPOS);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeF2 >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeF2                                                           |
 | < @Description       : move blinking of the IP to Pervious                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeF2() {
    if (gu16TypeEdit == 0) {
        return;
    }

    if (gu8TypeLCDPOS != 0) {
        gu8TypeLCDPOS--;
        lcdBlink(1, gu8TypeLCDPOS);
        lcdUpdateNow();
        return;
    }
    lcdBlink(1, gu8TypeLCDPOS);
    lcdUpdateNow();
    gu8TypeLCDPOS = gu8TypeLCDMAXDIGIT - 1;



}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeF3>                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeF3                                                              |
 | < @Description       : remove Last Index                                                             |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeF3() {
    uint8_t start;
    uint8_t buf[5];
    lcdClearlines(1);
    if (gu16TypeEdit != 0) {
        gu16TypeEdit = (gu16TypeEdit / 10);
        start = u16TOASII(buf, gu16TypeEdit);
        lcdwritebuf(1, 0, buf + start, 5 - start);
        if (gu8TypeLCDPOS != 0) {
            gu8TypeLCDPOS--;
        }
    } else {
        LcdWriteIndex(16, '0');
    }
    lcdBlink(1, gu8TypeLCDPOS);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeInit>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeInit                                                            |
 | < @Description       : Init all data Into file                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void TypeInit() {
    gu16TypeEdit = 0;
    gu8TypeLCDPOS = 0;
    gu16Type = 0;
    gu8TypeState = 0;
    gu8TypeLCDMAXDIGIT = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeCallBack>                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeCallBack                                                           |
 | < @Description       : call this function when write uint8 data or uint16Data                        |                                                  |                                                           
 | < @return            : retun Case if 0 is ruuning , 1 is cencel , 2 is Enter                         |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t TypeCallBack() {
    /*retu*/
    uint8_t start;
    uint8_t buf[5];
    switch (gu8TypeState) {
        case 0:
            setBuff(buf, '0', 5);
            ReturnMenuCallBack();
            CommanEventFunctions(TypeF1, TypeF2, TypeF3, TypeEnter, TypeCencel);
            CommanEventHandles(TypeNumber);
            lcdClearlines(1);
            start = u16TOASII(buf, gu16LastDataEdit);
            lcdwritebuf(1, 0, buf + start, 5 - start);
            gu8TypeLCDPOS = 0;
            lcdBlink(1, gu8TypeLCDPOS);
            lcdUpdateNow();
            gu8TypeState = 1;
            break;
        case 1:
            break;
        case 2:
            ReturnMenuCallBack();
            gu8TypeState = 0;
            gu16TypeEdit = 0;
            gu8TypeLCDMAXDIGIT = 0;
            gu8TypeLCDPOS = 0;
            return (2);
            break;
        case 3:
            ReturnMenuCallBack();
            gu8TypeState = 0;
            gu16TypeEdit = 0;
            gu16Type = 0;
            gu8TypeLCDMAXDIGIT = 0;
            gu8TypeLCDPOS = 0;
            return (1);
            break;
        default:
            gu8TypeState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  RegisterTypeAs3DigitOr5Digit>                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   RegisterTypeAs3DigitOr5Digit                                           |
 | < @Description       : define max digit show in LCD nad casting to                                   |       
 | < @Param MaxDigit    : max Digit show in LCD                                                         |
 | < @Param StartShow   : Inialize the Edit data                                                        |                                                             
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void RegisterTypeAs3DigitOr5Digit(uint8_t MaxDigit, uint16_t StartshowData) {
    gu16TypeEdit = 0;
    gu16LastDataEdit = StartshowData;
    gu8TypeLCDMAXDIGIT = MaxDigit;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeGetValue8Bit >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeGetValue8Bit                                                           |
 | < @Description       : get type in LCD with 3 Digit                                            |                                                  |                                                           
 | < @return            : return 0 to 255                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t TypeGetValue8Bit() {
    return (uint8_t) gu16Type;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeGetValue16Bit >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeGetValue16Bit                                                           |
 | < @Description       : get type in LCD with 5 Digit                                            |                                                  |                                                           
 | < @return            : return 0 to 2^16 -1                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
uint16_t TypeGetValue16Bit() {
    return gu16Type;
}
