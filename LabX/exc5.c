#include <stdio.h>

int add(int *num1, int *num2, int *num3);

int main() {
	int x = 1; int y = 2; int z = 3;
	printf("%d\n", add(&x, &y, &z));
}

int add(int *num1, int *num2, int *num3) {
	return *num1 + *num2 + *num3;
}
