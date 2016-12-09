/**
 * File: pool.h
 * Description: Module for memory management
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 * VUT FIT 2016
**/

#ifndef _POOL_H_
#define _POOL_H_

#include <stdint.h>

typedef struct MemoryList {
    void *dataPtr;
    struct MemoryList *next;
} MemList;

void * MemAlloc(size_t size);   // Memory alloc
void freeOne();                 // Free one block
void freeAll();                 // Free all alocated memory

#endif
