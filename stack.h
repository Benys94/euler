/**
 *
 * File: stack.h
 * Description: Module for stack operation
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/

#ifndef _STACK_H_
#define _STACK_H_

// Item struck
typedef struct StackItem {
    unsigned int coordinates[2];
    struct StackItem *next;
} SWay;

// Stack module prototypes
SWay * SInit();
SWay * SPush(SWay *sOpen, unsigned int from, unsigned int to);
SWay * SPop(SWay *sOpen);
unsigned int STop(SWay *sOpen);
size_t SLen(SWay *sOpen);
bool SEmpty(SWay *sOpen);
bool in_stack(SWay *sOpen, unsigned int from, unsigned int to);

#endif