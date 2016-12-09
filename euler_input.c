#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    unsigned int **ui;
    unsigned int a, b;
	unsigned int el;
	int i, j;
	char file_name[] = "example.txt"; //*argv[1];
	FILE *fp;
	int c;

	fp = fopen(file_name, "r"); 
	if (fp == NULL) 
	{
        printf("Error in opening file\n");
        return 1;
    }

	if (fscanf(fp, "%d", &el) != 1)
	{
        printf("Error in reading size of array\n");
        return 1;
    }

	do {
	c = fgetc(fp);
	}
	while (isspace(c) || c==10);
	//c = fgetc(fp);
	
    ui = (unsigned int **) malloc(el * (sizeof(unsigned int *)));
    if (ui == NULL)
        return 1;

    for (a = 0; a < el; a++) {
        ui[a] = (unsigned int *) malloc(el * (sizeof(unsigned int)));
        if (ui[a] == NULL)
            return 1;
    }
	//ui[3][3] = c;
	for (i=0; i<el; i++)
	{
		for(j=0; j<el; j++)
		{		
		do {
		c = fgetc(fp);
		/*if (c == 10)
			i++;*/
		} while (c != 48 && c != 49 && c != EOF);
		ui[i][j] = c;
		printf("jakoby: %c\n", c);
		//printf("jakoby: %d\n", ui[i][j]);
		}
	}
	
	printf("jakoby: %d\n", ui[3][3]);

    for (a = 0; a < el; a++) {
        free(ui[a]);
    }
    free(ui);
 
    return 0;
}
