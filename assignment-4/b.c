// gcc b.c -o main -lm && ./main

/* 
main -> binary -> 
ELF format -> .text, stack
.text section:
in usual cases: call 0x1234fedf is the ASM for function calling

now, when using function pointers
we store the address of the function's instructions in a stack of virtual memory
now, we move that address from the stack to the RAX register, and then call it

so its indirect invocation as opposed to direct invocation
*/

#include <stdio.h>

double add(double a, double b){return a + b;}
double sub(double a, double b){return a - b;}
double mult(double a, double b){return a * b;} 
double pow(double a, double b){return pow(a, b);}

int main()
{
	double (*ops[])(double, double) = {add, sub, mult, pow};

	int choice; double a, b;
	printf("Enter <add=0, sub=1, mult=2, pow=3> <a> <b>: ");
	scanf("%d %lf %lf", &choice, &a, &b);
	printf("\nResult: %lf\n", ops[choice](a, b));
	return 0;
}