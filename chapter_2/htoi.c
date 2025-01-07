/* Write a function htoi(x), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value. The
 * allowable digits are 0 through 9, a through f, and A through F.
 */
#include <stdio.h>
#define MAXLINE 18

int htoi(char s[]);

int main() {
  char s[MAXLINE] = "12abc";
  char t[MAXLINE] = "12abcff";

  printf("Integer equivalent of s is: %d\n", htoi(s));
  printf("Integer equivalent of t is: %d\n", htoi(t));

  char x = '6' - '5';
  // Since chars are just integers that are numeric values of the character in machine's character set
  // They can be used freely in arithmetic expressions.
  char y = 'F' - 55;

  printf("Result: %d\n", x);
  printf("Result: %d\n", y);

  return 0;
}

int htoi(char s[]) {
  // 0xF, 0XF, 0xA
  int i = 0, n = 0;

  // TODO: Add 0x/0X support
  // while (i < 2) {
  //   if (s[i] == 0) {
  //     ++i;
  //   } else if (s[i] == 'x' || s[i] == 'X') {
  //     ++i;
  //   } else {
  //     i = 2;
  //   }
  // }

  for (i = 0; i < MAXLINE && s[i] != '\0'; ++i) {
    if (s[i] >= '0' && s[i] <= '9') {
      n = 16 * n + s[i] - '0';
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      n = 16 * n + (s[i] - 55);
    } else if (s[i] >= 'a' && s[i] <= 'z') {
      n = 16 * n + (s[i] - 87);
    }
  }

  return n;
}
