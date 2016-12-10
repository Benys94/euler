/**
 *
 * File: generator.h
 * Description: Module for generating graphs
 * Author: Marek Jankech <xjanke01@stud.fit.vutbr.cz>
 *
 **/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define DECIMAL 10

/**
 * Enum types
 */
typedef enum {
    RANDOM = 0,
    CONNECTED = 1,
    EULER_TRAIL = 2,
    EULER_CYCLE = 3
  } TProperty;
  
typedef enum {
    OK = 0,
    ARG_NUM = 1,
    NODES = 2,
    EDGES = 3,
    PROPERTY = 4    
  } TErrCode;

/**
 * Prototypes
 */
void swap(int* a1, int *a2);
int my_random(int n);
void rearrange(int* array, int n);
void graph_generating_manager(uint8_t *matrix, int nodes, int edges, TProperty property);
void random_graph(uint8_t *matrix, int nodes, int edges);
void connected_random_graph(uint8_t *matrix, int nodes, int edges);
void euler_trail_random_graph(uint8_t *matrix, int nodes, int edges, int *start_node, int *end_node);
void euler_cycle_random_graph(uint8_t *matrix, int nodes, int edges, int *start_node, int *end_node);
void matrix_printing_manager(int nodes, uint8_t *matrix, bool print_to_stdout);
void matrix_printer(int nodes, uint8_t *matrix, FILE *output_stream);
void checkArgs(int argc, char *argv[], int *nodes, int *edges, TProperty *property);
void print_help(TErrCode err);

#endif /* GENERATOR_H */

