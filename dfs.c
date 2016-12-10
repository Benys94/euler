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
void print_way(SWay *sOpen, FILE *outPaths)
{
    for(SWay *tmp = sOpen; tmp -> next != NULL; tmp = tmp -> next){
        fprintf(outPaths, "%u", tmp -> coordinates[1]);
        if(tmp -> next -> next != NULL){
            fprintf(outPaths, " -> ");
        }
    }
    fprintf(outPaths, "\n");
}

/**
 * @brief Method for recursive paths seeking in Eulerian or Semi-Eulerian graphs
 *
 * @param wrapper Wrapper for stacks
 * @param params Details of a graph
 * @param actNode Node where is algorithm located right now
 * @param actDepth Actual depth
**/
void pathSeeker(SWay *sOpen, GParams *params, uint8_t actNode, size_t actDepth, FILE *outPaths)
{
    // Deep meter
    actDepth++;

    // Check if actual node is a goal
    if(actDepth == params -> depth + 1){
        print_way(sOpen, outPaths);
        pathCnt++;
        return ;
    }

    // Expand actual node
    for(size_t i = 0; i < params -> depth * 2; i++){
        if(actNode == params -> ops[i][0]){
            // Expand operation if isn't already in stack
            if( ! in_stack(sOpen, params -> ops[i][0], params -> ops[i][1])){
                sOpen = SPush(sOpen, params -> ops[i][0], params -> ops[i][1]);
                pathSeeker(sOpen, params, STop(sOpen), actDepth, outPaths);
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
    FILE *outPaths = fopen("paths.txt", "w");

    bool semiEulerian = (details -> origins[0] != details -> origins[1] ? true : false);

    if(semiEulerian){
        printf("Searching paths in Semi-Eulerian graph.");
    }
    else {
        printf("Searching paths in Eulerian graph.");
    }

    printf("\n%zu nodes", details -> nodes);
    printf("\n%zu edges\n", details -> depth);


    origin = SPush(origin, 0, details -> origins[0]);
    pathSeeker(origin, details, details -> origins[0], 0, outPaths);
    origin = SPop(origin);

    fclose(outPaths);
    printf("\n%ld founded paths.\n", pathCnt);
    printf("You can see all paths in 'paths.txt'\n");
}
