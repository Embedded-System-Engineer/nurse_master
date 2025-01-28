

#include "appRes.h"



/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ResetSystemAll >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetSystemAll                                                            |  
 | < @Description       : shard function between power on and reset                                      |                                                    |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t SetIpCallback();
MenuItem(SMU, NullItem, NullItem, NullItem, SDT, NULL, SMUL, "0.SYSTEM");

MenuItem(SDT, SLP, SWT, SMU, NullItem, SDTF, TimeSystem_Lable, "1.DATE TIME");
MenuItem(SLP, SCP, SDT, SMU, NullItem, loadIpCallBack, SLPL, "2.LOAD IP"); /*Create New Product*/
MenuItem(SCP, SRP, SLP, SMU, SCC, GeneralPasswordCallback, SCPL, "3.CONFIG POINT"); /*Create New Product*/
MenuItem(SRP, SWT, SCP, SMU, SRAL, GeneralPasswordCallback, WSTL, "4.SYSTEM RESET"); /*Select Main Product to Main by Product Number*/
MenuItem(SWT, SDT, SRP, SMU, NullItem, SWTF, SWTL, "5.SYSTEM WORK TIME"); /*Select Main Product to Main by Product Number*/


MenuItem(SCC, SRC, SDC, SCP, CPSAD, SetIpCallback, SCCL, "1.SWITCH CONFIG"); /*Create New Product*/
MenuItem(SRC, SDC, SCC, SCP, RPST, SetIpCallback, SRCL, "2.ROOM CONFIG"); /*Create New Product*/
MenuItem(SDC, BSE, SRC, SCP, DPST, SetIpCallback, SDCL, "3.DISPLAY CONFIG"); /*Create New Product*/
MenuItem(BSE, SCC, SDC, SCP, NullItem, setGloable_Active_buzzer, BSEL, "4.BUZZER STATE");


MenuItem(SRAL, SRMO, SRIP, SRP, NullItem, ResetSystemAll, SRALL, "1.RESET ALL"); /*Create New Product*/
MenuItem(SRMO, SRIP, SRAL, SRP, RDMS, NULL, SRMOL, "2.RESET MODULE"); /*Create New Product*/
MenuItem(SRIP, SRAL, SRMO, SRP, NullItem, inactiveSytemCallBack, SRIPL, "3.Deactivate"); /*Create New Product*/


MenuItem(RDMS, RRMS, RLDS, SRMO, NullItem, SystemResetDisplayCallBack, RDMSL, "1.RESET DISPLAYS"); /*Create New Product*/
MenuItem(RRMS, RSCS, RDMS, SRMO, NullItem, SystemResetRoomCallBack, RRMSL, "2.RESET ROOMS"); /*Create New Product*/
MenuItem(RSCS, RSDS, RRMS, SRMO, NullItem, SystemResetSwConfigCallBack, RSCSL, "3.RESET SW CONFIG"); /*Create New Product*/
MenuItem(RSDS, RLDS, RSCS, SRMO, NullItem, SystemResetSwDataCallBack, RSDSL, "4.RESET SW DATA"); /*Create New Product*/
MenuItem(RLDS, RDMS, RSDS, SRMO, NullItem, SystemResetLogCallBack, RLDSL, "5.RESET LOG"); /*Create New Product*/



