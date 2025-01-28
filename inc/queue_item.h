/* 
 * File:   queue_item.h
 * Author: hassa
 *
 * Created on August 29, 2024, 9:13 AM
 */

#ifndef QUEUE_ITEM_H
#define	QUEUE_ITEM_H
typedef struct {
    char data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} CharQueue;

#endif	/* QUEUE_ITEM_H */

