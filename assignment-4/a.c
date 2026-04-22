#include <stdio.h>

float power_f(float a, int b);
int power_i(int a, int b);

#define power(a, b) _Generic ((a), int: power_i, float: power_f, default: power_f)(a, b)

int main()
{ 	
	int t;
	printf("Enter the type of 'a' (float=0, int=1): ");
	scanf("%d", &t);

	printf("Enter the values [a] [b]: ");
	if (t == 0) {
		float a; int b;
		scanf("%f %d", &a, &b);
		printf("ans: %f\n", power(a, b));
	}
	else {
		int a; int b;
		scanf("%d %d", &a, &b);
		printf("ans: %d\n", power(a, b));
	}
	return 0;
}

float power_f(float a, int b) {
	if (b == 0) return 1;
	if (b < 0) return 1 / power_f(a, -b);
	if (b%2 == 0) {
		float half = power_f(a, b/2);
		return half * half;
	}
	return a * power_f(a, b - 1);
}

int power_i(int a, int b) {
	if (b == 0) return 1;
	if (b < 0) return 1 / power_i(a, -b);
	if (b%2 == 0) {
		int half = power_i(a, b/2);
		return half * half;
	}
	return a * power_i(a, b - 1);
}