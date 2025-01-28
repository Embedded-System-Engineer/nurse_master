


#include "../inc/appRes.h"

/*
 *<@var scoller Message
 */
static uint8_t gu8ProductLCDScoller[LCD_NUMBER_OF_BYTE];

static const time_t scrollTime = 3000;

static bool gu8Buzzer = 0;

static bool gu8GeneralBuzzerActive = 0;

static uint8_t gu8BuzzerState = 0;

static uint8_t gu8UserAcceptState = 0;

static uint8_t gu8AcceptIpState = 0;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Variables>                                                |
 --------------------------------------------------------------------------------------------------------
 */

/*
 *<@var user Indicator System
 */
static CommandType gu8UserSystem;
/*
 *user Last Indicator System 
 */
static uint8_t gu8OnPeriodIsDone;
/*
 * < @var Timer-Flashing Data
 */
static uint8_t gu8ToggleState;
/*
 * Pointer to Read current Data
 */
static QueueItem item;


/*
 s
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Function Definitions>                                                |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static void cancelState();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onUserEMG>                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onUserEMG                                                             |
 | < @Description         : user indicator at emg events                                               |      
 | < @return              : void                                                                       |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t onUserEMG();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static void cancelItemByItem();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onUserCall>                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onUserCall                                                             |
 | < @Description         : user indicator at call events                                               |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t onUserCall();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < MainNumbersEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void MainNumbersEvent                                                        |
 | < @Description       : Main specific Lable by Main Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void MainShow();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Function >                                                |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onUserEMG>                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onUserEMG                                                             |
 | < @Description         : user indicator at emg events                                               |      
 | < @return              : void                                                                       |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t onUserEMG() { /*get Feed back*/
    time_t PeriodToggle;
    time_t PeriodFixed;

    switch (gu8ToggleState) {
        case 0:
            PeriodToggle = (30 * scrollTime) / 100;
            DataTimePlay(&item, (PeriodToggle >> 1), (PeriodToggle >> 2), 2);
            Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
            if (gu8Buzzer) {
                Toneplay(0, 400, 3, 200);
            }
            gu8ToggleState = 1;
            break;
        case 1:
            if (systemIsDateTimeReady() == 0) {
                Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
                PeriodFixed = (70 * scrollTime) / 100;
                DataTimePlay(&item, PeriodFixed, PeriodFixed, 1);
                if (gu8Buzzer) {
                    Toneplay(0, 400, 3, 200);
                }
                gu8ToggleState = 2;
            }
            break;
        case 2:
            if (systemIsDateTimeReady() == 0) {
                Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
                gu8ToggleState = 0;
                return (1);
            }
            break;
        default:
            gu8ToggleState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onUserCall>                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onUserCall                                                             |
 | < @Description         : user indicator at call events                                               |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t onUserCall() {

    if (gu8ToggleState == 0) {
        gu8ToggleState = 1;
        DataTimePlay(&item, scrollTime, scrollTime, 1);
        Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
        if (gu8Buzzer) {
            Toneplay(0, 1000, 3, 300);
        }
        return (0);
    }
    if (systemIsDateTimeReady() == 0) {
        Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
        gu8ToggleState = 0;
        return (1);
    }
    return (0);
}

static uint8_t onNewRequest() {

    if (gu8ToggleState == 0) {
        gu8ToggleState = 1;
        DataTimePlay(&item, 500, 250, 2);
        return (0);
    }
    if (systemIsDateTimeReady() == 0) {
        Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
        gu8ToggleState = 0;
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RegisterOnUserSystem >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function                   : void RegisterOnUserSystem                                            |
 | < @Description                : user indicator show                                                  |     
 | < @Param  State               : Register with direct state                                           |
 | < @return                     : void                                                                 |
 --------------------------------------------------------------------------------------------------------
 */

void setCurrentItem(QueueItem currentItem) {
    item = currentItem;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < RegisterOnUserSystem >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function                   : void RegisterOnUserSystem                                            |
 | < @Description                : user indicator show                                                  |     
 | < @Param  State               : Register with direct state                                           |
 | < @return                     : void                                                                 |
 --------------------------------------------------------------------------------------------------------
 */
void RegisterOnUserSystemState(CommandType State) {
    gu8OnPeriodIsDone = 0;
    gu8ToggleState = 0;
    gu8UserSystem = State;
    Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
    systemDateTimeStop();
    if (menuIsOpen()) {
        return;
    }

    if (gu8AcceptIpState) {
        return;
    }

    if (State != CANCEL_STATE) {
        ReturnMenuCallBack();
        CommanEventFunctions(cancelItemByItem, NULL, NULL, NULL, cancelState);
        KeypadRegisterEvent(MainModeEvent, 12);
    } else {
        MainInit();
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < MainNumbersEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void MainNumbersEvent                                                        |
 | < @Description       : Main specific Lable by Main Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void MainShow() {


    if (menuIsOpen()) {
        return;
    }

    if (!SystemIsSerial()) {
        lcdClear();
        WriteMessage(0, 66);
        WriteMessage(1, 67);
        return;
    }

    if (systemInactive() == false) {
        lcdClear();
        WriteMessage(0, 31);
        WriteMessage(1, 32);
        return;
    }


    tm_t Date;
    uint8_t buf[PRINT_BUF_DATETIME_lENGTH];
    uint8_t size;
    uint8_t buf2[65];
    time_t t;
    if (lcdIsBusy())
        return;

    if (!systemSecondEvent())
        return;

    t = systemNow();
    DateTimeFromTimeStamp(&Date, t);
    PrintDateTime(&Date, buf);
    /*show Message*/
    setBuff(buf2, 0x20, 65);
    lcdwritebuf(0, 0, buf, LCD_NUMBER_OF_BYTE);
    size = appPrintMessage(buf2, 0, 17);
    scllormessage(gu8ProductLCDScoller, buf2, size, LCD_NUMBER_OF_BYTE);
    lcdwritebuf(1, 0, gu8ProductLCDScoller, LCD_NUMBER_OF_BYTE);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <UserInit>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void UserInit                                                               |
 | < @Description         : Init all variable in this file                                              |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void UserInit() {
    gu8UserSystem = CANCEL_STATE;
    gu8ToggleState = 0;
    gu8OnPeriodIsDone = 0;
    gu8Buzzer = gu8GeneralBuzzerActive;
    setBuff(gu8ProductLCDScoller, 0x20, LCD_NUMBER_OF_BYTE);
    systemDateTimeStop();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <UserCallBack>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void UserCallBack                                                           |
 | < @Description         : run in background                                                           |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void UserCallBack() {
    switch (gu8UserSystem) {
        case CANCEL_STATE:
            MainShow();
            break;
        case CALL_STATE:
            if (onUserCall()) {
                gu8OnPeriodIsDone = 1;
            }
            break;
        case URGENT_STATE:
            if (onUserEMG()) {
                gu8OnPeriodIsDone = 1;
            }
            break;
        case NEW_REQUEST_STATE:
            if (onNewRequest()) {
                gu8UserSystem = item.State;
            }
            break;
        default:
            gu8UserSystem = CANCEL_STATE;
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getPeriodIsDone() {
    if (gu8OnPeriodIsDone) {
        gu8OnPeriodIsDone = 0;
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static void cancelState() {
    gu8Buzzer = 0;
    if (gu8UserAcceptState == 3) {
        return;
    }
    gu8UserAcceptState = 1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static void cancelItemByItem() {
    //Enter  ip 
    if (gu8UserAcceptState == 3) {
        return;
    }
    gu8AcceptIpState = 1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t AcceptIpIsRun() {
    return gu8AcceptIpState;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void setActiveBuzzer() {
    gu8UserAcceptState = 0;
    if (gu8GeneralBuzzerActive == 0) {
        return;
    }

    gu8Buzzer = 1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t setGloable_Active_buzzer() {
    memAddresst_t address;
    uint8_t OptionCallBackState = 0;
    switch (gu8BuzzerState) {
        case 0:
            OptionCallBackState = CustomPasswordCallback();
            if (OptionCallBackState == 2) {
                return (1);
            }

            if (OptionCallBackState == 1) {
                gu8BuzzerState = 1;
            }
            break;
        case 1:
            address = GOABL_BUZZER_ACTIVE;
            if (LoadFromMemory(address, (uint8_t *) & gu8GeneralBuzzerActive, 1)) {
                gu8BuzzerState = 2;
                lcdClear();
                WriteMessage(0, 50);
                systemOptionRegisterData(2, gu8GeneralBuzzerActive, 40);
            }
            break;
        case 2:
            OptionCallBackState = systemOptionCallBack();
            if (OptionCallBackState == 1) {
                gu8BuzzerState = 0;
                return (1);
            }
            if (OptionCallBackState == 2) {
                gu8GeneralBuzzerActive = SystemGetCurrentOption();
                gu8BuzzerState = 3;
                return (0);
            }
            break;
        case 3:
            address = GOABL_BUZZER_ACTIVE;
            if (SaveIntoMemory(address, (uint8_t *) & gu8GeneralBuzzerActive, 1)) {
                gu8Buzzer = gu8GeneralBuzzerActive;
                gu8BuzzerState = 0;
                return (1);
            }
            break;
        default:
            gu8BuzzerState = 0;
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t loadBuzzerStateFroMemeory() {
    memAddresst_t address = GOABL_BUZZER_ACTIVE;
    if (LoadFromMemory(address, (uint8_t *) & gu8GeneralBuzzerActive, 1)) {
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void UserAcceptCallback() {

    switch (gu8UserAcceptState) {
        case 0:
            break;
        case 1://accept all in queue
            if (acceptAllCallState()) {
                gu8UserAcceptState = 2;
            }
            break;
        case 2:
            if (acceptAllUregntState()) {
                gu8UserAcceptState = 3;
            }
            break;
        case 3:
            break;
        default:
            gu8UserAcceptState = 0;
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void acceptUserCallBack() {
    uint8_t state = 0;
    switch (gu8AcceptIpState) {
        case 0:
            break;
        case 1:
            state = selectIpCallback();
            if (state == 1) {
                Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
                systemDateTimeStop();
                gu8AcceptIpState = 0;
                resetCurrentIP();
                return;
            }
            if (state == 2) {
                gu8AcceptIpState = 2;
                return;
            }
            break;
        case 2:
            if (acceptCurrentCallPoint(getCurrentIpSelect())) {
                gu8AcceptIpState = 3;
            }
            break;
        case 3:
            if (acceptCurrentUrgentPoint(getCurrentIpSelect())) {
                Tonestop(TONE_PIN0_GPIO, 0, TONE_PIN0_DEFALUT_STATE);
                systemDateTimeStop();
                gu8AcceptIpState = 0;
                resetCurrentIP();
            }
            break;
        default:
            gu8AcceptIpState = 0;
            break;
    }
}
