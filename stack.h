/**
 *
 * File: stack.h
 * Description: Module for stack operation
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/

#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>

// Item struck
typedef struct StackItem {
    uint8_t coordinates[2];
    struct StackItem *next;
} SWay;

// Stack module prototypes
SWay * SInit();
SWay * SPush(SWay *sOpen, uint8_t from, uint8_t to);
SWay * SPop(SWay *sOpen);
uint8_t STop(SWay *sOpen);
size_t SLen(SWay *sOpen);
bool SEmpty(SWay *sOpen);
bool in_stack(SWay *sOpen, uint8_t from, uint8_t to);

#endif
