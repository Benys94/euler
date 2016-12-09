#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

int check_array(unsigned int **ui, int el)
{
	int i, j, cnt, odd=0, even=0;

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
			odd++;
		if(cnt%2==0) // count even rows
			even++;
	}

	if(odd==2) {
		return 1; // graph is euler path
	} else if(odd==0 && even>0) {
		return 2; // graph is euler cycle
	} else {
		return 0; // graph is not euler graph	
	}
}


int main(int argc, char *argv[])
{
	unsigned int **ui;
	unsigned int el;
	int i, j;
	char file_name[50]; // max length of file name
	FILE *fp;
	int c;

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

	if (fscanf(fp, "%d", &el) != 1) // reading size of array
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
    ui = (unsigned int **) malloc(el * (sizeof(unsigned int *)));
    if (ui == NULL)
        return 1;

    for (i = 0; i < el; i++) {
        ui[i] = (unsigned int *) malloc(el * (sizeof(unsigned int)));
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

	for (i=0; i<el; i++) 						// print (smazat)
	{
		for(j=0; j<el; j++)
		{
			printf(" %d", ui[i][j]);		
		}
		printf(" \n");
	}
		
	if(check_array(ui, el) == 1)
	{		
		printf("It is euler path. \n");
		return 1;
	}	
	if(check_array(ui, el) == 2)
	{		
		printf("It is euler cycle. \n");
		return 1;
	}
	if(check_array(ui, el) == 0)
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
