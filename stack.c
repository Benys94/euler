/**
 *
 * File: stack.c
 * Description: Operations over stack
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"
#include "stack.h"
#include "pool.h"


///////////////////
// Stack wrapper //
///////////////////

PWrap * wrap_init()
{
    PWrap *new_wrap = (PWrap *)MemAcq(sizeof(PWrap));
    new_wrap -> path = NULL;
    new_wrap -> next = NULL;

    return new_wrap;
}

PWrap * push_stack(PWrap *wrapper, SWay *sOpen)
{
    PWrap *tmp = (PWrap *)MemAcq(sizeof(PWrap));

    tmp -> path = sOpen;

    tmp -> next = wrapper;
    wrapper = tmp;

    return wrapper;
}

PWrap * pop_stack(PWrap *wrapper)
{
    return wrapper -> next;
}

SWay * top_stack(PWrap *wrapper)
{
    return wrapper -> path;
}

bool wrapper_empty(PWrap *wrapper)
{
    return (wrapper == NULL ? true : false);
}


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
    SWay *new_way = (SWay *)MemAcq(sizeof(SWay));
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
SWay * SPush(SWay *sOpen, int from, int to)
{
    SWay *new_item = (SWay *)MemAcq(sizeof(SWay));

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
void SPop(SWay *sOpen)
{
    sOpen = sOpen -> next;
}

/**
 * @brief Get top value from a stack
 *
 * @param sOpen Stack/list variable
 *
 * @return Method return value from top of a stack
**/
int * STop(SWay *sOpen)
{
    static int coordinates[2];

    coordinates[0] = sOpen -> coordinates[0];
    coordinates[1] = sOpen -> coordinates[1];

    return coordinates;
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
bool in_stack(SWay *sOpen, int from, int to)
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
