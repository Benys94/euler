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

// List of allocated momory blocks
MemList *actPool = NULL;

/**
 * @brief Memory allocator
 *
 * @param size Size of requested memory
 *
 * @return Block of allocated memory which is need to be retyped
**/
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

/**
 * @brief This will free one block of memory (for poping from stack)
**/
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

/**
 * @brief Free all alocated memory (call only at the end or on error state)
**/
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
