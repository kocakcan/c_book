/* Write a routine ungets(s) that will push back an entire string onto the
* input. Should ungets know about buf and bufp, or should it just use ungetch?
* */
#include <stdio.h>
#include <string.h>
#define MAXLEN  1000
#define BUFSIZE 1000

int gets(char s[], int lim);
void ungets(char s[]);

int main(void) {
  char line[MAXLEN];
  char temp[MAXLEN];

  gets(line, MAXLEN);
  printf("%s", line);

  ungets(line);

  gets(temp, MAXLEN);
  printf("%s", temp);
}

int getch(void);
void ungetch(int c);

/* gets: basically getline */
int gets(char s[], int lim) {
  int i = 0, c;

  while (--lim > 0 && (c = getch()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

void ungets(char s[]) {
  int i = strlen(s);

  while (i)
    ungetch(s[--i]);
}

int bufp = 0;
char buf[BUFSIZE];

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
/* ungets functions doesn't need access to buf and bufp. It is enough for it to
* use the ungetch() */
