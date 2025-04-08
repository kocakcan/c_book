#include <stdio.h>

void expand(char s1[], char s2[]);

int main() {
	char s1[] = "-a-zA-Z0-9HELLO-";
	char s2[100];

	expand(s1, s2);
	printf("Going to expand %s\n", s1);
	printf("%s\n", s2);

	return 0;
}

void expand(char s1[], char s2[]) {
	int i = 0;	// Index into s1
	int j = 0;	// Index into s2
	char c;		// Current character read

	while ((c = s1[i]) != '\0') {
		if (s1[i + 1] == '-' && s1[i + 2] >= c) {
			// Move i to the larger character
			i = i + 2;	

			while (c <= s1[i]) {
				s2[j] = c;
				c++;		// Update c C++ rocks!
				j++;		// Update j
			}
		} else {
			// Read into s2 the current character
			s2[j] = c;
			j++;			// Update j
		}
	i++;
	}

	s2[j] = '\0';
}
