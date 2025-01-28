
#include "appRes.h"


static uint8_t gu8TpeSate = 0;
static uint8_t password [4];
static int8_t forntPassword = 0;
static int8_t realPassword = -1;
static uint8_t sizePassword = 0;
static uint8_t displayUpdateState = 0;
static uint8_t currentIndex = 0;
static stTimer_TimeOut_t gsPasswordTimeOut;


static void resetPassword();

static uint8_t InvalidPassword(uint8_t *password, uint8_t currentLength, uint8_t type) {
    //day + month
    uint16_t num = 0;
    uint16_t valid_number = 0;
    uint8_t day[3];
    uint8_t validpassword[4];
    uint8_t start = 0;
    uint8_t day_length = 0;
    for (uint8_t i = 0; i < currentLength; i++) {
        num = (num * 10UL) +((uint8_t) ((password[i] - '0')));
    }


    tm_t date;
    time_t time = systemNow();
    DateTimeFromTimeStamp(&date, time);
    //get day form passowd
    if (type) {
        start = u8TOASII(day, date.tm_hour); //hour + day
    } else {
        start = u8TOASII(day, date.tm_mday); //day + month
    }
    copyBuff(validpassword, day + start, 3 - start);
    day_length = 3 - start;
    if (type) {
        start = u8TOASII(day, date.tm_mday); //hour + day
    } else {
        start = u8TOASII(day, date.tm_mon); //day + month
    }
    copyBuff(validpassword + day_length, day + start, 3 - start);
    day_length += (3 - start); //total length
    for (uint8_t i = 0; i < day_length; i++) {
        valid_number = (valid_number * 10UL) +((uint8_t) ((validpassword[i] - '0')));
    }
    if (valid_number == num) {
        return (1);
    }
    return (0);


}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeCencel >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeCencel                                                      |
 | < @Description       : cencel event when select your IP                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeCencelPassword() {
    gu8TpeSate = 3;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  TypeCencel >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   TypeCencel                                                      |
 | < @Description       : cencel event when select your IP                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void TypeEnterPassword() {
    gu8TpeSate = 2;
}

void enqueuePassword(char value) {
    if (sizePassword < 4) {
        realPassword = (realPassword + 1) % 4;
        password[realPassword] = value;
        sizePassword++;
    }
}

char dequeue() {
    if (sizePassword > 0) {
        char value = password[forntPassword];
        forntPassword = (forntPassword + 1) % 4;
        sizePassword--;
        return value;
    }
    return '\0'; // Return null character if queue is empty
}

static void RemoveLastChar() {
    dequeue();
    displayUpdateState = 3;
}

static void TypePassword(uint8_t p) {

    if (gu8TpeSate == 4) {
        resetPassword();
    }

    if (sizePassword == 4) {
        dequeue(); // Remove the oldest character if the queue is full
    }
    enqueuePassword(p);
    displayUpdateState = 3;
}

static void resetPassword() {
    forntPassword = 0;
    realPassword = -1;
    sizePassword = 0;
    currentIndex = 0;
    displayUpdateState = 0;
    setBuff(password, '0', 4);
    lcdClear();
    WriteMessage(0, 63);
    ReturnMenuCallBack();
    CommanEventFunctions(RemoveLastChar, NULL, NULL, TypeEnterPassword, TypeCencelPassword);
    CommanEventHandles(TypePassword);
    gu8TpeSate = 1;
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
static void passwordErrorCencel() {
    gu8TpeSate = 0;
}

static void updateDisplay() {

    if (lcdIsBusy()) {
        return;
    }


    switch (displayUpdateState) {
        case 0:
            break;
        case 1:
            if (sysIsTimeoutMs(&gsPasswordTimeOut) == 0) {
                lcdwritebuf(1, 6 + currentIndex, &password[(forntPassword + currentIndex) % 4], 1);
                lcdUpdateNow();
                sysSetPeriodMS(&gsPasswordTimeOut, 150);
                displayUpdateState = 2;
            }
            break;
        case 2:
            if (sysIsTimeoutMs(&gsPasswordTimeOut) == 0) {
                uint8_t byte = '*';
                lcdwritebuf(1, 6 + currentIndex, &byte, 1);
                sysSetPeriodMS(&gsPasswordTimeOut, 1);
                lcdUpdateNow();
                currentIndex++;
                displayUpdateState = 0;
            }
            break;
        case 3:
            if (currentIndex >= 4) {
                setBuff(password, '0', 4); //clear password to zero
                lcdClearlines(1);
                currentIndex = 0;
            }
            displayUpdateState = 1;
            break;
        default:
            break;
    }

}

static uint8_t passwaordCallbackGeneration(uint8_t type) {
    if (lcdIsBusy()) {
        return (0);
    }
    switch (gu8TpeSate) {
        case 0:
            resetPassword();

            break;
        case 1://write password
            updateDisplay();
            break;
        case 2:
            if (InvalidPassword(password, sizePassword, type)) {
                gu8TpeSate = 0;
                return (1);
            } else {
                //show error message
                lcdClear();
                WriteMessage(0, 64);
                WriteMessage(1, 65);
                ReturnMenuCallBack();
                CommanEventFunctions(NULL, NULL, NULL, NULL, passwordErrorCencel);
                CommanEventHandles(TypePassword);
                gu8TpeSate = 4;
            }
            break;
        case 3:
            gu8TpeSate = 0;
            if (!type) {
                CencelCurrentMenue();
                return (1);
            } else {
                return (2);
            }
            break;
        case 4:
            break;
        default:
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  general password  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   general password                                                         |
 | < @Description       : run this callback to active data                                              |                                                  |                                                           
 | < @return            : 0 is run , one is done                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t GeneralPasswordCallback() {
    return passwaordCallbackGeneration(0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            <  custome password  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   custome password                                                         |
 | < @Description       : run this callback to active data                                              |                                                  |                                                           
 | < @return            : 0 is run , one is done                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t CustomPasswordCallback() {
    return passwaordCallbackGeneration(1);
}
