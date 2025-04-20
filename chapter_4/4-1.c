/* Write the function strindex(s, t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none. */
#include <stdio.h>
#include <string.h>
#define MAXLINE	1000

/* strindex: return index of the rightmost occurrence of t in s, -1 if none */
int strindex(char s[], char t[]);
int getline_(char s[], int lim);

char pattern[] = "lo";

int main() {
	char line[MAXLINE];
	int found = 0;

	while (getline_(line, MAXLINE) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	return found;
}

int strindex(char s[], char t[]) {
	int i, j, k;

	for (i = strlen(s) - 1; i >= 0; i--) {
		for (j = i, k = strlen(t) - 1; j >= 0 && s[j] == t[k]; j--, k--)
			;
		if (k < 0)
			return j + 1;
	}
	return -1;
}

int getline_(char s[], int lim) {
	int i, c;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';
	return i;
}
