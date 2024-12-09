/*
 *   Write a program to "fold" long input lines into two or more shorter lines
 *   after the last non-blank character that occurs before n-th column of input.
 *   Make sure your program does something intelligent with very long lines, and
 *   if there are no blanks or tabs before the specified column.
 */
#include <stdio.h>
#define MAXLINE 1000

int _getline(char s[], int lim);
void copy(char to[], char from[]);

int main() {
  char curr[MAXLINE];
  char line[MAXLINE];
  int len, max = 0;

  while ((len = _getline(curr, MAXLINE)) > 0) {
    if (len >= max) {
      max = len;
      copy(line, curr);
    }
  }

  if (max > 0) {
    printf("%s\n", line);
  }

  return 0;
}

int _getline(char s[], int lim) {
  int i, c;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n') {
    s[i] = c;
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
