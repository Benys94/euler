/**
 *
 * File: euler_input.c
 * Description: Main program for running algorithm. Checking arguments and reading file.
 * Author: Jan Morávek <xmorav33@stud.fit.vutbr.cz>
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "dfs.h"
#include "pool.h"
#include "error.h"

int check_array(uint8_t **ui, size_t el)
{
	size_t i, j, cnt, cnt2=0, odd=0, even=0, totalCnt=0;
	GParams *graph = (GParams *)MemAlloc(sizeof(GParams));
	if (graph == NULL){
		FatalError(EC_MEM_ALLOC, "Malloc has failed.");}
	graph -> nodes = el;
	graph -> origins[0] = 1;
	graph -> origins[1] = 1;

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
				FatalError(EC_BAD_GRAPH, "Array is not symmetric.");
			}
			cnt+=ui[i][j];
		}

		if(cnt==0)	// checking if graph is continuous (cant be 0 in every row)
		{
			FatalError(EC_BAD_GRAPH, "Graph is not continuous.");
		}


		// checking if graph is euler path or euler cycle
		if(cnt%2==1) // count odd rows
		{
			odd++;
			if(odd>2)
			{
				FatalError(EC_BAD_GRAPH, "Graph is not euler. More than 3 odd nodes.");
			}
			graph->origins[odd-1]=i+1; // getting starting and ending node for euler path
		}
		if(cnt%2==0) // count even rows
			even++;
		totalCnt+=cnt;
	}
	graph->depth=totalCnt/2; // getting graph depth to structure

	size_t graphNodes[graph->depth * 2][2];
	cnt=0;
	for(i=0; i<el; i++)
	{
		for(j=0; j<el; j++)
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

	graph -> ops = (uint8_t**)MemAlloc(sizeof(uint8_t *) * graph->depth * 2);
	if (graph->ops == NULL){
		FatalError(EC_MEM_ALLOC, "Malloc has failed.");}
	for(i=0; i<graph->depth*2; i++){
		graph->ops[i] = (uint8_t *)MemAlloc(sizeof(uint8_t) * 2);
		graph->ops[i][0] = graphNodes[i][0];
		graph->ops[i][1] = graphNodes[i][1];
    }

	/*for (i=0; i<graph->depth * 2; i++) 						// print
	{
		for(j=0; j<2; j++)
		{
			printf(" %u", graph -> ops[i][j]);
		}
		printf(" \n");
	}*/
	warmUp(graph);

	return 0;
}


int main(int argc, char *argv[])
{
	uint8_t **ui;
	size_t el;
	size_t i, j;
	char file_name[50]; // max length of file name
	FILE *fp;
	int c;

	if(argc!=2)
	{
		FatalError(EC_BAD_ARG, "Argument error. Add name of file with graph as first argument.\n");
	}

	strcpy(file_name, argv[1]); // getting name of file from arguments
	fp = fopen(file_name, "r"); // opening file for reading
	if (fp == NULL)
	{
       FatalError(EC_BAD_FILE, "Error in opening file\n");
    }

	if (fscanf(fp, "%zu", &el) != 1) // reading size of array
	{
		fclose(fp);
        FatalError(EC_BAD_FILE, "Error in reading size of array\n");
    }

	// skiping all whitespaces after size of array on first line
	do {
	c = fgetc(fp);
	}
	while (isspace(c) || c==10);

	// allocation size of array
    ui = (uint8_t **) MemAlloc(el * (sizeof(uint8_t *)));
    if (ui == NULL)
	{
		fclose(fp);
		FatalError(EC_MEM_ALLOC, "Malloc has failed.");
	}

    for (i = 0; i < el; i++) {
        ui[i] = (uint8_t *) MemAlloc(el * (sizeof(uint8_t)));
        if (ui == NULL)
		{
			fclose(fp);
			FatalError(EC_MEM_ALLOC, "Malloc has failed.");
		}
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
	fclose(fp);
	check_array(ui, el);
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
    freeAll();

    return 0;
}
