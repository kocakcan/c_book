/* Rewrite the prefix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number conversion/ */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0' /* signal that a number was found */
#define MAXOP 100

static double val[MAXOP];
static double *sp = val;

void push(double);
double pop(void);

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

/* getop: get next operator or numeric operand using scanf */
int getop(char *s) {
  int c;

  /* Skip spaces and tabs */
  while ((c = getchar()) == ' ' || c == '\t')
    ;

  /* Store first character */
  s[0] = c;
  s[1] = '\0';

  /* If not a digit or '.', it's an operator or newline or EOF */
  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  /* Could be negative number */
  int i = 0;
  if (c == '-') {
    int next = getchar();
    if (!isdigit(next) && next != '.') {
      /* Just a minus operator */
      if (next != EOF)
        ungetc(next, stdin);
      return c;
    }
    s[++i] = next;
    c = next;
  }

  /* Collect integer part */
  if (isdigit(c))
    while (isdigit(s[++i] = c = getchar()))
      ;

  /* Collect decimal part */
  if (c == '.')
    while (isdigit(s[++i] = c = getchar()))
      ;

  s[i] = '\0';

  if (c != EOF)
    ungetc(c, stdin);

  return NUMBER;
}

void push(double f) {
  if (sp - val < MAXOP)
    *sp++ = f;
  else
    printf("error: stack full, can't push\n");
}

double pop(void) {

  if (sp - val > 0)
    return *--sp;
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}
