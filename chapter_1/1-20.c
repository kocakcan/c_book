#include <stdio.h>
#define MAXLINE 1000

int _getline(char s[], int lim);
void copy(char to[], char from[]);

int main() {
  char curr[MAXLINE];
  char output[MAXLINE];
  int len;

  while ((len = _getline(curr, MAXLINE)) > 0) {
    copy(output, curr);
  }

  printf("%s", output);

  return 0;
}

int _getline(char s[], int lim) {
  int i, c;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    if (c == '\t') {
      s[i] = ' ';
      ++i;
      s[i] = ' ';
    } else {
      s[i] = c;
    }
  }

  if (c == '\n') {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';
  return i;
}

void copy(char to[], char from[]) {
  int i = 0;

  while ((to[i] = from[i]) != '\0')
    ++i;
}
