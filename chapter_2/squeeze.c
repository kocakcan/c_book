#include "header.h"
#include <stdio.h>

enum bool { NO, YES };

/* squeeze: delete all c from s */
void squeeze(char s[], int c);

/* squeeze_: delete all matching chars in s2 from s1 */
void squeeze_(char s1[], char s2[]);

/* strcat: concatenate t to the end of s; s must be big enough */
void strcat_(char s[], char t[]);

/* any: find first location in s1 where s2 occurs; return -1 if not found */
int any(char s1[], char s2[]);

int main() {
  int my_bool = NO;
  enum bool bool_var = 5;
  printf("The value of bool_var is: %d\n", bool_var);
  printf("Sekiro is an amazing game mate\n");
  int flag = nil;

  // The bitwise AND operator & is often used to mask off some set of bits
  // Below sets to zero but the low-order 7 bits of n.
  // (7 * 1) + (7 * 8) + (1 * 64) = 7 + 56 + 64 = 127
  // 01111111 = 0177 (octal) = 127 (decimal)

  int n = 255;

  printf("n is %d\n", n);
  n = n & 0177;
  printf("n is %d after masking\n", n);

  // The bitwise inclusive OR operator | is used to turn bits on
  // Turning on = Making it 1
  // Makes it 1 if at least one of the operand is 1
  // If both is 0 then it's 0
  int x = 304 >> 2;
  // 00001000
  int z = 8;

  // 00001111
  int q = 15;

  // 00001000
  // 00001010
  int y = 10 | z;

  // 00001111
  // 00001010
  // 00000101 -> 5
  // The bitwise exclusive OR ^ sets a one in each bit position where its
  // operands have different bits, and zero where they are the same.
  int u = 10 ^ q;
  // 00000001
  // 00000010
  // 00000000
  printf("n is %d\n", n);
  printf("x is %d\n", x);
  printf("y is %d\n", y); // 10
  printf("u is %d\n", u); // 5

  if (!flag)
    printf("This is the worst TV show ever mate.\n");

  char name[] = "can";
  char buffer[] = "ali";

  printf("Here's my name before: %s\n", name);
  squeeze_(name, buffer);
  printf("Here's my name after: %s\n", name);

  char boss[] = "Mert Can";
  char mini_boss[] = "Can";
  printf("This should be equal to 5 = %d\n", any(boss, mini_boss));

  // We can define arrays larger than our original string
  // Rest of the characters would be initialized to null character
  // But that doesn't mean that our string is also larger than it should be
  // as only the first null character matter when it comes to finding the
  // length of the string
  // char s[] = {'\0', '\0', '\0', '\0', '\0', '\0'};
  // char s[6] is different though as it has no initializer it contains garbage
  // values.
  char s[6] = {};
  char t[] = "Kocak";

  strcat_(s, t);
  printf("Here's my surname: %s\n", s);

  int bit = 16 << 2;
  printf("bit is: %d\n", bit);

  return 0;
}

void squeeze(char s[], int c) {
  int i, j;

  for (int i = j = 0; s[i] != '\0'; ++i) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

void strcat_(char s[], char t[]) {
  int i = 0, j = 0;

  while (s[i] != '\0')
    ++i;

  while ((s[i++] = t[j++]) != '\0')
    ;
}

void squeeze_(char s1[], char s2[]) {
  int i, j, k = 0;

  for (i = 0; s1[i] != '\0'; ++i) {
    for (j = 0; s2[j] != '\0'; ++j) {
      if (s1[i] == s2[j]) {
        // We have a match
        break;
      }
    }

    // If for loop has been completed and s2[j] is null terminator
    // Or we finished checking s2 and found no matches
    if (s2[j] == '\0') {
      // Copy current character if it's not in s2
      s1[k++] = s1[i];
    }
  }

  s1[k] = '\0';
}

int any(char s1[], char s2[]) {
  int i, j;

  for (i = 0; s1[i] != '\0'; ++i) {
    for (j = 0; s2[j] != '\0'; ++j) {
      if (s1[i] == s2[j]) {
        return i;
      }
    }

    // if (s2[j] == '\0') {
    //   return -1;
    // }
  }

  if (s1[i] != '\0') {
    return -1;
  }

  return -1;
}
