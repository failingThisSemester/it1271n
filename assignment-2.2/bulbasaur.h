/*
a minimal reimplementation of stdio.h
*/

#ifndef BULBASAUR_H
#define BULBASAUR_H


#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdarg.h>


void bulbaPrintf(const char *text, ...);
void _printfFloat(double value);
void _printfInt(int value);
	

void bulbaPrintf(const char *text, ...) {
	va_list pointer;
	va_start(pointer, text);
	
	while(*text) {
		if (*text == '%' && *(text + 1) == 'd') {
			int value = va_arg(pointer, int);
			_printfInt(value);
			text += 2;
			continue;
		}
		else if (*text == '%' && *(text + 1) == 'f') {
			double value = va_arg(pointer, double);
			_printfFloat(value);
			text += 2;
			continue;
		}
		write(1, text++, 1);
	}
}

/*
void bulbaPrintf(const char *text, int value) {
	while(*text) {
		if (*text == '%' && *(text + 1) == 'd') {
			_printfInt(value);
			text += 2;
			continue;
		}
		write(1, text++, 1);
	}
}
*/


void _printfFloat(double value) {
	if (value < 0) {
		write(1, "-", 1);
		value = -value;
	}
	
	long long int_value = (long long)value;
	double frac_value = value - int_value;
	
	_printfInt(int_value);
	write(1, ".", 1);

	// supporting just 2 decimal places for now
	for(int i = 0; i < 2; i++) {
		frac_value *= 10;
		long long digit = (long long)frac_value;
		char c = '0' + digit;
		write(1, &c, 1);
		frac_value -= digit;	
	}
}


void _printfInt(int value) {
	char buffer[32];
	if (value == 0) {
		write(1, "0", 1);
		return;
	}
		
	if (value < 0) {	
		write(1, "-", 1);
		value = -value;
	}
		
	int i = 0;
	while(value > 0) {
		buffer[i++] = '0' + (value%10);
		value/=10;
	}
	while(i--) {
		write(1, &buffer[i], 1);
	}
}


void bulbaScream(const char *msg) {
	while(*msg)
		write(2, msg++, 1);
		
	write(2, "\n", 1);
	_exit(1);
}


void bulbaWrite(const char *msg) {
	while(*msg)
		write(1, msg++, 1);

	write(1, "\n", 1);
}



#endif