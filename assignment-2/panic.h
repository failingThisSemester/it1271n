#ifndef PANIC_H
#define PANIC_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#define BUFFER 1024

void scream(const char *msg) {
	while(*msg)
		write(2, msg++, 1);
	
	write(2, "\n", 1);
	_exit(1);
}

void talk(const char *msg) {
	while(*msg)
		write(1, msg++, 1);
	write(1, "\n", 1);
}

#endif
