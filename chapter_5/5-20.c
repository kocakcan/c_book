/* Expand dcl to handle declarations with function argument types, qualifiers
 * like const, and so on. */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define BUFSIZE 100
enum { NAME, PARENS, BRACKETS };

static char buf[BUFSIZE];
static char *bufp = buf;

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char qualifier[MAXTOKEN]; /* qualifier = const, static, etc. */
char out[1000];

/* isqualifier: simple check for qualifiers */
int isqualifier(char *s) {
	return strcmp(s, "const") == 0 ||
		strcmp(s, "static") == 0 ||
		strcmp(s, "volatile") == 0;
}

/* convert declaration to words */
int main(void) {
  int len;
  qualifier[0] = '\0';

  while (gettoken() != EOF) { /* 1st token on line */
    qualifier[0] = '\0';
    /* accumulate qualifiers before datatype */
    while (tokentype == NAME && isqualifier(token)) {
	if (qualifier[0])
		strcat(qualifier, " ");
	strcat(qualifier, token);
	gettoken();
    }
    /* next token should be datatype */
    if (tokentype == NAME)
	strcpy(datatype, token);
    else {
	printf("error: expected data type\n");
	continue;
    }
    out[0] = '\0';
    dcl(); /* parse rest of line */
    if (tokentype != '\n')
      printf("syntax error\n");
    printf("%s: %s %s %s\n", name, out, qualifier[0] ? qualifier : "", datatype);
  }
  return 0;
}

/* parsearg: parse a single argument, storing in out */
void parsearg(char *argout) {
	char argqual[MAXTOKEN], argtype[MAXTOKEN], argname[MAXTOKEN];
	argqual[0] = argtype[0] = argname[0] = '\0';

	/* accumulate qualifiers */
	while (gettoken() == NAME && isqualifier(token)) {
		if (argqual[0])
			strcat(argqual, " ");
		strcat(argqual, token);
	}
	/* type */
	if (tokentype == NAME) {
		strcpy(argtype, token);
		gettoken();
	}
	/* pointer */
	int ns = 0;
	while (tokentype == '*') {
		ns++;
		gettoken();
	}
	/* name */
	if (tokentype == NAME) {
		strcpy(argname, token);
		gettoken();
	}
	/*compose argument description */
	argout[0] = '\0';
	if (argname[0])
		sprintf(argout, "%s%s%s %s%s",
			argqual[0] ? argqual : "",
			argqual[0] ? " " : "",
			argtype,
			ns > 0 ? "pointer to " : "",
			argname);
	else
		sprintf(argout, "%s%s%s",
			argqual[0] ? argqual : "",
			argqual[0] ? " " : "",
			argtype);
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
  int type;

  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      printf("error: missing )\n");
  } else if (tokentype == NAME) /* variable name */ {
    strcpy(name, token);
  } else
    printf("error: expected name or (dcl)\n");
  while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
    if (type == PARENS)
      strcat(out, " function returning");
    else if (type == BRACKETS) {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    } else if (type == '(') {
	strcat(out, " function expecting (");
	int first = 1;
	do {
		char argdesc[300];
		parsearg(argdesc);
		if (!first)
			strcat(out, ", ");
		first = 0;
		strcat(out, argdesc);
	} while (tokentype == ',');
	if (tokentype != ')')
		printf("error: missing ) in argument list\n");
	strcat(out, ") and returning");
	gettoken();	/* eat next token after arg list */
   }
  }
}

/* dcl: parse a declarator */
void dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

int gettoken(void) { /* return next token */
  int c, getch(void);
  void ungetch(int);
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
      ;
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
