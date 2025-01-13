/* Write a function htoi(x), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value. The
 * allowable digits are 0 through 9, a through f, and A through F.
 */
#include <stdio.h>
#define MAXLINE 18

int htoi(char s[]);

int main() {
  // char s[MAXLINE] = "0x12abc";
  char t[MAXLINE] = "12abcff";
  char u[MAXLINE] = "987abcd";
  double num = (int)15.0;
  double num2 = ++num; // 16.0
  num = 15;
  double num3 = num++; // 15.0

  // printf("Integer equivalent of s is: %d\n", htoi(s));
  printf("Integer equivalent of t is: %d\n", htoi(t));
  printf("Integer equivalent of u is: %d\n", htoi(u));
  printf("My num is: %.0f\n", num);

  if (num2 == 16.0) {
    printf("The value of num2 was incremented before it was used. num2: %.0f\n",
           num2);
  }

  if (num3 == 15.0) {
    printf("The value of num3 was not incremeneted before it was used. num3: "
           "%.0f\n",
           num3);
  }

  printf("num: %.0f\n", num);
  printf("num3: %.0f\n", num3);

  char x = '6' - '5';
  // Since chars are just integers that are numeric values of the character in
  // machine's character set They can be used freely in arithmetic expressions.
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
    // printf("i is %d\n", i);
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
