#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "dfs.h"

int check_array(uint8_t **ui, size_t el)
{
	size_t i, j, cnt, cnt2=0, odd=0, even=0, totalCnt=0;
	struct graphParam* graph;
	graph = malloc(sizeof(struct graphParam));

	// setting diagonal to 0
	for(i=0; i<el; i++)
	{
		ui[i][i]=0; 
	}
	
	for (i=0; i<el; i++)
	{
		cnt=0;
		for(j=0; j<el; j++)
		{		
			if(ui[i][j]!=ui[j][i]) // checking if array is symmetric
			{
				printf("Array is not symmetric.\n");
				return 0;
			}
			cnt+=ui[i][j];
		}

		if(cnt==0)	// checking if graph is continuous (cant be 0 in every row)
		{			
			printf("Graph is not continuous.\n");
			return 0;
		}

	
		// checking if graph is euler path or euler cycle			
		if(cnt%2==1) // count odd rows
		{
			odd++;
			if(odd>2)
			{
				printf("Graph is not euler. More than 3 odd nodes.\n");
				return 0;
			}
			graph->origins[odd-1]=i+1; // getting starting and ending node for euler path
		}		
		if(cnt%2==0) // count even rows
			even++;
		totalCnt+=cnt;
	}
	graph->depth=totalCnt/2; // getting graph depth to structure
	
	size_t graphNodes[graph->depth][2];
	cnt=0;
	for(i=0; i<el; i++)
	{
		for(j=cnt; j<el; j++)
		{
			if (ui[i][j] == 1)
			{
				graphNodes[cnt2][0]=i+1;
				graphNodes[cnt2][1]=j+1;
				cnt2++;
			}
		}
		cnt++;
	}

    graph -> ops = (uint8_t**)malloc(sizeof(uint8_t *) * graph->depth * 2);

    for(i=0; i<graph->depth*2; i++){
        graph->ops[i] = (uint8_t *)malloc(sizeof(uint8_t) * 2);
        graph->ops[i][0] = graphNodes[i][0];
        graph->ops[i][1] = graphNodes[i][1];
    }
	/*
	for (i=0; i<graph->depth; i++) 						// print
	{
		for(j=0; j<2; j++)
		{
			printf(" %d", graphNodes[i][j]);		
		}
		printf(" \n");
	}
	*/
	
	if(odd==2) {
		return 1; // graph is euler path
	} else if(odd==0 && even==el) {
		graph->origins[0]=1; // getting starting and ending node for euler cycle
		graph->origins[1]=1;
		return 2; // graph is euler cycle
	} else {
		return 0; // graph is not euler graph	
	}
}


int main(int argc, char *argv[])
{
	uint8_t **ui;
	size_t el;
	size_t i, j;
	char file_name[50]; // max length of file name
	FILE *fp;
	int c;
	size_t tmp;

	if(argc!=2)
	{
		printf("Argument error. Add name of file with graph as first argument.\n");
        return 1;
	}	

	strcpy(file_name, argv[1]); // getting name of file from arguments
	fp = fopen(file_name, "r"); // opening file for reading 
	if (fp == NULL) 
	{
        printf("Error in opening file\n");
        return 1;
    }

	if (fscanf(fp, "%zu", &el) != 1) // reading size of array
	{
        printf("Error in reading size of array\n");
        return 1;
    }

	// skiping all whitespaces after size of array on first line
	do {
	c = fgetc(fp);
	}
	while (isspace(c) || c==10);

	// allocation size of array 
    ui = (uint8_t **) malloc(el * (sizeof(uint8_t *)));
    if (ui == NULL)
        return 1;

    for (i = 0; i < el; i++) {
        ui[i] = (uint8_t *) malloc(el * (sizeof(uint8_t)));
        if (ui[i] == NULL)
            return 1;
    }

	// filling array from file
	for (i=0; i<el; i++)
	{
		for(j=0; j<el; j++)
		{		
		do {
		c = fgetc(fp);
		} while (c != '0' && c != '1' && c != EOF);
		if(c=='0')		
			ui[i][j] = 0;
		if(c=='1')		
			ui[i][j] = 1;
		}
	}
	/*
	for (i=0; i<el; i++) 						// print
	{
		for(j=0; j<el; j++)
		{
			printf(" %d", ui[i][j]);		
		}
		printf(" \n");
	}
	*/	
	tmp = check_array(ui, el);
	if(tmp == 1)
	{		
		printf("It is euler path. \n");
		return 1;
	}	
	else if(tmp == 2)
	{		
		printf("It is euler cycle. \n");
		return 1;
	}
	else if(tmp == 0)
	{
		printf("It is not euler graph. \n");
		return 0;
	}
		


	for (i = 0; i < el; i++) // free memory
	{
        free(ui[i]);
    }
    free(ui);
 
    return 0;
}
