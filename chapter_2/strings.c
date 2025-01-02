#include <stdio.h>

/*strlen: return length of s */
int _strlen(char s[]);

// enum is a list of constant integer values.
// the first name in an enum has value 0, the next 1, and so on, unless
// explicit values are specified.
enum boolean { NO, YES };

// If not all values are specified, unspecified values continue the progression
// from the last specified value.
enum escapes {
  BELL = '\a',
  BACKSPACE = '\b',
  TAB = '\t',
  NEWLINE = '\n',
  VTAB = '\v',
  RETURN = '\r'
};

/* FEB = 2, MAR = 3, etc. */
enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

int strlen_(const char s[]);

int main() {
  char *str = "This is a string";
  int x = JAN;
  int y = FEB;

  printf("%s\n", str);
  printf("There are %d characters in the string above\n", _strlen(str));
  printf("This should be equal to 1 = %d\n", x);
  printf("This should be equal to 2 = %d\n", y);

  char *const name = "Can";
  const char *surname = "Kocak";

  printf("My name, %s, is %d characters long.\n", name, strlen_(name));
  printf("My surname, %s, is %d characters long.\n", surname, strlen_(surname));

  return 0;
}

int _strlen(char s[]) {
  int i = 0;

  while (s[i] != '\0')
    ++i;

  return i;
}

int strlen_(const char s[]) {
  int i = 0;

  while (s[i] != '\0')
    ++i;

  return i;
}
