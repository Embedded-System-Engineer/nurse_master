
#include <stdint.h>

#include "appRes.h"

const char string_1[] PROGMEM = "ENTER IP";
const char string_2[] PROGMEM = "IP INVALID";
const char string_3[] PROGMEM = "[1]...[";
const char string_4[] PROGMEM = "Enter ID";
const char string_5[] PROGMEM = "Enter Room ID";
const char string_6[] PROGMEM = "Invalid ID";
const char string_7[] PROGMEM = "RESET IP";
const char string_8[] PROGMEM = "RESET DPLY";
const char string_9[] PROGMEM = "RESET ROOM";
const char string_10[] PROGMEM = "RESET SWC ";
const char string_11[] PROGMEM = "RESET SWD";
const char string_12[] PROGMEM = "RESET LOG";
const char string_13[] PROGMEM = "RESET SERAIL";
const char string_14[] PROGMEM = "RESET Working";
const char string_15[] PROGMEM = "RESET CONFIG";
const char string_16[] PROGMEM = "WELCOME";
const char string_17[] PROGMEM = "MODULES";
const char string_18[] PROGMEM = "NURSE SYSYEM SERVER-TEL:+201224066670-EMAIL:www.smartsol-eg.com";
const char string_19[] PROGMEM = "PLEASE PRESS F1";
const char string_20[] PROGMEM = "TO RESET MODULE";
const char string_21[] PROGMEM = "Enter Room IP";
const char string_22[] PROGMEM = "NETWORK ERROR";
const char string_23[] PROGMEM = "TRY AGAIN";
const char string_24[] PROGMEM = "ENTER ADD 1-";
const char string_25[] PROGMEM = "IP ACTIVE";
const char string_26[] PROGMEM = "IP DE-ACTIVE";
const char string_27[] PROGMEM = "BID:";
const char string_28[] PROGMEM = "RID:";
const char string_29[] PROGMEM = "";
const char string_30[] PROGMEM = "CALL ON BED ";
const char string_31[] PROGMEM = "URGE ON BED ";
const char string_32[] PROGMEM = "SYSYREM";
const char string_33[] PROGMEM = "NOT ACTIVEATED";
const char string_34[] PROGMEM = "ROOM ID";
const char string_35[] PROGMEM = "SWITCH ID";
const char string_36[] PROGMEM = "Enter SW IP"; //35
const char string_37[] PROGMEM = "Inactive System";
const char string_38[] PROGMEM = "Active System";
const char string_39[] PROGMEM = "SYSTEM STATE";
const char string_40[] PROGMEM = "REST SYSTEM";
const char string_41[] PROGMEM = "OFF";
const char string_42[] PROGMEM = "ON";
const char string_43[] PROGMEM = "DISABLED";
const char string_44[] PROGMEM = "CALL";
const char string_45[] PROGMEM = "CENCEL";
const char string_46[] PROGMEM = "ASSISSET";
const char string_47[] PROGMEM = "CALL ASSIESSET";
const char string_48[] PROGMEM = "EMERGENCY";

const char string_49[] PROGMEM = "IP STATE";
const char string_50[] PROGMEM = "SWITCH STATE";
const char string_51[] PROGMEM = "BUZZER STATE";
const char string_52[] PROGMEM = "DISAPLED STATE";
const char string_53[] PROGMEM = "BUZZER TIME";

const char string_54[] PROGMEM = "MAX QUEUE";
const char string_55[] PROGMEM = "RESET SYSTEM";
const char string_56[] PROGMEM = "DANGDONG STATE";
const char string_57[] PROGMEM = "MAIN ID";

const char string_58[] PROGMEM = "BUZZER TIME IS";
const char string_59[] PROGMEM = "VALID FROM [1-60]";

const char string_60[] PROGMEM = "DISPLAY TIME IS";
const char string_61[] PROGMEM = "VALID FROM [1-31]";
const char string_62[] PROGMEM = " display max active";
const char string_63[] PROGMEM = "state is 48";
const char string_64[] PROGMEM = "Enter Password";
const char string_65 [] PROGMEM = "Invalid Password";
const char string_66 [] PROGMEM = "Try Again";
const char string_67 [] PROGMEM = "SYSTEM NOT";
const char string_68 [] PROGMEM = "HAVE SERIAL";
const char string_69 [] PROGMEM = "SW DEACTIVE";
const char string_70 [] PROGMEM = "SW ACTIVE";


PGM_P const Messages[] PROGMEM = {
    string_1,
    string_2,
    string_3,
    string_4,
    string_5,
    string_6,
    string_7,
    string_8,
    string_9,
    string_10,
    string_11,
    string_12,
    string_13,
    string_14,
    string_15,
    string_16,
    string_17,
    string_18,
    string_19,
    string_20,
    string_21,
    string_22,
    string_23,
    string_24,
    string_25,
    string_26,
    string_27,
    string_28,
    string_29,
    string_30,
    string_31,
    string_32,
    string_33,
    string_34,
    string_35,
    string_36,
    string_37,
    string_38,
    string_39,
    string_40,
    string_41,
    string_42,
    string_43,
    string_44,
    string_45,
    string_46,
    string_47,
    string_48,
    string_49,
    string_50,
    string_51,
    string_52,
    string_53,
    string_54,
    string_55,
    string_56,
    string_57,
    string_58,
    string_59,
    string_60,
    string_61,
    string_62,
    string_63,
    string_64,
    string_65,
    string_66,
    string_67,
    string_68,
    string_69,
    string_70
};

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WriteMessage  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WriteMessage                                                   |
 | < @Description       : Write Message From message Buffer                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void WriteMessage(uint8_t lin, uint8_t Index) {
    PGM_P String = (PGM_P) pgm_read_word(&Messages[Index]);
    lcdWriteString(lin, String);
    lcdUpdateNow();
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < messageCompareString  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  messageCompareString                                                      |
  | < @Description       : compare buffer with string                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t messageCompareString(uint8_t *buf, uint8_t Index, uint8_t length) {
    const char *date = (const char *) pgm_read_word(&Messages[Index]);
    if (memcmp_P(buf, date, length) == 0) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintMessage  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintMessage                                                       |
  | < @Description       : Print Message Into Buffer Array                                                    |
  |                      : PrintMessage                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t appPrintMessage(uint8_t *buf, uint8_t start, uint8_t MsgIndex) {
    return PrintMessage(buf, start, MsgIndex, Messages);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < messageCompareString  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  messageCompareString                                                      |
  | < @Description       : compare buffer with string                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t getMessageLength(uint8_t Index) {
    const char *date = (const char *) pgm_read_word(&Messages[Index]);
    uint8_t length = strlen(date);
    return length;
}