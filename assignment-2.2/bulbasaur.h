/*
a minimal reimplementation of stdio.h

TODO: 
1. printf(const char *format, ...);
	printf("sentnce %d", 1);
	printf("a: %d, b: %d", 1, 2);
	taking things as printf("string %d", 1); it should print "string 1"
	
	how can i approach this?
	
	it smells as if i need to parse the string expression? regex is one option but too hard
	passing the integer as a string is another way maybe? something like 
	
	"hello here is an integer %d", 1234
	and we detect that "%d", so uh a sliding window with 2 unit dist?
	
	and then we use that integer, use some modulus and division operations, 
	switch case with digit detection to print the integer as a string
	
	this CAN be one way.
	
	so it is:
		we take a string, use sliding window with 2 unit window length, 
		detect the formatter pattern 
		go to the other parameter, detect digits, print as characters
		
	or maybe, variadic functions ??
	
	yes single value works, ill check out variadic functions now.
	
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
	
	GNU's Variable Parameter list reference: 
	https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Variable-Number-of-Arguments.html
	
	we just use a va_list type variable, and then increment it to get new arguments
	

2. scanf(const char *format, ...);

*/

#ifndef BULBASAUR_H
#define BULBASAUR_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdarg.h>

void bulbaPrintf(const char *text, ...);
void _printfFloat(float value);
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
			int value = va_arg(pointer, int);
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


void _printfFloat(float value) {
	if (value < 0) {
		write(1, "-", 1);
		value = -value;
	}
	
	int int_value = (int)value;
	float frac_value = value - int_value;
	
	_printfInt(int_value);
	write(1, ".", 1);

	// supporting just 2 decimal places for now
	for(int i = 0; i < 2; i++) {
		frac_value *= 10;
		int digit = (int)frac_value;
		char c = '0' + digit;
		write(1, &c, 1);
		frac_value -= digit;	
	}
}

void _printfInt(int value) {
		char buffer[32];
		if (value == 0) {
			write(1, 0, 1);
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