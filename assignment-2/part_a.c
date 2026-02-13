/*
* author: sagnik bhattacharjee
* date: feb 6, 2026
* assignment: 2_partA
*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER 1024

int main(int argc, char *argv[]) {
	char buffer[BUFFER];
	
	FILE *fp = fopen(argv[1], "w");
	printf("INPUT: \n");
	while(fgets(buffer, BUFFER, stdin)) { 
		fputs(buffer, fp);
	}
	fclose(fp);
	
	
	fp = fopen(argv[1], "r");
	printf("OUTPUT: \n");
	while(fgets(buffer, BUFFER, fp)) {
		fputs(buffer, stdout);
	}
	fclose(fp);
	
	return 0;
}
