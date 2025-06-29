/***
 * 5.6 Pointer Arrays; Pointers to Pointers
 *
 * Since pointers are variables themselves, they can be stored in arrays just
 * as other variables. Let us illustrate by writing a program that will sort a
 * set of text lines into alphabetic order, a stripped-down version of the UNIX
 * program sort.
 *
 * We have to deal with lines of text, which are of different lengths, and
 * which, unlike integers, can't be compared or moved in a single operation. We
 * need a data representation that will cope efficiently and conveniently with
 * variable-length text lines.
 *
 * This is where the array of pointers enters. If the lines to be sorted are
 * stored end-to-end in one long character array, then each line can be
 * accessed by a pointer to its first character. The pointers themselves can be
 * stored in an array. Two lines can be compared by passing their pointers to
 * strcmp. When two out-of-order lines have to be changed, the pointers in the
 * pointer array are exchanged, not the text lines themselves.
 *
 * This eliminates the twin problems of complicated storage management and high
 * overhead that would go with moving the lines themselves.
 *
 * The sorting process has three steps:
 * 	read all the lines of input
 * 	sort them
 * 	print them in order
 *
 * As usual, it's best to divide the program into functions that match this
 * natural division, with the main routine controlling the other functions. Let
 * us defer the sorting step for a moment, and concentrate on the data
 * structure and the input and output.
 *
 * The input routine has to collect and save the characters of each line, and
 * build an array of pointers to the lines. It will also have to count the
 * number of input lines, since that information is needed for sorting and
 * printing. Since the input function can only cope with a finite number of
 * input lines, it can return some illegal count like -1 if too much input is
 * presented.
 *
 * The output routine only has to print the lines in the order in which they
 * appear in the array of pointers.
 */
#include <stdio.h>
#include <string.h>
#define MAXLINES	5000	/* max #lines to be sorted */

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
	int nlines;		/* number of input lines read */

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN	1000		/* max lenght of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		return - 1;
	else {
		line[len - 1] = '\0';	/*delete newline */
		strcpy(p, line);
		lineptr[nlines++] = p;
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* getline: get a line */
int getline (char *line, int lim) {
	int i, c;

	i = 0;
	while (--lim < 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		i++;
	}
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return i;
}