MenuItem(CPSAD, CPSID, CPSRS, SCC, NullItem, switchActiveByIp, CPSADL, "01.SWITCH ENABLE"); /*Create New Product*/
MenuItem(CPSID, CPRID, CPSAD, SCC, NullItem, switchIDCallBack, CPSIDL, "02.SWITCH ID"); /*Create New Product*/
MenuItem(CPRID, CPRIP, CPSID, SCC, NullItem, RoomIdCallBack, CPRIDL, "03.ROOM ID"); /*Create New Product*/
MenuItem(CPRIP, CPSW1, CPRID, SCC, NullItem, switchRoomIpCallBack, CPRIPL, "04.ROOM IP"); /*Create New Product*/
MenuItem(CPSW1, CPSW2, CPRIP, SCC, NullItem, sw1Type, CPSW1L, "05.SW1 STATE"); /*Create New Product*/
MenuItem(CPSW2, CPSW3, CPSW1, SCC, NullItem, sw2Type, CPSW2L, "06.SW2 STATE"); /*Create New Product*/
MenuItem(CPSW3, CPBUZ, CPSW2, SCC, NullItem, sw3Type, CPSW3L, "07.SW3 STATE"); /*Create New Product*/
MenuItem(CPBUZ, CPBTO, CPSW3, SCC, NullItem, switchBuzzerState, CPBUZL, "08.BUZZER STATE"); /*Create New Product*/
MenuItem(CPBTO, CPSRS, CPBUZ, SCC, NullItem, switchBuzzerTime, CPBTOL, "09.BUZZER TIME"); /*Create New Product*/
MenuItem(CPSRS, CPSAD, CPBTO, SCC, NullItem, switchDisabledSystem, CPSRSL, "10.DISABLED SYSTEM"); /*Create New Product*/


MenuItem(RPST, RPLV, RPBT, SRC, NullItem, NULL, RPSTL, "1.LED SCORLL TIME"); /*Create New Product*/
MenuItem(RPLV, RPBS, RPST, SRC, NullItem, NULL, RPLVL, "2.LED HW VERSION"); /*Create New Product*/
MenuItem(RPBS, RPLR, RPLV, SRC, NullItem, NULL, RPBSL, "3.LED BUZZER"); /*Create New Product*/
MenuItem(RPLR, RPBT, RPBS, SRC, NullItem, NULL, RPLRL, "4.LED RESPONSE"); /*Create New Product*/
MenuItem(RPBT, RPST, RPLR, SRC, NullItem, NULL, RPBTL, "5.LED BUZZER TIME"); /*Create New Product*/

MenuItem(DPST, DPMV, DPED, SDC, NullItem, DISPLAYTimeScoller, DPSTL, "1.ACTIVE SWITCH"); /*Create New Product*/
MenuItem(DPMV, DPED, DPST, SDC, NullItem, DispalyMainID, DPMVL, "2.MAIN ID"); /*Create New Product*/
MenuItem(DPED, DPST, DPMV, SDC, NullItem, DispalyDandogState, DPEDL, "4.DANGDONG STATE"); /*Create New Product*/


/*
 *<@var Main Lable CallBacks Function
 */
static uint8_t gu8Main;

/*
 --------------------------------------------------------------------------------------------------------
 |                            < MainInit  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void MainInit                                                        |
 | < @Description       : Init Data of main callback                                         |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void MainInit() {
    lcdClear();
    ReturnMenuCallBack();
    lcdNoBlink();
    ClearsystemSecondEvent();
    KeypadRegisterEvent(MainModeEvent, 12);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < MainCallBack  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void MainCallBack                                                        |
 | < @Description       : MainCallBack                                        |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void MainCallBack() {

    if (gu8Main == 0) {
        return;
    }

    if (menuIsOpen() == 0) {/*close the Menue*/
        ATOMIC_BEGIN
        systemDateTimeStop();
        MainInit();
        gu8Main = 0;
        ATOMIC_END
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < MainModeEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void MainModeEvent                                                        |
 | < @Description       : Main specific Lable by Main Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t MainModeEvent(stkey_t * key) {
    if (key->State == KEY_PRESS) {
        ReturnMenuCallBack();
        menuStart(&SMU);
        gu8Main = 1;
    }
    KeypadResetTabCounter(key, 1);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onUserAccept>                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onUserAccept                                                          |
 | < @Description         : accept all of the current Order                                            |      
 | < @return              : void                                                                       |          
 --------------------------------------------------------------------------------------------------------
 */


static uint8_t SetIpCallback() {
    uint8_t state = selectIpCallback();
    if (state == 1) {
        resetCurrentIP();
        CencelCurrentMenue();
        return (1);
    }

    if (state == 2) {
        return (1);
    }

    return (0);
}

