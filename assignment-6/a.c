#include <stdio.h>
#include <stdarg.h>

int search(int key, int count, ...) {
	va_list args;
	va_start(args, count);

	for(int i = 0; i < count; i++) {
		if (va_arg(args, int) == key) {
			va_end(args);
			return 1;
		}
	}
	va_end(args);
	return 0;
}

int main() {
	int found = search(4, 3, 1,2,3);
	printf("found: %d\n", found);
}