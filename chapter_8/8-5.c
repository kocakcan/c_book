/* Modify the fsize program to print the other information contained in the
 * inode entry. */
#include "dirent.h"
#include <fcntl.h> /* flags for read and write */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>  /* structure returned by stat */
#include <sys/types.h> /* typedefs */

int _stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* fsize: print inode #, mode, links, size of file "name" */
void fsize(char *name) {
  struct stat stbuf;

  if (_stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    dirwalk(name, fsize);
  printf("%5u %6o %3u %8ld %s\n", stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink,
         stbuf.st_size, name);
}

/*** We modified fsize to print the inode number, the file mode in octal, the
 * number of links to the file, the file size, and the file name. */
