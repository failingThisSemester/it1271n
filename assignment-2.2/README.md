# Custom Minimal Standard I/O Library Implementation

## Problem Statement

1. Write a C program that imitates the functions provided by `<stdio.h>`. You should have
separate functions similar to `getc`, `putc`, `scanf`, `printf`, `fscanf`, `fprintf`, etc. with options for variable type of arguments as input.

2. Update your customized header (.h) file created in Assignment 2 to include these system
headers, global constants (if any) and function prototypes that you will be using
throughout the semester.

## Thought Process

The scope of the problem is quite big, first step is to reduce that. Implementing `printf()` and `scanf()` seems to be the most optimal thing to do for now

### `printf()`

[man page](https://man7.org/linux/man-pages/man3/printf.3.html)

prototype: `printf(const char *format, ...);`

The original `printf()` can be used like 

```c
int apples = 67;
int oranges = 9;
printf("I have %d apples and %d oranges.", apples, oranges);
```
We can pass as many arguments as we want. Unnecessary complexity for now. Let's scope it down even further.

We will implement only `printf(const char *text, int value)`. Only one single `int` value.

How can I approach this?

It smells as if, we need to parse the orignal string and do evaluate some if-else conditions.

How about taking 2 characters like "I ", " h", "ha", "av" etc. to detect the "%d"? Seems doable.

Once we detect that, we can then pass the integer value to be printed.
Maybe, maybe, capture individual digits and writing their char representations? 

```c
void bulbaPrintf(const char *text, int value) {
	while(*text) {
		if (*text == '%' && *(text + 1) == 'd') {
            // integer value handler
			_printfInt(value);
			text += 2;
			continue;
		}
		write(1, text++, 1);
	}
}
```

and then quite obviously we can write,

```c
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
```
the code is self explanatory.

Now, 

```c
#define CARROTS 12
// .. other code ..
bulbaPrintf("I have eaten %d carrots\n", CARROTS);
```
Successfully prints "I have eaten 12 carrots".

Now we may think of adding support for variable number of arguments.

[GNU's Variable Parameter List Reference](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Variable-Number-of-Arguments.html) states the use of `va_list`.

Our current `_printfInt()` function currently looks like this:

```c
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
```

In order to make it accept we modify it in this way:

```c
void bulbaPrintf(const char *text, ...) {
    // we have an ellipsis in the method signature

    // va_list is a special pointer type, we can imagine it like a bookmark maybe?
	va_list pointer;

    // this tells the pointer to bookmark the first '...' argument
    // the reference says that 'a variadic function must specify at
    // least one fixed argument with an explicitly declared data type.'

    // the pointer starts right after where 'text' ends
	va_start(pointer, text);
	
	while(*text) {
		if (*text == '%' && *(text + 1) == 'd') {

            // we fetch the next time as an integer
            // this both returns the value AND moves the bookmarking pointer forward
            // that's it.
			int value = va_arg(pointer, int);

			_printfInt(value);
			text += 2;
			continue;
		}

		write(1, text++, 1);
	}
}
```

and now.. we got support for:

```c
#define CARROTS 12
#define POTATOES 13
bulbaPrintf("Carrots: %d, Potatoes: %d\n", CARROTS, POTATOES);
```
> [!NOTE]
> Earlier I used `write(1, 0, 1);` in `_printfInt()` function. The compiler warned about it. When value == 0, we are passing the literal 0 (`NULL`) as the buffer address. Rather we need to pass the address of a character, using `write(1, "0", 1);`.

Implementing support float is pretty trivial. Just a if-else pass in the `bulbaPrintf()` function, to forward the workload to `_printfFloat()` function.

Initial implementation:

```c
void bulbaPrintf(const char *text, ...) {
	va_list pointer;
	va_start(pointer, text);
	
	// other code 
		else if (*text == '%' && *(text + 1) == 'f') {
			int value = va_arg(pointer, int);
			_printfFloat(value);
			text += 2;
			continue;
		}
    // other code
}

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
```

But this gives weird results when used as:

```c
#define WATER 1.23
bulbaPrintf("I drank %f litres of water\n", WATER);

// output:
// I drank 1855864960.00 litres of water
```

After digging into the reference manual, I found that:

In C, when passing arguments to a variadic function, `float` is automatically promoted to `double`. Even if you want a float back, `va_arg` must be told to look for a double. 

So essentially, we were facing a type mismatch error. Because an `int` is typically 4 bytes and a double is 8, `va_arg` grabbed the first 4 bytes of the floating point bit pattern and interpreted them as a raw integer. This resulting integer was then passed to `_printfFloat()`, which treated that garbled integer as the new _whole number_ part, leading to some weird stuff.

That was easily fixed by:

```c
int value = va_arg(pointer, int); // old
double value = va_arg(pointer, double); // new
```

and

```c
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
```
This fixes the problem.

Now when we try to print something like:

```c
#define WATER 1.12
// other code
bulbaPrintf("I drank %f litres of water\n", WATER);
```

We get an output of 

```bash
I drank 1.12 litres of water
```

But again, something like
```c
#define WATER 1.22
// other code
bulbaPrintf("I drank %f litres of water\n", WATER);
```

outputs:

```bash
I drank 1.21 litres of water
```

Well, turns out its the floating point precision problem. 

Refer to [IEE 754](https://en.wikipedia.org/wiki/IEEE_754) specifications.