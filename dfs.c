/**
 *
 * File: dfs.c
 * Description: Implementation of DFS algorithm.
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

int main()
{
    // Allocate memory for new stack
    SList *sOpen = malloc(sizeof(SList));
    if(sOpen == NULL){
        fprintf(stderr, "Error: Stack malloc has failed.\n\n");
        return 1;
    }

    // Init stack
    SInit(sOpen);


    // Clening part
    while (!SEmpty(sOpen)){
        SPop(sOpen);
    }

    free(sOpen);
    return 0;
}
