/**
 * File: pool.c
 * Description: Memoru management
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 * VUT FIT 2016
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "pool.h"

#define POOL_SIZE (100000)

AllocatedMem *pool = NULL;

static inline AllocatedMem *PAddPool(size_t size){
    AllocatedMem *tmp = malloc(sizeof(AllocatedMem) + size);
    if(tmp == NULL){
        FatalError(EC_MEM_ALLOC, "Memory allocation has failed.");
    }

    tmp -> capacity = size;
    tmp -> used = 0;

    return tmp;
}

/**
 * @brief Initialize memory pool
**/
void pool_init()
{
    pool = malloc(sizeof(AllocatedMem) + POOL_SIZE);
    if(pool == NULL){
        FatalError(EC_MEM_ALLOC, "Memory pool allocation has failed.");
    }

    pool -> capacity = POOL_SIZE;
    pool -> used = 0;
    pool -> next = NULL;
}

/**
 * @brief Allocate memory and store it in the pool
 *
 * @param size Size of the requested memory
 *
 * @return Method return void pointer to allocated memory which should be retyped
**/
void *MemAcq(size_t size)
{
    // If pool is exausted create next one.
    if((pool -> capacity - pool -> used) < size){
        AllocatedMem *old = pool;

        size_t newSize = ((pool -> capacity << 1) >= size ? (pool -> capacity << 1) : size);
        pool = PAddPool(newSize);
        pool -> next = old;
    }

    void *tmp = pool -> dataPtr + pool -> used;
    pool -> used += size;
    return tmp;
}

/**
 * @brief Free all allocated memory in the pool
**/
void pool_free(void)
{
    while(pool != NULL){
        AllocatedMem *tmp = pool -> next;
        free(pool);
        pool = tmp;
    }
}

/////////////////////////////////////////////////////
/// Alternative Pool                              ///
/////////////////////////////////////////////////////

MemList *actPool = NULL;

void * MemAlloc(size_t size)
{
    MemList *new_item = malloc(sizeof(MemList));
    if(new_item == NULL){
        FatalError(EC_MEM_ALLOC, "Malloc has failed.");
    }

    void *data = malloc(size);
    if(data == NULL){
        FatalError(EC_MEM_ALLOC, "Malloc has failed.");
    }

    new_item -> dataPtr = data;
    new_item -> next = actPool;
    actPool = new_item;

    return data;
}

void freeOne()
{
    MemList *tmp;
    if(actPool != NULL){
        free(actPool -> dataPtr);
        actPool -> dataPtr = NULL;
        tmp = actPool -> next;
        free(actPool);
        actPool = tmp;
    }
}

void freeAll()
{
    MemList *tmpLast;
    while (actPool != NULL){
        free(actPool -> dataPtr);
        actPool -> dataPtr = NULL;
        tmpLast = actPool -> next;
        free(actPool);
        actPool = tmpLast;
    }
}
