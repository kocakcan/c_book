#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000

int getline_(char *s, int lim) {
	int c, i = 0;
	
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c, i++;

	if (c == '\n')
		*s++ = c, i++;
	*s = '\0';
	return i;
}

int main(void) {
	char s[MAXLEN];
	int length, num;

	printf("Enter a number: ");

	if ((length = getline_(s, MAXLEN)) > 0)
		num = atoi(s);

	if (num == 0) {
		printf("You haven't provided a valid number matey!\n");
		return 1;
	}

	for (int i = 1; i <= num; i++) {
		for (int j = i; j < num; j++)
			printf(" ");
		for (int k = 1; k <= i; k++)
			printf("%d", k);
		for (int l = i - 1; l >= 1; l--)
			printf("%d", l);
		printf("\n");
	}

	return 0;
}
