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
 */
