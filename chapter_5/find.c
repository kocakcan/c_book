/***
 * Following the lead of the UNIX program grep, let us enhance the
 * pattern-finding program so the pattern to be matched is specified by the
 * first argument on the command line.
 */
// #include <stdio.h>
// #include <string.h>
// #define MAXLINE 1000
//
// int getline_(char *line, int max) {
//   int i, c;
//
//   i = 0;
//   while (--max > 0 && (c = getchar()) != EOF && c != '\n') {
//     *line++ = c;
//     i++;
//   }
//
//   if (c == '\n') {
//     *line++ = c;
//     i++;
//   }
//
//   *line = '\0';
//   return i;
// }
//
// char *strindex_(char *s, char *t) {
//   char *ps, *pt;
//
//   for (; *s; s++) {
//     for (ps = s, pt = t; *pt && *ps == *pt; ps++, pt++)
//       ;
//     if (pt > t && *pt == '\0')
//       return s;
//   }
//   return NULL;
// }

/* find: print lines that match pattern from 1st arg */
// int main(int argc, char *argv[]) {
//   char line[MAXLINE];
//   int found = 0;
//
//   if (argc != 2)
//     printf("Usage: find pattern\n");
//   else
//     while (getline_(line, MAXLINE) > 0)
//       if (strindex_(line, argv[1]) != NULL) {
//         printf("%s", line);
//         found++;
//       }
//   return found;
// }

/***
 * The standard library function strstr(s, t) returns a pointer to the first
 * occurrence of the string t in the string s, or NULL if there is none. It is
 * declared in <string.h>
 *
 * The model can now be elaborated to illustrate further pointer constructions.
 * Suppose we want to allow two optional arguments. One says "print all lines except those that match the pattern;" the second says "precede each printed line by its line number."
 *
 * A common convention for C programs on UNIX systems is that an argument that begins with a minus sign introduces an optional flag or parameter. If we choose -x (for "except") to signal the inversion, and -n ("number") to request line numbering, then the command
 *
 * 	find -x -npattern
 * will print each line that doesn't match the pattern, preceded by its line number.
 *
 * Optional arguments should be permitted in any order, and the rest of the program should be independent of the number of arguments that we present. Furthermore, it is convenient for users if option arguments can be combined, as in
 *
 * 	find -nx pattern
 * Here is the program:
 */
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline_(char *s, int lim) {
	int i, c;

	i = 0;
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

/* find: print line that match pattern from 1st arg */
int main(int argc, char *argv[]) {
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		// while ((c = *++argv[0]) != '\0')
		while (c = *++argv[0])	/* check the next char */
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("find: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}
	if (argc != 1)
		printf("Usage: find -x -n pattern\n");
	else
		while (getline_(line, MAXLINE) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}
	return found;
}

/***
 * argc is decremented and argv is incremented before each optional argument. At the end of the loop, if there are no errors, argc tells how many arguments remain unprocessed and argv points to the first of these. Thus argc should be 1 and *argv should point at the pattern. Notice that *++argv is a pointer to an argument string, so (*++argv)[0] is its first character. (An alternate valid form would be **++argv.) Because [] binds tighter than * and ++, the parantheses are necessary; without them the expression would be taken as *++(argv[0]). In fact, that is what we have used in the inner loop, the expression *++argv[0] increments the pointer argv[0]!
 *
 * It is rare than one uses pointer expressions more complicated than these; in such cases, breaking them into two or three steps will be more intuitive.
 */
