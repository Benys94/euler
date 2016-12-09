/**
 *
 * File: stack.c
 * Description: Operations over stack
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"
#include "stack.h"
#include "pool.h"


///////////////////
//  Path Stack   //
///////////////////

/**
 * @brief Initialize stack
 *
 * @param sOpen Stack/list variable
**/
SWay * SInit()
{
    SWay *new_way = (SWay *)MemAlloc(sizeof(SWay));
    new_way -> coordinates[0] = 0;
    new_way -> coordinates[1] = 0;
    new_way -> next =  NULL;

    return new_way;
}

/**
 * @brief Push a value to stack
 *
 * @param sOpen stack/list variable
 * @param from Origin point
 * @param to Destination point
**/
SWay * SPush(SWay *sOpen, uint8_t from, uint8_t to)
{
    SWay *new_item = (SWay *)MemAlloc(sizeof(SWay));

    // Store path coordinates
    new_item -> coordinates[0] = from;
    new_item -> coordinates[1] = to;


    new_item -> next = sOpen;
    sOpen = new_item;

    return sOpen;
}

/**
 * @brief Remove value from top of a stack
 *
 * @param sOpen Stack/list variable
**/
SWay *SPop(SWay *sOpen)
{
    sOpen = sOpen -> next;
    freeOne();
    return sOpen;
}

/**
 * @brief Get top value from a stack
 *
 * @param sOpen Stack/list variable
 *
 * @return Method return value from top of a stack
**/
uint8_t STop(SWay *sOpen)
{
    return sOpen -> coordinates[1];
}

/**
 * @brief Count number of items in stack Open
 *
 * @param sOpen stack Open
 *
 * @return Count of items
**/
size_t SLen(SWay *sOpen)
{
    size_t sLen = 0;
    for(SWay *tmp = sOpen; tmp -> next != NULL; tmp = tmp -> next){
        sLen++;
    }

    // We must decrement by one because we want count of a transitions not nodes
    return sLen;
}

/**
 * @brief Check if stack is empty
 *
 * @param sOpen Stack/list variable
 *
 * @return True if stack is empty, false otherwise
**/
bool SEmpty(SWay *sOpen)
{
    return (sOpen == NULL ? true : false);
}

/**
 * @brief Initialize stack
 *
 * @param sOpen Stack/list variable
 * @param val Tested value
 *
 * @return true is value is in the stack, false otherwise
**/
bool in_stack(SWay *sOpen, uint8_t from, uint8_t to)
{
    // Find out if expanded path is in stack
    // Check even rotated coordinates
    for(SWay *tmp = sOpen; tmp -> next != NULL; tmp = tmp -> next){
        if(tmp -> coordinates[0] == from && tmp -> coordinates[1] == to){
            return true;
        }
        else if(tmp -> coordinates[0] == to && tmp -> coordinates[1] == from){
            return true;
        }
    }

    return false;
}
