/* 
 * File:   boardinfo.h
 * Author: hassa
 *
 * Created on April 11, 2023, 7:42 PM
 */

#ifndef BOARDINFO_H
#define	BOARDINFO_H


#include "appRes.h"

typedef struct SystemSerial_s {
    time_t Time;
    uint8_t Code;
    uint8_t PatchNumber;
    uint16_t PrintCode;
    uint8_t CH0;
    uint8_t CH1;
} SystemSerial_t;



typedef struct bordinfo_s {
    uint8_t State;
    SystemSerial_t SystemSerial;
} boardinfo_t;



#endif	/* BOARDINFO_H */

