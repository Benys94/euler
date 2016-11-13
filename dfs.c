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

#include "error.h"
#include "stack.h"
#include "pool.h"

#define MAX_DEPTH (8)

int operations[16][2] = {
    {1,2},
    {1,3},
    {1,4},
    {2,1},
    {2,3},
    {2,4},
    {3,1},
    {3,2},
    {3,4},
    {3,5},
    {4,1},
    {4,2},
    {4,3},
    {4,5},
    {5,3},
    {5,4},
};

void print_way(SWay *sOpen)
{
    for(SWay *tmp = sOpen; tmp -> next != NULL; tmp = tmp -> next){
        printf("%d", tmp -> coordinates[1]);
        if(tmp -> next -> next != NULL){
            printf(" -> ");
        }
    }

    printf("\n");
}

bool dfs_run(PWrap *wrapper, int actNode[], int depth)
{
    if(wrapper_empty(wrapper)){
        if(depth == 0){
            FatalError(EC_BAD_PATH, "No origin node.");
        }
    }

    SWay *sOpen = top_stack(wrapper);
    wrapper = pop_stack(wrapper);


    if(depth == MAX_DEPTH){
        if(sOpen -> coordinates[1] == 1){
            print_way(sOpen);
            return true;
        }
        else {
            FatalError(EC_BAD_PATH, "Founded path is not eulerian.");
        }
    }

    for(int i = 0; i < 16; i++){
        if(actNode[1] == operations[i][0]){
            if( ! in_stack(sOpen, operations[i][0], operations[i][1])){
                SWay *new_stack = SPush(sOpen, operations[i][0], operations[i][1]);
                wrapper = push_stack(wrapper, new_stack);
            }
        }
    }

    if( ! dfs_run(wrapper, STop(top_stack(wrapper)), ++depth)){
        return false;
    }

    return true;
}

int main()
{
    pool_init();

    PWrap *wrapper = wrap_init();

    int poc[2] = {0, 2};
    SWay *origin = SInit();

    SWay *new_stack = SPush(origin, poc[0], poc[1]);
    wrapper = push_stack(wrapper, new_stack);

    if( ! dfs_run(wrapper , poc, 0)){
        return EXIT_FAILURE;
    }

    pool_free();
    return EXIT_SUCCESS;
}
