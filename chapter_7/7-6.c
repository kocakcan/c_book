/*
 * Write a program to compare two files, printing the first line where they
 * differ.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *fp, *fp2;
  char buffer[256];
  char _buffer[256];

  if ((fp = fopen("test.log", "r")) != NULL)
    fscanf(fp, "%[^\n]", buffer);

  if ((fp2 = fopen("input.log", "r")) != NULL)
    fscanf(fp2, "%[^\n]", _buffer);

  fclose(fp);
  fclose(fp2);

  if (strcmp(buffer, _buffer) != 0)
    printf("They are different!\n");
  else
    printf("They are same!\n");

  return 0;
}
