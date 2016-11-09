/**
 *
 * File: main.c
 * Description: Main file for the graph generator
 * Author: Marek Jankech <xjanke01@stud.fit.vutbr.cz>
 *
 **/

#include "generator.h"

int main() {
  int n = 5, e = 10;  //Specifying the number of nodes and edges that would be processed
	uint8_t *matrix;
	
	//Seed the generator of random numbers
	srand(time(NULL));
  //Allocate memory for adjacency matrix
	if((matrix = (uint8_t *) malloc(n * n * sizeof(uint8_t))) == NULL) {
		perror("malloc");
		exit(1);
	}
  
	//Create random graph with selected property and parameters
	graph_generating_manager(matrix, n, e, EULER_TRAIL);
	//Print the matrix - for debugging
  matrix_printing_manager(n, matrix, false);
  //Free the memory for the matrix
  free(matrix);
  
  return 0;
}

