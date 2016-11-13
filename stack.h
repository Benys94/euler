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
    int coordinates[2];
    struct StackItem *next;
} SWay;

// Stack wrapper
typedef struct StackStore {
    SWay *path;
    struct StackStore *next;
} PWrap;

// Stack module prototypes
SWay * SInit();
SWay * SPush(SWay *sOpen, int from, int to);
void SPop(SWay *sOpen);
int * STop(SWay *sOpen);
bool SEmpty(SWay *sOpen);
bool in_stack(SWay *sOpen, int from, int to);

// Stack wrapper prototypes
PWrap * wrap_init();
PWrap * push_stack(PWrap * wrapper, SWay *sOpen);
PWrap * pop_stack(PWrap *wrapper);
SWay * top_stack(PWrap *wrapper);
bool wrapper_empty(PWrap * wrapper);

#endif
