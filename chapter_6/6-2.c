/***
 * Write a program that reads a C program and prints in alphabetical order each
 * group of variable names that are identical in the first 6 characters, but
 * different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */
#include <stdio.h>

int strcmp_(const char *, const char *);

int main(int argc, char *argv[]) {
  // while (argc--)
  //   printf("%s\n", *argv++);

  // if ((*++argv)[0] == '-') {
  //   char *s = *argv;
  //   printf("Result: %s\n", s + 1);
  // }

  // if ((*argv++)[0] == '.') {
  //   printf("Result: %s\n", *argv);
  // }

  // if ((*++argv)[0] == '-')
  //   printf("Result: %d\n", *++argv[0] - '0');

  // if ((*++argv)[0] == '-') {
  //   // char *flag = *argv;
  //   if (strcmp_((*argv) + 1, "help") == 0)
  //     printf("You played us like a damn fiddle\n");
  // }

  int verbose = 0, force = 0;
  int c;

  while (--argc > 0 && (*++argv)[0] == '-')
    while (c = *++argv[0])
      switch (c) {
      case 'v':
        verbose = 1;
        break;
      case 'f':
        force = 1;
        break;
      default:
        printf("unknown flag %c\n", **argv);
      }

  printf("verbose: %d | force: %d\n", verbose, force);

  return 0;
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t) {
    if (*s == '\0')
      return 0;
    s++, t++;
  }

  return (unsigned char)*s - (unsigned char)*t;
}
