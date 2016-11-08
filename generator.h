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
#include <stdint.h>
#include <time.h>

/**
 * Enum type properties of the graph
 */
typedef enum {
    RANDOM = 0,
    CONNECTED = 1,
    EULER_TRAIL = 2,
    EULER_CYCLE = 3
  } TProperty;

/**
 * Prototypes
 */
void swap(int* a1, int *a2);
int my_random(int n);
void rearrange(int* array, int n);
void graph_generating_manager(uint8_t *matrix, int nodes, int edges, TProperty property);
void random_graph(uint8_t *matrix, int nodes, int edges);
void connected_random_graph(uint8_t *matrix, int nodes, int edges);
void euler_trail_random_graph(uint8_t *matrix, int nodes, int edges);
void matrix_printing_manager(int nodes, uint8_t *matrix, bool print_to_stdout);
void matrix_printer(int nodes, uint8_t *matrix, FILE *output_stream);

#endif /* GENERATOR_H */

