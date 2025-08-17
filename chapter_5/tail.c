/* Write the program tail, which prints the last n lines of its input. By
 * default, n is set to 10, let us say, but it can be changed by an optional
 * argument so that
 *
 *   tail -n
 * prints the last n lines. The program should behave rationally no matter
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program, not in a two-dimensional array of fixed size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_NUMBER 10
#define MAXLINES 1000
#define MAXLEN 1000

char *input[MAXLINES];
char **ip = input;

int getline_(char *s, int lim) {
  int c, i = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *s++ = c;
    i++;
  }

  if (c == '\n') {
    *s++ = c;
    i++;
  }

  *s = '\0';
  return i;
}

void writelines(char **input, size_t nlines) {
  while (nlines--)
    // printf("%s", *input++);
    fputs(*input++, stdout);
}

int readlines(char **input, int maxlines) {
  int len;
  char line[MAXLEN];

  while ((len = getline_(line, MAXLEN)) > 0) {
	// if (nlines >= maxlines)
	if (ip - input >= maxlines)
		return -1;

	char *p = malloc(len + 1);
	if (!p) return -1;
	strcpy(p, line);
	*ip++ = p;
  }

  return ip - input;
}

/* main: tail without circular buffer, which is fine for practice */
int main(int argc, char *argv[]) {
  int n = DEFAULT_NUMBER, nlines;

  if (--argc > 0 && (*++argv)[0] == '-')
    n = atoi(*(argv) + 1);

  if (n <= 0) n = DEFAULT_NUMBER;

  if ((nlines = readlines(input, MAXLINES)) >= 0) {
	if (n > nlines) n = nlines;
	writelines(input + (nlines - n), n);

	// for (size_t i = 0; i < nlines; i++)
		// free(input[i]);

	for (char **temp = input; temp < ip; ++temp)
		free(*(input + (temp - input)));
		// which is equivalent to free(*temp) 😅

	return 0;
  } else {
	printf("error: input too big to store\n");
	return 1;
  }
}
