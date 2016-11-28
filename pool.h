/**
 * File: pool.h
 * Description: Module for memory management
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 * VUT FIT 2016
**/

#ifndef _POOL_H_
#define _POOL_H_

#include <stdint.h>

typedef struct myMemory {
    size_t used;
    size_t capacity;
    struct myMemory *next;
    uint8_t dataPtr[];
} AllocatedMem;

typedef struct MemoryList {
    void *dataPtr;
    struct MemoryList *next;
} MemList;

// Momory pool functions
void pool_init();               // Memory pool initialize
void *MemAcq(size_t size);      // Allocate memory into pool
void pool_free(void);           // Release all allocated memory

size_t memWatch();
void * MemAlloc(size_t size);
void freeGoalPath(size_t size);
void freeAll(void);

#endif
