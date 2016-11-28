/**
 *
 * File: dfs.c
 * Description: Header file for DFS source
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/

#ifndef _DFS_H_
#define _DFS_H_

#include <stdbool.h>

typedef struct graphParam{
    size_t depth;                   // Max depth I can go into
    size_t opsLen;                  // Number of operations
    unsigned int **ops;             // Set of operations
    bool semiEulerian;              // Is graph Semi-Eulerian or not
    unsigned int semiOrigins[2];    // Set of origin nodes
} GParams;

void warmUp(GParams *details);      // Call this and start seeking

#endif
