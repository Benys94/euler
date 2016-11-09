/**
 *
 * File: generator.c
 * Description: Operations for graph generating
 * Author: Marek Jankech <xjanke01@stud.fit.vutbr.cz>
 *
 **/

#include "generator.h"

/**
 * Swapping function
 */
void swap(int* a1, int *a2 ) {
   int aux;

   aux = *a1;
   *a1 = *a2;
   *a2 = aux;
}

/**
 * Random number generator, 0...n-1
 */
int my_random(int n) {
   return rand() % n;
}

/**
 * Function for rearranging elements of array
 */
void rearrange(int* array, int n) {
   int i;

   for (i = 0; i < n - 1; i++)
      swap(array + i + my_random(n - i), array + i);
}

/**
 * Function that manages generating the right graph with selected parameters and properties
 */
void graph_generating_manager(uint8_t *matrix, int nodes, int edges, TProperty property) {
  switch (property) {
    case RANDOM:
      random_graph(matrix, nodes, edges);
      break;
    case CONNECTED:
      connected_random_graph(matrix, nodes, edges);
      break;
    case EULER_TRAIL:
      euler_trail_random_graph(matrix, nodes, edges);
      break;
    case EULER_CYCLE:
      //euler_cycle_random_graph();
      //Should be done in near future
      break;
    default:
      random_graph(matrix, nodes, edges);
      break;
  }
}

/**
 * Generator of general random graphs without any specification and
 * with the probablity of isolated vertices or partitions
 */
void random_graph(uint8_t *matrix, int nodes, int edges) {
  int i, j, k;
  
  //Generate some random edges of the graph
	for (k = 0; k < edges;) {
		i = my_random(nodes);
		j = my_random(nodes);

		//Do not write to the diagonale and do not rewrite the edges that were already set
    if (i != j && !matrix[i * nodes + j]) {
			 matrix[i * nodes + j] = matrix[j * nodes + i] = 1;
			 k++;
		}
  }
}

/**
 * Generator of connected random graphs without any isolated vertices or
 * partitions
 */
void connected_random_graph(uint8_t *matrix, int nodes, int edges) {
	int *aux_array, i, j, k;
	
	//Allocate memory for auxilliary array
	if((aux_array = (int *) malloc(nodes * sizeof(int))) == NULL) {
		perror("malloc");
		exit(1);
	}
  
	//Initialize auxilliary array
	for (i = 0; i < nodes; i++) {
		aux_array[i] = i;
	}
	
	//Rearrange elements of aux array
	rearrange(aux_array, nodes);
	
	//Generate random spanning tree
	for (i = 1; i < nodes; i++) {
		j = my_random(i);
		matrix[aux_array[i] * nodes + aux_array[j]] = matrix[aux_array[j] * nodes + aux_array[i]] = 1;
  }
	
	//Generate remaining random edges of the graph
	for (k = nodes - 1; k < edges;) {
		i = my_random(nodes);
		j = my_random(nodes);

		//Do not write to the diagonale and do not rewrite the edges that were already set
    if (i != j && !matrix[i * nodes + j]) {
			 matrix[i * nodes + j] = matrix[j * nodes + i] = 1;
			 k++;
		}
  }
  //Free the memory for aux array
  free(aux_array);
}

/**
 * Generator of connected random graphs with Eulerian trails
 * Every element on the diagonale will contain the number of degree 
 * of the vertex on that row (and column).
 */
