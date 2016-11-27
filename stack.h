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

// Stack wrapper
typedef struct StackStore {
    SWay *path;
    struct StackStore *next;
} PWrap;

// Stack module prototypes
SWay * SInit();
SWay * SPush(SWay *sOpen, unsigned int from, unsigned int to);
void SPop(SWay *sOpen);
unsigned int STop(SWay *sOpen);
bool SEmpty(SWay *sOpen);
bool in_stack(SWay *sOpen, unsigned int from, unsigned int to);

// Stack wrapper prototypes
PWrap * wrap_init();
PWrap * push_stack(PWrap * wrapper, SWay *sOpen);
PWrap * pop_stack(PWrap *wrapper);
SWay * top_stack(PWrap *wrapper);
bool wrapper_empty(PWrap * wrapper);

#endif
