/*
* author: sagnik bhattacharjee
* date: march 6, 2026
* assignment: 3
*/

/*
objective: 
 	allocate a contiguous linear memory for storing int values
 	[ 4 bytes ] [ 4 bytes ] [ 4 bytes ] ... [ 4 bytes ]
	0 to n-1 -> n cells -> (4n) bytes

references:
	[1] https://www.linuxquestions.org/questions/linux-general-1/in-linux-malloc-initializes-to-zero-843577/#post4155432
	[2] https://stackoverflow.com/questions/8029584/why-does-malloc-initialize-the-values-to-0-in-gcc
	[3] https://sourceware.org/glibc/manual/latest/html_mono/libc.html#Dynamic-Memory-Allocation
	[4] https://www.kernel.org/doc/Documentation/vm/overcommit-accounting

note:
	malloc() never* fails on linux
	*except when memory overcommiting is turned off.
*/

#include <stdlib.h>
#include <stdio.h>

int main() {

	/*  
	1. malloc allocated memory and all were initialised to 0
	2. why not garbled? answer in reference [1] link
	3. to put simply, it might not have been utilized so soon by any other process
	4. memset() is necessary to gurantee that memory has been allocated, otherwise malloc just _promises_.	
	*/
	
	printf(" == malloc() == \n");
	int n = 1000;
	int *data1 = malloc(sizeof(int) * n);
	for(int i = 0; i < n; ++i) data1[i] = (i*2 + 1);
	printf("\nAddress: %p\n", data1);
	free(data1);
	
	printf("\n == calloc() == \n");
	int *data2 = (int*)calloc(n, sizeof(int));
	printf("\nAddress: %p\n", data1);
	printf("\n");
	free(data2);
	
	/*
	1. new address appears ONLY if the new memory allocated demands space which is beyond whatever was previously present as a free
	2. using n * 200 (a big memalloc demonstrates that fact)
	*/

	printf("\n == realloc() == \n");
	int *data3 = malloc(sizeof(int) * n);
	printf("\nOld Address: %p\n", data3);
	int n2 = n * 200;
	int *temp =	 realloc(data3, sizeof(int) * (n2));
	data3 = temp;
	printf("\nNew Address: %p\n", data3);
	free(data3);
}