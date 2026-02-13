/*
* author: sagnik bhattacharjee
* date: feb 6, 2026
* assignment: 2_partB
*/

#include "panic.h"

int main(int argc, char *argv[]) {
	char buffer[BUFFER];
	int n;
	
	// WRITE OPERATION
	
	int file = open(argv[1], O_WRONLY | O_APPEND);
	if(file < 0) scream("open(write) failed");
	talk("INPUT: ");
	while((n = read(0, buffer, BUFFER)) > 0) {
		if (write(file, buffer, n) != n)
			scream("write(file) failed");
	}
	if (n < 0) scream("read(stdin) failed");
	if (close(file) < 0) scream("close(write file) failed");
	
	// READ OPERATION
	
	file = open(argv[1], O_RDONLY);
	if(file < 0) scream("open(read) failed");
	talk("OUTPUT: ");
	while((n = read(file, buffer, BUFFER)) > 0) {
		if (write(1, buffer, n) != n)
			scream("read(stdout) failed");
	}
	if (n < 0) scream("read(file) failed");
	if (close(file) < 0) scream("close(read file) failed");
	return 0;
}
