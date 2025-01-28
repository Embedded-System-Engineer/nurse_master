/* 
 * File:   display_queue.h
 * Author: hassa
 *
 * Created on September 3, 2024, 8:32 AM
 */

#ifndef DISPLAY_QUEUE_H
#define	DISPLAY_QUEUE_H

typedef enum {
    CANCEL_STATE = 0,
    CALL_STATE = 1,
    URGENT_STATE = 2,
    CONFIG_STATE = 3,
    NEW_REQUEST_STATE = 4,
} CommandType;

typedef struct {
    uint16_t swId;
    uint16_t RId;
    time_t timestamp;
    uint8_t address;
    uint8_t State;
} QueueItem;

typedef struct Node {
    QueueItem item;
    struct Node* next;
} Node;
// Define the queue structure


/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
void QueueRun(uint8_t state);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
void putIntoQueue(QueueItem receivedData);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
void processQueue();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptAllCallState();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptAllUregntState();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptCurrentUrgentPoint(uint8_t ip);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptCurrentCallPoint(uint8_t ip);
#endif	/* DISPLAY_QUEUE_H */

