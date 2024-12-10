#include <stdio.h>
#define MAXLINE 1000

int _getline(char s[], int lim);
void reverse(char s[]);
void copy(char to[], char from[]);

int main() {
  char curr[MAXLINE];
  char line[MAXLINE];
  int len = 0, size = 0;

  while ((len = _getline(curr, MAXLINE)) > 0) {
    copy(line, curr);
    ++size;
  }

  // Print the line in reverse
  if (size > 0) {
    reverse(line);
  }

  return 0;
}

int _getline(char s[], int lim) {
  int i, c;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n') {
    // s[i] = c;
    ++i;
  }

  // Null terminator is not taken into account when length is computed
  // as it is only there to mark the end
  s[i] = '\0';
  return i;
}

void copy(char to[], char from[]) {
  int i = 0;

  while ((to[i] = from[i]) != '\0')
    ++i;
}

void reverse(char s[]) {
  int i = 0;

  while (s[i] != '\0') {
    ++i;
  }

  for (int j = i; j >= 0; --j) {
    putchar(s[j]);
  }

  putchar('\n');
}
