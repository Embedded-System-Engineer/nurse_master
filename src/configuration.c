#include "appRes.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Variables>                                                       |
 --------------------------------------------------------------------------------------------------------
 */
/*
 *<@var : Board Info and configuration var
 */
static boardinfo_t gstboardInfo;

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Internal function Definitions>                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveSerial>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveSerial                                                           |
 | < @Description         : save serial number On boot section this function reboot system              |   
 | < @return              : void                                                     |          
 --------------------------------------------------------------------------------------------------------
 */
static void OnSaveSerial(uint8_t *buf);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveConfiguration>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveConfiguration                                                    |
 | < @Description         : save configuartion On boot section this function reboot system              |   
 | < @return              : void                                                                         |          
 --------------------------------------------------------------------------------------------------------
 */
void OnSaveConfiguration(uint8_t *buf);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Internal function >                                         |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveSerial>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveSerial                                                           |
 | < @Description         : save serial number On boot section this function reboot system              |   
 | < @return              : void                                                     |          
 --------------------------------------------------------------------------------------------------------
 */
static void OnSaveSerial(uint8_t *buf) {
    copyBuff(&gstboardInfo.SystemSerial.Time, buf + 3, 4);
    copyBuff(&gstboardInfo.SystemSerial.Code, buf + 9, 6);
    gstboardInfo.State = 1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <ConfigurationInit>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void ConfigurationInit                                                           |
 | < @Description         : iniliaztion value of the configuration master             |   
 | < @return              : void                                                     |          
 --------------------------------------------------------------------------------------------------------
 */
void ConfigurationInit() {
    csmaSaveSerialRegister(OnSaveSerial);
    setBuff(&gstboardInfo, 0x00, sizeof (boardinfo_t));
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <noSerial>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void noSerial                                                               |
 | < @Description         : system have serial or not                                                   |   
 | < @return              : 0 is not have a serial and  1 system have a serial                          |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemIsSerial() {
    if (gstboardInfo.SystemSerial.Time == 0) {
        return (0);
    }
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveConfiguration>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveConfiguration                                                    |
 | < @Description         : save serail Number On extranleeprom section this function reboot system              |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void OnSaveSerialCallBack() {
    if (!gstboardInfo.State) {
        return;
    }

    if (SaveIntoMemory(MEMORY_START_SERAIL_NUMBER, ((uint8_t *) & gstboardInfo.SystemSerial), sizeof (SystemSerial_t))) {
        csmaloadConfig(gstboardInfo.SystemSerial.CH0, gstboardInfo.SystemSerial.Time);
        gstboardInfo.State = 0;
        return;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SystemLoadSerail>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void SystemLoadSerail                                                       |
 | < @Description         : load serial number from eeprom                                              |   
 | < @return              : void                                                                         |          
 --------------------------------------------------------------------------------------------------------
 */
void SystemLoadSerail(SystemSerial_t *serail) {
    copyBuff(&gstboardInfo.SystemSerial, serail, sizeof (SystemSerial_t));
    csmaloadConfig(gstboardInfo.SystemSerial.CH0, gstboardInfo.SystemSerial.Time);
    csmaInitStationIp(1);
}