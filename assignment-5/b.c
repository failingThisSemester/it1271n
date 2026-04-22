#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	DIR *d;
	struct dirent *entry;

	d = opendir(argv[1]);
	while((entry = readdir(d)) != NULL)	 {
		printf("%s\n", entry->d_name);
	}
	closedir(d);
	return 0;
}
