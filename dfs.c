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

#include "dfs.h"
#include "error.h"
#include "stack.h"
#include "pool.h"

int pathCnt = 0;

// Method prints stack content into log file
void stack_dump(PWrap *wrapper)
{
    FILE *logFile = fopen("log.txt", "w");
    fprintf(logFile, "[\n");
    for(PWrap *tmpWrap = wrapper; tmpWrap -> next != NULL; tmpWrap = tmpWrap -> next){
        fprintf(logFile, "\t[\n");
        for(SWay *tmpWay = tmpWrap -> path; tmpWay -> next != NULL; tmpWay = tmpWay -> next){
            fprintf(logFile, "\t\t[%d, %d]\n", tmpWay -> coordinates[0], tmpWay -> coordinates[1]);
        }
        fprintf(logFile, "\t],\n");
    }
    fprintf(logFile, "]\n");

    fclose(logFile);
}

// Print one way through Eulerian graph
void print_way(SWay *sOpen)
{
    // printf("%zu, %d: "++pathCnt);
    for(SWay *tmp = sOpen; tmp -> next != NULL; tmp = tmp -> next){
        printf("%d", tmp -> coordinates[1]);
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
 *
 * @bug Big memory consumption
**/
void pathSeeker(SWay *sOpen, GParams *params, unsigned int actNode, size_t actDepth)
{

    // Check if actual node is a goal
    if(actDepth == params -> depth){
        // If this is a goal print path and search next one
        if(sOpen -> coordinates[1]){
            print_way(sOpen);
            return ;
        }
        else {
            FatalError(EC_BAD_PATH, "Founded path is not eulerian.");
        }
    }

    // Deep meter
    actDepth++;

    // Expand actual node
    // bool deadEnd = true;
    for(size_t i = 0; i < params -> opsLen; i++){
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
 *
 * @bug Seeking paths only in semi-eulerian graphs
**/
void warmUp(GParams *details)
{
    SWay *origin = SInit();
    if(details -> semiEulerian){
        for(int start = 0; start < 2; start++){
            origin = SPush(origin, 0, details -> semiOrigins[start]);
            pathSeeker(origin, details, details -> semiOrigins[start], 0);
            origin = SPop(origin);
        }
    }

}
