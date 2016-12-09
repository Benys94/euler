/**
 * File: error.c
 * Description: Error handling functions
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 * VUT FIT 2016
**/

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "pool.h"

void FatalError(ERROR_CODE errCode, char *errMsg)
{
    fprintf(stderr, "Error: %s \n\n", errMsg);
    freeAll();
    exit(errCode);
}
