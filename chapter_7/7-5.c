/* Rewrite the prefix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number conversion/ */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0' /* signal that a number was found */
#define MAXOP 100

extern void push(double);
extern double pop(void);

/* getop: get next operator or numeric operand */
int getop(char *);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      double op1 = pop();
      if ((int)op2 != 0)
        push((int)op1 % (int)op2);
      else
        printf("error: zero divisor for modulus\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
}

int getop(char *s) {
  int c, i, rc;
  static char lastc[] = " ";

  sscanf(lastc, "%c", &c);
  lastc[0] = ' '; /* clear last character */
  while ((s[0] = c) == ' ' || c == '\t')
    if (scanf("%c", &c) == EOF)
      c = EOF;
  s[i] = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  i = 0;
  if (isdigit(c)) /* collect integer part */
    do {
      rc = scanf("%c", &c);
      if (!isdigit(s[++i] = c))
        break;
    } while (rc != EOF);
  if (c == '.') /* collect fraction part */
    do {
      rc = scanf("%c", &c);
      if (!isdigit(s[++i] = c))
        break;
    } while (rc != EOF);
  s[i] = '\0';
  if (rc != EOF)
    lastc[0] = c;
  return NUMBER;
}
