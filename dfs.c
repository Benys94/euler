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
void pathSeeker(PWrap *wrapper, GParams *params, unsigned int actNode, size_t actDepth)
{
    // Fail if there is no origin node
    if(wrapper_empty(wrapper)){
        FatalError(EC_BAD_PATH, "No origin node.");
    }

    // Get actual stack that will be expanded and throw away non-expanded stack
    SWay *sOpen = top_stack(wrapper);
    wrapper = pop_stack(wrapper);

    // Check if actual node is a goal
    if(actDepth == params -> depth){
        // If this is a goal print path and search next one
        if(sOpen -> coordinates[1]){
            print_way(sOpen);
            freeGoalPath(1 + SLen(sOpen) - SLen(wrapper->path));
            pathSeeker(wrapper, params, STop(top_stack(wrapper)), SLen(wrapper -> path));
            return ;
        }
        else {
            FatalError(EC_BAD_PATH, "Founded path is not eulerian.");
        }
    }

    // Expand actual node
    bool deadEnd = true;
    for(size_t i = 0; i < params -> opsLen; i++){
        if(actNode == params -> ops[i][0]){
            // Expand operation if isn't already in stack
            if( ! in_stack(sOpen, params -> ops[i][0], params -> ops[i][1])){
                SWay *new_stack = SPush(sOpen, params -> ops[i][0], params -> ops[i][1]);
                wrapper = push_stack(wrapper, new_stack);
                deadEnd = false;
            }
        }
    }

    // When you can't exapnd anything go back
    if(deadEnd){
        if(wrapper -> path != NULL){
            freeGoalPath(1 + SLen(sOpen) - SLen(wrapper->path));
            pathSeeker(wrapper, params, STop(top_stack(wrapper)), SLen(wrapper -> path));
        }
        return ;
    }

    // Go deeper
    pathSeeker(wrapper, params, STop(top_stack(wrapper)), ++actDepth);
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
    if(details -> semiEulerian){
        for(int start = 0; start < 2; start++){

            PWrap *wrapper = wrap_init();
            SWay *origin = SInit();

            SWay *new_stack = SPush(origin, 0, details -> semiOrigins[start]);
            wrapper = push_stack(wrapper, new_stack);
            pathSeeker(wrapper, details, details -> semiOrigins[start], 0);
        }
    }

}
