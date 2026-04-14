/***
 * 8.3 Open, Create, Close, Unlink
 *
 * Other than the default standard input, output and error, you must explicitly
 * open files in order to read or write them. There are two system calls for
 * this, open and create.
 *
 * open is rather like the fopen discussed in Chapter 7. except that instead of
 * returning a file pointer, it returns a file descriptor, which is just an int.
 * open returns -1 if any error occurs.
 *
 *  #include <fcntl.h>
 *
 *  int fd;
 *  int open(char *name, int flags, int perms);
 *
 *  fd = open(name, flags, perms);
 */
