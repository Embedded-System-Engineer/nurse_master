#include "../inc/appRes.h"


/*
 <@var Time of show Data on display
 */
static uint16_t gu16Period[2];
/*
 <@var number of repeat Period
 */
static uint8_t gu8Duration;

static uint8_t gu8State = 0;

static QueueItem *display_item;
/*
 * <@var time traget is done
 */
static stTimer_TimeOut_t gstFrequncy;

static void lcdWrite();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimePlay>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimePlay                                                           |
 | < @Description         : flahing data Into buffer                                                    |   
 | < @Param swID          : Switch id  display data show                                                |
 | < @PAram RID           : room id display data show                                                   |
 | < @Param Period        : Time Required Ton and off display                                           |
 | < @Param  Toff         : off Time of the Display                                                     |
 | < @Param duration      : number of repeat counter                                                    |
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimePlay(QueueItem *item, uint16_t Period, uint16_t Ton, uint8_t duration) {
    gu16Period[0] = Ton;
    gu16Period[1] = Period - Ton;
    gu8Duration = duration;
    gu8State = 1;
    display_item = item;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimeCallBack>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimeCallBack                                                       |
 | < @Description         : run task in background                                                      |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimeCallBack() {

    if (SystemIsSerial() == false) {
        return;
    }
    if (lcdIsBusy()) {
        return;
    }

    switch (gu8State) {
        case 0:
            break;
        case 1: //start state 
            if (gu8Duration == 0) {
                gu8State = 0;
                return;
            }

            if (gu16Period[0] != 0) {
                lcdWrite();
            }
            sysSetPeriodMS(&gstFrequncy, gu16Period[0]);
            gu8State = 2;
            return;


            if (gu16Period[1] != 0) {
                if (menuIsOpen() == 0) {
                    lcdClearlines(1);
                    lcdUpdateNow();
                }
                sysSetPeriodMS(&gstFrequncy, gu16Period[1]);
                gu8State = 3;
                return;
            }



            break;
        case 2: //on time
            if (sysIsTimeoutMs(&gstFrequncy) == 0) {
                if (gu16Period[1] != 0) {
                    lcdClearlines(1);
                    sysSetPeriodMS(&gstFrequncy, gu16Period[1]);
                    gu8State = 3;
                    return;
                }
                gu8State = 1;
                gu8Duration--;
            }
            break;
        case 3: // off time
            if (sysIsTimeoutMs(&gstFrequncy) == 0) {
                gu8State = 1;
                gu8Duration--;
            }
            break;
        default:
            break;

    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimeInit>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimeInit                                                           |
 | < @Description         : init all data into this file                                                |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimeInit() {
    gu8State = 0;
    gu8Duration = 0;
    gu16Period[0] = 0;
    gu16Period[1] = 0;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <systemIsDateTimeReady>                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void systemIsDateTimeReady                                                          |
 | < @Description         : get status of the timing of the Data                                        |      
 | < @return              : 0 done , 1 is busy                                                          |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t systemIsDateTimeReady() {
    return gu8State;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <systemIsDateTimeStop>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void systemIsDateTimeStop                                                   |
 | < @Description         : stop running time                                                           |      
 | < @return              : 0 done , 1 is busy                                                          |          
 --------------------------------------------------------------------------------------------------------
 */
void systemDateTimeStop() {
    gu16Period[0] = 0;
    gu16Period[1] = 0;
    gu8Duration = 0;
    gu8State = 0; /*Reset all Data*/
}

static void lcdWrite() {
    if (menuIsOpen()) {
        return;
    }

    if (AcceptIpIsRun() != 0) {
        return;
    }
    
    //write data IP and bed number and room number
    uint8_t buf[LCD_NUMBER_OF_BYTE];
    uint8_t buf2[5];
    uint8_t start = 0;
    lcdClear();
    lcdNoBlink();
    /*write Data into Line 0*/
    setBuff(buf, ' ', LCD_NUMBER_OF_BYTE);
    uint8_t currentIndex = 28 + display_item->State;
    appPrintMessage(buf, 0, currentIndex);
    start = u8TOASII(buf2, display_item->address);
    copyBuff(buf + 12, buf2 + start, 3 - start);
    lcdwritebuf(0, 0, buf, LCD_NUMBER_OF_BYTE);
    /*write Data into Line 1*/
    setBuff(buf, ' ', LCD_NUMBER_OF_BYTE);
    appPrintMessage(buf, 0, 26);
    start = u16TOASII(buf2, display_item->swId);
    copyBuff(buf + 4, buf2 + start, 5 - start);
    appPrintMessage(buf + 9, 0, 27);
    start = u16TOASII(buf2, display_item->RId);
    copyBuff(buf + 13, buf2 + start, 5 - start);
    lcdwritebuf(1, 0, buf, LCD_NUMBER_OF_BYTE);
    lcdUpdateNow();
}