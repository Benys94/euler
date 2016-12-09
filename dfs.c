/**
 *
 * File: dfs.c
 * Description: Implementation of DFS algorithm.
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "dfs.h"
#include "error.h"
#include "stack.h"
#include "pool.h"

long int pathCnt = 0;

// Print one way through Eulerian graph
void print_way(SWay *sOpen)
{
    for(SWay *tmp = sOpen; tmp -> next != NULL; tmp = tmp -> next){
        printf("%u", tmp -> coordinates[1]);
        if(tmp -> next -> next != NULL){
            printf(" -> ");
        }
    }

    printf("\n");
}

/**
 * @brief Method for recursive paths seeking in Eulerian or Semi-Eulerian graphs
 *
 * @param wrapper Wrapper for stacks
 * @param params Details of a graph
 * @param actNode Node where is algorithm located right now
 * @param actDepth Actual depth
**/
void pathSeeker(SWay *sOpen, GParams *params, uint8_t actNode, size_t actDepth)
{
    // Deep meter
    actDepth++;
    // Check if actual node is a goal
    if(actDepth == params -> depth + 1){
        // If this is a goal print path and search next one
        if(sOpen -> coordinates[1]){
            print_way(sOpen);
            pathCnt++;
            return ;
        }
        else {
            FatalError(EC_BAD_PATH, "Founded path is not eulerian.");
        }
    }

    // Expand actual node
    for(size_t i = 0; i < params -> depth * 2; i++){
        if(actNode == params -> ops[i][0]){
            // Expand operation if isn't already in stack
            if( ! in_stack(sOpen, params -> ops[i][0], params -> ops[i][1])){
                sOpen = SPush(sOpen, params -> ops[i][0], params -> ops[i][1]);
                pathSeeker(sOpen, params, STop(sOpen), actDepth);
                sOpen = SPop(sOpen);
            }
        }
    }
}

/**
 * @brief Preparing for path seeking
 *
 * @param details Eulerian graph details
**/
void warmUp(GParams *details)
{
    SWay *origin = SInit();

    bool semiEulerian = (details -> origins[0] != details -> origins[1] ? true : false);

    if(semiEulerian){
        printf("Searching paths in Semi-Eulerian graph.");
    }
    else {
        printf("Searching paths in Eulerian graph.");
    }

    printf("\n%zu nodes", details -> nodes);
    printf("\n%zu edges\n\n", details -> depth);


    for(int start = 0; start < 2; start++){
        origin = SPush(origin, 0, details -> origins[start]);
        pathSeeker(origin, details, details -> origins[start], 0);
        origin = SPop(origin);

        if( ! semiEulerian)
            break;
    }

    printf("\n\n%ld founded paths.\n", pathCnt);
}
