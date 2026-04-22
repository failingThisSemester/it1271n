#include <stdio.h>


int main(int argc, char *argv[]) {
	FILE *f = fopen(argv[1], "rb");
	
	unsigned char buf[1024];
	size_t n;

	while 
		((n = fread(buf, 1, sizeof(buf), f)) > 0) {
			fwrite(buf, 1, n , stdout);
		}
	fclose(f);
	return 0;
}