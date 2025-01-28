
#include <stdint.h>

#include "../inc/appRes.h"
static uint8_t gu8CurrentCallPointDataIndex = 0;
/*
 *<@var Main Lable CallBacks Function
 */
static memAddresst_t gu8MemInitMem;
/*
 *<@var Main Lable CallBacks Function
 */
static uint8_t gu8MemPowerOn;
/*
 * <@var gu8EEpromState : State Value of memory
 */
static uint8_t gu8MEMBuffer[EXEEPROM_MEM_MAX_BUFFER];
/*
 * <@var gu8EEpromState : State Value of memory
 */
static uint8_t gu8MemReadState;
/*
 * <@var gu8EEpromState : State Value of memory
 */
static uint8_t gu8MemWriteState;

/*
 *<@var system ResetAll
 */
static uint8_t gu8ResetAll;

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ResetSystemAllWithSerialOtions >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetSystemAllWithSerialOtions                                                            |  
 | < @Description       : shard function between power on and reset                                      |                                                    |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ResetSystemAllWithSerialOtions(uint8_t ResetSerial);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < MemPowerOn >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void MemPowerOn                                                        |  
 | < @Description       : Load Data Into MEM                                        |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */

uint8_t MemPowerOn() {
    
    if (!gu8MemPowerOn) {
        if (LoadFromMemory(0, gu8MEMBuffer, 3)) {
            if ((gu8MEMBuffer[0] == MEMORY_VERIFIY_CODE_ONE) && (gu8MEMBuffer[1] == MEMORY_VERIFIY_CODE_TWO) && (gu8MEMBuffer[2] == MEMORY_VERIFIY_CODE_THREE)) {
                gu8ResetAll = 10;
            } else {
                WriteMessage(0, 39);
                gu8ResetAll = 0;
            }
            gu8MemPowerOn = 1;
        }
        return (0);
    }
    if (ResetSystemAllWithSerialOtions(0)) {
        gu8MemPowerOn = 0;
        return (1);

    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < LoadFromMemory >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                                        |  
 | < @Description       : load Data From memory with specific                                            |                                                    |
 | < @return            : return done value of the memory                                                |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t LoadFromMemory(memAddresst_t address, uint8_t *buf, uint8_t nByte) {
    if (exeepromReady() == 0)
        return (0);
    if (gu8MemReadState) {
        exEepromRead(gu8MEMBuffer);
        copyBuff(buf, gu8MEMBuffer, nByte);
        gu8MemReadState = 0;
        return (1);
    }
    exeepromRequestSteram(address, nByte);
    gu8MemReadState = 1;

    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < LoadFromMemory >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                                        |  
 | < @Description       : save data into  memory with specific                                            |                                                    |
 | < @return            : return done value of the memory                                                |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t SaveIntoMemory(memAddresst_t address, uint8_t *buf, uint8_t nByte) {
    if (exeepromReady() == 0)
        return (0);
    if (gu8MemWriteState) {
        gu8MemWriteState = 0;
        return (1);
    }
    copyBuff(gu8MEMBuffer, buf, nByte);
    exeepromWriteBuffer(address, gu8MEMBuffer, nByte);
    gu8MemWriteState = 1;

    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < InitMem >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void InitMem                                                        |  
 | < @Description       : init all values in memory                                          |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void InitMem() {
    gu8MemPowerOn = 0;
    gu8MemReadState = 0;
    gu8MemWriteState = 0;
    gu8MemInitMem = 0;
    gu8ResetAll = 0;
    gu8MemPowerOn = 0;

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ResetSystemAll >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetSystemAll                                                            |  
 | < @Description       : shard function between power on and reset                                      |                                                    |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t ResetSystemAll() {
    return ResetSystemAllWithSerialOtions(0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ResetSystemAll >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetSystemAll                                                            |  
 | < @Description       : shard function between power on and reset                                      |                                                    |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ResetSystemAllWithSerialOtions(uint8_t ResetSerial) {

    SystemSerial_t serial;
    memAddresst_t address;
    uint8_t ConfirmedKey = 0;
    if (lcdIsBusy()) {
        return (0);
    }

    switch (gu8ResetAll) {
        case 0:
            ConfirmedKey = CustomPasswordCallback();  
            if (ConfirmedKey == 2) {
                gu8ResetAll = 10; //load data from memory
                return (0);
            }
            if (ConfirmedKey == 1) {
                gu8ResetAll = 1;
                return (0);
            }
            break;
        case 1:/*Init workingTime*/
            if (SystemResetDisplayModule()) {
                gu8ResetAll = 2;
            }
            break;
        case 2:
            if (SystemResetRoomModule()) {
                gu8ResetAll = 3;
            }

            break;
        case 3:
            if (SystemResetSwConfigModule()) {
                gu8ResetAll = 4;
            }
            break;
        case 4:
            if (SystemResetSwDataModule()) {
                gu8ResetAll = 5;
            }
            break;
        case 5:
            if (SystemResetLogDataModule()) {
                gu8ResetAll = 6;
            }
            break;
        case 6:
            if (ResetSerial == 0) {
                gu8ResetAll = 7;
                return (0);
            }
            if (SystemResetSerail()) {
                gu8ResetAll = 7;
            }
            break;
        case 7:
            if (SystemResetWorkingTime()) {
                gu8ResetAll = 8;
            }
            break;

        case 8:
            if (SystemResetLoadConfig()) {
                gu8MEMBuffer[0] = MEMORY_VERIFIY_CODE_ONE;
                gu8MEMBuffer[1] = MEMORY_VERIFIY_CODE_TWO;
                gu8MEMBuffer[2] = MEMORY_VERIFIY_CODE_THREE;
                lcdClear();
                WriteMessage(0, 15);
                gu8ResetAll = 9;
            }
            break;
        case 9:
            if (SaveIntoMemory(0x0000, gu8MEMBuffer, 3)) {
                gu8ResetAll = 10;
            }
            /*load Verification Code*/
            break;
        case 10:/*load*/
            if (LoadFromMemory(CURRENT_WORKINGTIME_ADDRESS, (uint8_t *) & gstWorkingTime, sizeof (stWorkingtime_t))) {
                gu8ResetAll = 11;
            }
            break;
        case 11:
            if (LoadFromMemory(MEMORY_START_SERAIL_NUMBER, gu8MEMBuffer, sizeof (SystemSerial_t))) {
                copyBuff(&serial, gu8MEMBuffer, sizeof (SystemSerial_t));
                SystemLoadSerail(&serial);
                gu8ResetAll = 12;
            }
            break;
        case 12:
            if (LoadFromMemory(MEMORY_START_LOAD_CONFIG, gu8MEMBuffer, MAX_DEVICE_USED >> 3)) {
                gu8ResetAll = 13;
            }
            break;
        case 13:// load and add points
            if (loadBuzzerStateFroMemeory()) {
                gu8ResetAll = 14;
            }
            break;
        case 14:
            address = SYSTEM_INACTIVE_ADDRESS;
            if (LoadFromMemory(address, gu8MEMBuffer, 1)) {
                if (gu8MEMBuffer[0] == 0) {
                    setSystemInactive(false);
                } else {
                    setSystemInactive(true);
                }
                gu8ResetAll = 15;
            }
            break;
        case 15:
            //add points
            if (gu8CurrentCallPointDataIndex < MAX_DEVICE_USED) {
                address = MEMORY_START_SWITCH_DATA + (((gu8CurrentCallPointDataIndex) * sizeof (stCallPointData_t)));
                if (LoadFromMemory(address, gu8MEMBuffer, sizeof (stCallPointData_t))) {
                    //swid0 swi1 rid0 rid1 state timestamp 
                    if (gu8MEMBuffer[4] != SYSTEM_DEFALUT_EVENT && gu8MEMBuffer[4] != SYSTEM_CANCEL_EVENT) {
                        QueueItem item;
                        item.address = gu8CurrentCallPointDataIndex + 1;
                        item.State = getCurrentState(gu8MEMBuffer[4]);
                        copyBuff(&item.swId, gu8MEMBuffer, 2);
                        copyBuff(&item.RId, gu8MEMBuffer + 2, 2);
                        copyBuff(&item.timestamp, gu8MEMBuffer + 5, 4);
                        ATOMIC_BEGIN
                        putIntoQueue(item);
                        ATOMIC_END
                    }
                    gu8CurrentCallPointDataIndex++;
                }
            } else {
                gu8CurrentCallPointDataIndex = 0;
                gu8ResetAll = 0;
                return (1);
            }
            break;
        default:
            gu8ResetAll = 0;
            break;
    }
    return (0);
}






