/***
 * 5.5 Character Pointers and Functions
 *
 * A string contans, written as
 *
 *  "I am a string"
 * is an array of characters. In the internal representation, the array is
 * terminated with the null character '\0' so that programs can find the end.
 * The length in storage thus one more than the number of characters between
 * the double quotes.
 *
 * Perhaps the most common occurrence of string contants is an arguments to
 * functions, as in
 *
 *  printf("hello, world\n");
 * When a character string like this appears in a program, access to it is
 * through a character pointer; printf receives a pointer to the beginning of
 * the character array. That is, a string constant is accessed by a pointer to
 * its first element.
 *
 * String contants need not be function arguments. If pmessage is declared as
 *
 *  char *pmessage;
 * then the statement
 *
 *  pmessage = "now is the time";
 * assigns to pmessage a pointer to the character array. This is not a string
 * copy; only pointers are involved. C does not provide any operators for
 * processing an entire string of character as a unit.
 *
 * There is an important difference between these definitions:
 *
 *  char amessage[] = "now is the time";  -> an array
 *  char *pmessage = "now is the time";   -> a pointer
 * amessage is an array, just big enough to hold the sequence of characters
 * and '\0' that initializes it. Individual characters within the array may be
 * changed but amessage will always refer to the same storage. On the other
 * hand, pmessage is a pointer, initialized to point to a string constant; the
 * pointer may subsequently be modified to point elsewhere, but the result is
 * undefined if you try to modify the string contents.
 *
 * To illustrate more aspects of pointers and arrays we can study versions of
 * two useful functions adapted from the standard library. The first function
 * is strcpy(s, t), which copies the string t to the string s. It would be nice
 * just to say s=t but this copies the pointer, not the characters. To copy the
 * characters, we need a loop. The array version first:
 *
 * Because arguments are passed by value, strcpy can use the parameters s and t
 * in any way it pleases. Here they are conveniently initialized pointers,
 * which are marched along the arrays a character at a time, until the '\0'
 * that terminates t has been copied into s.
 *
 * This moves the increment of s and t into the test part of the loop. The
 * value *t++ is the character that t pointed to before t was incremented; the
 * postfix ++ doesn't change t until after this character has been fetched. In
 * the same way, the character is stored into the old s position before s is
 * incremented. This character is also the value that is compared against '\0'
 * to control the loop. The net effect is that characters are copied from t to
 * s, up and including the terminating '\0'.
 *
 * As the final abbreviation, observe that a comparison against '\0' is
 * redundant, since the question is merely whether the expression is zero. So
 * the function would likely be written as
 *
 *  void strcpy(char *s, char *t) {
 *    while (*s++ = *t++)
 *    ;
 *  }
 * Although this may seem cryptic at first sight, the notational convenience is
 * considerable, and the idiom should be mastered, because you will see it
 * frequently in C programs.
 *
 * The strcpy in the standard library (<string.h>) returns the target string as
 * its function value.
 *
 * The second routine that we will examine is strcmp(s, t), which compares the
 * character strings s and t, and returns negative, zero or positive if s is
 * lexicographically less than, equal to, or greater than t. The value is
 * obtained by subtracting the characters at the first position where s and t
 * disagree.
 */
#include <stdio.h>

/* strcpy_: copy t to s; array subscript version */
void strcpy_(char *s, char *t) {
  int i;

  i = 0;
  while ((s[i] = t[i]) != '\0')
    i++;
}

/*strcpy__: copy t to s; pointer version */
void strcpy__(char *s, char *t) {
  int i;

  i = 0;
  while ((*s = *t) != '\0') {
    s++, t++;
  }
}

// In practice, strcpy would not be written as shown above. Experienced C
// programmers would prefer
/* strcpy___: copy t to s; pointer version 2 */
void strcpy___(char *s, char *t) {
  while ((*s++ = *t++) != '\0')
    ;
}

/* strcmp_: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int strcmp_(char *s, char *t) {
  int i;

  for (i = 0; s[i] == t[i]; i++)
    if (s[i] == '\0')
      return 0;
  return s[i] - t[i];
}

// The pointer version of strcmp
int strcmp__(char *s, char *t) {
  for (; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

/***
 * Since ++ and -- are either prefix or postfix operators, other combinations
 * of * and ++ and -- occur, although less frequently. For example,
 *
 *   *--p
 * decrements p before fetching the character p points to. In fact, the pair of
 * expressions
 *
 *   *p++ = val; -> push val onto stack
 *   val = *--p; -> pop top of stack into val
 * are the standard idiom for pushing and popping s back.
 */

int main(void) {
  char s[50];
  char *t = "Knight Artorias";
  strcpy___(s, t);
  printf("%s\n", s);

  return 0;
}
