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

#include "stack.h"

/**
 * @brief Initialize stack
 *
 * @param sOpen Stack/list variable
**/
void SInit(SList *sOpen)
{
    sOpen -> head =  NULL;
}

/**
 * @brief Push a value to stack
 *
 * @param sOpen stack/list variable
 * @param val New value into stack
 *
 * @return method return true if success, false otherwise
**/
bool SPush(SList *sOpen, char val[])
{
    sitem *tmp = malloc(sizeof(sitem));
    if(tmp == NULL){
        fprintf(stderr, "Error: Item malloc has failed. \n\n");
        return false;
    }

    strcpy(tmp -> path, val);
    tmp -> path[2] = '\0';
    tmp -> next = sOpen -> head;
    sOpen -> head = tmp;

    return true;
}

/**
 * @brief Remove value from top of a stack
 *
 * @param sOpen Stack/list variable
**/
void SPop(SList *sOpen)
{
    sitem *tmp = sOpen -> head;

    sOpen -> head = sOpen -> head -> next;

    free(tmp);
}

/**
 * @brief Get top value from a stack
 *
 * @param sOpen Stack/list variable
 *
 * @return Method return value from top of a stack
**/
char * STop(SList *sOpen)
{
    static char path[3];

    sitem *tmp = sOpen -> head;
    strcpy(path, tmp -> path);

    return path;
}

/**
 * @brief Check if stack is empty
 *
 * @param sOpen Stack/list variable
 *
 * @return True if stack is empty, false otherwise
**/
bool SEmpty(SList *sOpen)
{
    return (sOpen -> head == NULL ? true : false);
}

/**
 * @brief Initialize stack
 *
 * @param sOpen Stack/list variable
 * @param val Tested value
 *
 * @return true is value is in the stack, false otherwise
**/
bool in_stack(SList *sOpen, char val[])
{
    for(sitem *tmp = sOpen -> head; tmp != NULL; tmp = tmp -> next){
        if(strcmp(tmp -> path, val) == 0) return true;
    }

    return false;
}
