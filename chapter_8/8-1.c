/*
 * Rewrite the program cat from Chapter 7 using read, write, open, and close
 * instead of their standard library equivalents. Perform experiments to
 * determine the relative speeds of the two versions.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void error(char *fmt, ...);

/* cat: concatenate files - read / write / open / close */
int main(int argc, char *argv[]) {
  int fd;
  void filecopy(int ifd, int ofd);

  if (argc == 1) /* no args; copy standard input */
    filecopy(0, 1);
  else
    while (--argc > 0)
      if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
        printf("cat: can't open %s\n", *argv);
        return 1;
      } else {
        filecopy(fd, 1);
        close(fd);
      }

  return 0;
}

/* filecopy: copy file ifd to file ofd */
void filecopy(int ifd, int ofd) {
  int n;
  char buf[BUFSIZ];

  while ((n = read(ifd, buf, BUFSIZ)) > 0)
    if (write(ofd, buf, n) != n)
      error("cat: write error");
}
