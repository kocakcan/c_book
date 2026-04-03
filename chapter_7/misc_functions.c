/*
 * 7.8 Miscellaneous Functions
 *
 * The standard library provides a wide variety of functions.
 *
 * 7.8.1 String Operations
 *
 * In the following, s and t are char *'s and c and n are ints.
 *
 *  strcat(s, t)      concatenate t to end of s
 *  strncat(s, t, n)  concatenate n characters of t to end of s
 *  strcmp(s, t)      return negative, zero, or positive for s < t, s == t, s >
 * t strncmp(s, t, n)  same as strcmp but only in first n characters strcpy(s,
 * t)      copy t to s strncpy(s, t, n)  copy at most n characters of t to s
 *  strlen(s)         return length of s
 *  strchr(s, c)      return pointer to first c in s, or NULL if not present
 *  strrchr(s, c)     return pointer to last c in s, or NULL if not present
 *
 * 7.8.2 Character Class Testing and Conversion
 *
 * Several functions from <ctype.h> perform character tests and conversions. In
 * the following, c is an int that can be represented as an unsigned char or
 * EOF. The function returns int.
 *
 *  isalpha(c)  non-zero if c is alphabetic, 0 if not
 *  isupper(c)  non-zero if c is upper case, 0 if not
 *  islower(c)  non-zero if c is lower case, 0 if not
 *  isdigit(c)  non-zero if c is digit, 0 if not
 *  isalnum(c)  non-zero if isalpha(c) or isdigit(c), 0 if not
 *  isspace(c)  non-zero if c is blank, tab, newline, return, formfeed, vertical
 * tab toupper(c)  return c converted to upper case tolower(c)  return c
 * converted to lower case
 *
 * 7.8.3 Ungetc
 *
 * The standard library provides a rather restricted version of the function
 * ungetch; it is called ungetc.
 *
 *  int ungetc(int c, FILE *fp)
 * pushes the character c back onto file file, and returns either c, or EOF for
 * an error. Only one character of pushback is guaranteed per file. ungetc may
 * be used with any of the input functions like scanf, getc, or getchar.
 *
 * 7.8.4 Command Execution
 *
 * The function system(char *s) executes the command contained in the character
 * string s, then resumes executio of the current program. The contents of s
 * depend strongly on the local operating system. As a trivial example, on UNIX
 * systems, the statement
 *
 *  system("date");
 * causes the program date to be run; it prints the date and time of day on the
 * standard output. system returns a system-dependent integer status from the
 * command executed. In the UNIX system, the status return is the value returned
 * by exit.
 *
 * 7.8.5 Storage Management
 *
 * The functions malloc and calloc obtain blocks of memory dynamically.
 *
 *  void *malloc(size_t n)
 * returns a pointer to n bytes of uninitialized storage, or NULL if the request
 * cannot be satisfied.
 *
 *  void *calloc(size_t n, size_t size)
 * returns a pointer to enough free space for an array of n objects of the
 * specified size, or NULL if the request cannot be satisfied. The storage is
 * initialized to zero.
 *
 * The pointer returned by malloc or calloc has the proper alignment for the
 * object in question, but it must be cast into the appropriate type, as in
 *
 *  int *ip;
 *
 *  ip = (int *) calloc(n, sizeof(int));
 * free(p) frees the space pointed to by p, where p was originally obtained by a
 * call to malloc or calloc. There are no restrictions on the order in which
 * space is freed, but it is a ghastly error to free something not obtained by
 * calling malloc or calloc.
 *
 * It is also an error to use something after it has been freed. A typical but
 * incorrect piece of code is this loop that frees items from a list:
 *
 *  for (p = head; p != NULL; p = p->next)  -> WRONG
 * The right way is to save whatever is needed before freeing:
 *
 *  for (p = head; p != NULL; p = q) {
 *    q = p->next;
 *    free(p);
 *  }
 */
