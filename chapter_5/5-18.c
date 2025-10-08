#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define BUFSIZE 100
enum { NAME, PARENS, BRACKETS };

static char buf[BUFSIZE];
static char *bufp = buf;

int dcl(void);
int dirdcl(void);

int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* identifier name */
char out[1000];

int getch(void);
void ungetch(int);

void skip_to_newline(void) {
  int c;
  while ((c = getch()) != '\n' && c != EOF)
    ;
}

/* convert declaration to words */
int main(void) {
  int error;

  while (gettoken() != EOF) { /* 1st token on line */
    strcpy(datatype, token);  /* is the datatype */
    out[0] = '\0';
    error = dcl(); /* parse rest of line */
    if (error || tokentype != '\n') {
      printf("syntax error: invalid declaration, skipping to next line.\n");
      skip_to_newline();
    } else
      printf("%s: %s %s\n", name, out, datatype);
  }

  return 0;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void) {
  int type;

  if (tokentype == '(') {
    if (dcl()) {
      printf("error: invalid declaration inside paranthesis\n");
      return 1;
    }

    if (tokentype != ')') {
      printf("error: missing )\n");
      return 1;
    }
  } else if (tokentype == NAME) { /* variable name */
    strcpy(name, token);

  } else {
    printf("error: expected name or (dcl)\n");
    return 1;
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }

  return 0;
}

/* dcl: parse a declarator */
int dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';)
    ns++;

  if (dirdcl())
    return 1;
  while (ns-- > 0)
    strcat(out, " pointer to");

  return 0;
}

int gettoken(void) { /* return next token */
  int c;
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;

  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      if (*(p - 1) == '\n' || *(p - 1) == EOF) {
        printf("error: missing ]\n");
        break;
      }
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

int getch(void) { return (bufp - buf > 0) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (bufp - buf >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = c;
}
