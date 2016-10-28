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
    char path[3];
    struct StackItem *next;
} sitem;

// Struct for whole stack
typedef struct StackList {
    sitem *head;
} SList;

// Stack module prototypes
void SInit(SList *sOpen);
bool SPush(SList *sOpen, char val[]);
void SPop(SList *sOpen);
char *STop(SList *sOpen);
bool SEmpty(SList *sOpen);
bool in_stack(SList *sOpen, char val[]);

#endif
