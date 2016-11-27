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
    size_t depth;
    size_t opsLen;
    unsigned int **ops;
    bool semiEulerian;
    unsigned int semiOrigins[2];
} GParams;

void warmUp(GParams *details);

#endif
