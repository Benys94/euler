/**
 *
 * File: dfs.c
 * Description: Header file for DFS source
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 *
**/

#ifndef _DFS_H_
#define _DFS_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct graphParam{
    size_t nodes;                   // Number of nodes
    size_t depth;                   // Max depth I can go into
    uint8_t **ops;                  // Set of operations
    uint8_t origins[2];             // Set of origin nodes
    bool print;                     // Set if founded paths should be written into file
} GParams;

void warmUp(GParams *details);      // Call this and start seeking

#endif
