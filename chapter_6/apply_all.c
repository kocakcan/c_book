#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define printa(arr, size) 			\
	printf("["); 				\
	for (size_t i = 0; i < size; i++) {	\
		if (i == size - 1)		\
			printf("%d", arr[i]);	\
		else				\
			printf("%d, ", arr[i]);	\
	}					\
	printf("]\n");				\


void apply_all(int *, int, int (*)(int *));
int multiply(int *);

int main(void) {
	srand(time(NULL));
	int nums[SIZE];

	for (size_t i = 0; i < SIZE; i++)
		nums[i] = rand() % 100;
	printa(nums, SIZE);
	apply_all(nums, SIZE, multiply);
	printa(nums, SIZE);
	return 0;
}

void apply_all(int *v, int n, int (*f)(int *)) {
	for (int *temp = v; temp - v < n; temp++)
		v[temp - v] = (*f)(&v[temp - v]);
}

int multiply(int *x) {
	return *x * 2;
}
