/* 
 * File:   Memory.h
 * Author: hassa
 *
 * Created on February 26, 2023, 8:19 PM
 */

#ifndef MEMORY_H
#define	MEMORY_H
#include "appRes.h"

#define  MAX_ADDRESS_PER_SWITCH                  1
#define  MAX_ADDRESS_PER_ROOM                    1
#define  MAX_ADDRESS_PER_DISPLAY                 1

typedef union {
    uint8_t Options;

    struct {
        unsigned MainView : 1;
        unsigned dangdongState : 1;
    };
} DisplayOptions_t;

typedef union {
    uint8_t Options;

    struct {
        unsigned Buz : 1;
        unsigned HWType : 1;
        unsigned DisapledSystem : 1;
        unsigned buzzerTimeFactor : 5;
    };
} RoomOptions_t;

typedef union {
    uint8_t Options;

    struct {
        unsigned DisapledSystem : 1;
        unsigned buzzerState : 1;
        unsigned buzzerTimeFactor : 6;
    };
} CallPointOptions_t;

typedef struct stDisplayConfig_s {
    DisplayOptions_t Option;
    uint8_t activeIps[MAX_DEVICE_USED >> 3];
} stDisplayConfig_t;

typedef struct stRoomConfig_s {
    uint8_t scollerTime;
    RoomOptions_t option;
} stRoomConfig_t;

typedef struct CallPointConfig_s {
    uint8_t Rip;
    uint8_t SwitchHwType[3];
    CallPointOptions_t Option;
} stCallPointConfig_t;

typedef struct stCallPointLog_s {
    uint8_t Ip;
    uint8_t State;
    time_t Time;
} stCallPointLog_t;

typedef struct CallPointData_s {
    uint16_t SWID;
    uint16_t RID;
    uint8_t State;
    time_t Time;
} stCallPointData_t;

typedef struct WorkingHour_s {
    uint8_t StartHour;
    uint8_t EndHour;
} stWorkingHour_t;

typedef struct WorkingTime_s {
    time_t StartTime;
    time_t EndTime;
} stWorkingtime_t;
/*
 *<@var MEMORY_VERIFIY_CODE_ONE       : Memeory verifiy code one    
 */
#define MEMORY_VERIFIY_CODE_ONE        (0x23)
/*
 *<@var MEMORY_VERIFIY_CODE_TWO       : Memeory verifiy code one    
 */
#define MEMORY_VERIFIY_CODE_TWO        (0x11)
/*
 *<@var MEMORY_VERIFIY_CODE_THREE       : Memeory verifiy code one    
 */
#define MEMORY_VERIFIY_CODE_THREE      (0x96)

/*
 * <@var start Init Code Address
 */
#define START_INIT_CODE_ADDRESS                   (0x00)

#define SYSTEM_INACTIVE_ADDRESS                   (0x03)

#define GOABL_BUZZER_ACTIVE                        (0x04)
/*
 * 
 * <@marco LAST_PRODUCT_ADDRESS    : Current Working Time Address address 
 */
#define  CURRENT_WORKINGTIME_ADDRESS               (0x05)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_SERAIL_NUMBER       /*0x000B*/            (CURRENT_WORKINGTIME_ADDRESS) + (sizeof(stWorkingtime_t))
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_LOAD_CONFIG        /*0x000B*/            (MEMORY_START_SERAIL_NUMBER) + (sizeof(SystemSerial_t))
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_DISPLAY_CONFIG                   (MEMORY_START_LOAD_CONFIG) + (MAX_DEVICE_USED)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_ROOM_CONFIG                   (MEMORY_START_DISPLAY_CONFIG) + ((sizeof(stDisplayConfig_t))*MAX_DEVICE_USED)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_SWITCH_CONFIG                    (MEMORY_START_ROOM_CONFIG) + ((sizeof(stRoomConfig_t))*MAX_DEVICE_USED)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_SWITCH_DATA                  (MEMORY_START_SWITCH_CONFIG) + ((sizeof(stCallPointConfig_t))*MAX_DEVICE_USED)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define MEMORY_START_SWITCH_LOG                  (MEMORY_START_SWITCH_DATA) + ((sizeof(stCallPointData_t))*MAX_DEVICE_USED)





#define    NO_MODULE_SELECT               0x00
#define    NO_MODULE_ON_SELECT            0x01
#define    DISPLAY_MODULE_SELECT          0x02
#define    ROOM_MODULE_SELECT             0x03
#define    SWCONFIG_MODULE_SELECT         0x04
#define    SWDATA_MODULE_SELECT           0x05
#define    LOG_MODULE_SELECT              0x06
#define    RESET_SERRIAL_SELECT           0x07
#define    WORKING_TIME_SELECT            0x08
#define    RESET_LOAD_CONFIG_SELECT       0x09




/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < MemPowerOn >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void MemPowerOn                                                        |  
 | < @Description       : Load Data Into MEM                                        |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */

uint8_t MemPowerOn();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < InitMem >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void InitMem                                                        |  
 | < @Description       : init all values in memory                                          |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void InitMem();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < LoadFromMemory >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                                        |  
 | < @Description       : load Data From memory with specific                                            |                                                    |
 | < @return            : return done value of the memory                                                |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t LoadFromMemory(memAddresst_t address, uint8_t *buf, uint8_t nByte);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < LoadFromMemory >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                                        |  
 | < @Description       : save data into  memory with specific                                            |                                                    |
 | < @return            : return done value of the memory                                                |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t SaveIntoMemory(memAddresst_t address, uint8_t *buf, uint8_t nByte);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ResetSystemAll >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetSystemAll                                                            |  
 | < @Description       : shard function between power on and reset                                      |                                                    |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t ResetSystemAll();

#endif	/* MEMORY_H */