void euler_trail_random_graph(uint8_t *matrix, int nodes, int edges) {
	int i, j, alone;
  const int max_degree = nodes - 1;
	
  //Generate random vertex and initialize the number of alone vertices
  i = my_random(nodes);
  printf("First i: %d", i);
  alone = nodes - 1;
  
  //Generating random edges
  while (alone < edges) {
    //Generate random vertex, not the same as the one before
    do {
      j = my_random(nodes);
    }
    while (i == j);
    
    //Do not rewrite the edges that were already set, write just new edges,
    //update the number on the diagonale and decrement the number of remaining
    //edges
    if (!matrix[i * nodes + j]) {
       matrix[i * nodes + j] = 1;
       matrix[i * nodes + i] += 1;
       matrix[j * nodes + i] = 1;
       matrix[j * nodes + j] += 1;
       edges--;
       
       //Decrement the number of alone vertices just if the new vertex was
       //alone before this iteration
       if (matrix[j * nodes + j] == 1) {
         alone--;
       }
       //Select the last vertex
       i = j;
    }
    
    //If it cannot continue because of max degree in some node, clear the number
    //of remaining edges = finish the generating algorithm
    if (matrix[i * nodes + j] == max_degree) {
      edges = 0;
    }
  }
  
  //Reinitialize second index to the beginning for the next cycle
  if (i == 0)
    j = 1;
  else
    j = 0;
  //Generating remainig edges just for the remainig alone vertices
  while (edges) { 
    //Processing just the diagonale of the matrix and searching for zero values
    while(matrix[j * nodes + j]) {
      j++;
    }
    //Write just new edges, update the number on the diagonale and decrement 
    //the number of remaining edges
    matrix[i * nodes + j] = 1;
    matrix[i * nodes + i] += 1;
    matrix[j * nodes + i] = 1;
    matrix[j * nodes + j] += 1;
    edges--;
    //Select the last vertex and increment the second index
    i = j;
    j++;
  }
}

/**
 * Generator of connected random graphs with Eulerian cycles
 * Every element on the diagonale will contain the number of degree 
 * of the vertex on that row (and column).
 */
void euler_cycle_random_graph(uint8_t *matrix, int nodes, int edges) {
	int i, j, alone;
	
  //Generate random vertex and initialize the number of alone vertices
  i = my_random(nodes);
  alone = nodes - 1;
  
  //Generating random edges
  while (alone < edges) {
    //Generate random vertex, not the same as the one before
    do {
      j = my_random(nodes);
    }
    while (i == j);
    
    //Do not rewrite the edges that were already set, write just new edges,
    //update the number on the diagonale and decrement the number of remaining
    //edges
    if (!matrix[i * nodes + j]) {
       matrix[i * nodes + j] = 1;
       matrix[i * nodes + i] += 1;
       matrix[j * nodes + i] = 1;
       matrix[j * nodes + j] += 1;
       edges--;
       
       //Decrement the number of alone vertices just if the new vertex was
       //alone before this iteration
       if (matrix[j * nodes + j] == 1) {
         alone--;
       }
       //Select the last vertex
       i = j;
    }
  }
  
  //Reinitialize second index to the beginning for the next cycle
  j = 0;
  //Generating remainig edges just for the remainig alone vertices
  while (edges) { 
    //Processing just the diagonale of the matrix and searching for zero values
    while(matrix[j * nodes + j]) {
      j++;
    }
    //Write just new edges, update the number on the diagonale and decrement 
    //the number of remaining edges
    matrix[i * nodes + j] = 1;
    matrix[i * nodes + i] += 1;
    matrix[j * nodes + i] = 1;
    matrix[j * nodes + j] += 1;
    edges--;
    //Select the last vertex and increment the second index
    i = j;
    j++;
  }
}

/**
 * Function that manages printing the matrix to the output file or stdout 
 * For debugging
 */
void matrix_printing_manager(int nodes, uint8_t *matrix, bool print_to_stdout) {
	
  if(print_to_stdout) {
    matrix_printer(nodes, matrix, stdout);
  }
  else {
    FILE *fw = fopen("matrix.txt", "w");
    matrix_printer(nodes, matrix, fw);
    fclose(fw);
  }
}

/**
 * Matrix printer
 * For debugging
 * Kind of a little ASCII art
 */
void matrix_printer(int nodes, uint8_t *matrix, FILE *output_stream) {
  fprintf(output_stream, "   |");
	for (int i = 0; i < nodes; i++) {
		fprintf(output_stream, "% d |", i);
	}
  fprintf(output_stream, "\n");
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j <= nodes; j++) {
			fprintf(output_stream, "----");
		}
		fprintf(output_stream, "\n %d |", i);
		for (int j = 0; j < nodes; j++) {
			fprintf(output_stream, " %d |", matrix[i * nodes + j]);
		}
    fprintf(output_stream, "\n");
	}
}
