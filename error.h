/**
 * File: erro.h
 * Description: Module for error handling
 * Author: David Benes <xbenes41@stud.fit.vutbr.cz>
 * VUT FIT 2016
**/

#ifndef _ERROR_H_
#define _ERROR_H_

typedef enum {

    // OK
    EC_SUCCESS = 0,
    // Memory allocation failed.
    EC_MEM_ALLOC = 1,
    // Bad eulerian path.
    EC_BAD_PATH = 2,
	// Bad euler graph.
	EC_BAD_GRAPH = 10,
	// Bad arguments.
	EC_BAD_ARG = 11,
	// Bad file.
	EC_BAD_FILE = 12,
    // Others fails.
    EC_OTHER = 99

} ERROR_CODE;

void FatalError(ERROR_CODE errCode, char *errMsg);

#endif
