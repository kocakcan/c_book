/***
 * 8.5 Example - An implementation of Fopen and Getc
 *
 * Let us illustrate how some of these pieces fit together by showing an
 * implementation of the standard library routines fopen and getc.
 *
 * Recall that files in the standard library are described by file pointers
 * rather than file descriptors. A file pointer is a pointer to a structure that
 * contains several pieces of information about a file: a pointer to a buffer,
 * so the file can be read in large chunks; a count of the number of characters
 * left in the buffer; a pointer to the next character position in the buffer;
 * the file descriptor; and flags describing read/write mode, error status, etc.
 *
 * The data structure describes a file is contained in <stdio.h>, which must be
 * included (by #include) in any source file that uses routines from the
 * standard input/output library. It is also included by functions in that
 * library. In the following excerpt from a typical <stdio.h>, names that are
 * intended for use only by functions of the library begin with an underscore so
 * they are less likely to collide with names in a user's program. This
 * convention is used by all standard library routines.
 */
#ifndef _STDIO_H
#define _STDIO_H
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

// struct flag_field {
//   unsigned is_read : 1;
//   unsigned is_write : 1;
//   unsigned is_unbuf : 1;
//   unsigned is_buf : 1;
//   unsigned is_eof : 1;
//   unsigned is_err : 1;
// };

typedef struct _iobuf {
  int cnt;    /* characters left */
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  int flag;   /* mode of file access */
  int fd;     /* file descriptor */
} _FILE;

extern _FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
  _READ = 01,  /* file open for reading */
  _WRITE = 02, /* file open for writing */
  _UNBUF = 04, /* file is unbuffered */
  _EOF = 010,  /* EOF has occurred on this file */
  _ERR = 020   /* error occurred on this file */
};

int _fillbuf(_FILE *);
int _flushbuf(int, _FILE *);
_FILE *_fopen(char *name, char *mode);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

/***
 * The getc macro normally decrements the count, advances the pointer, and
 * returns the character. (Recall that a long #define is continued with a
 * backslash.) If the count goes negative, however, getc calls the function
 * _fillbuf to replenish the buffer, re-initialize the structure contents, and
 * return a character. The characters are returned unsigned, which ensures that
 * all characters will be positive.
 *
 * Although we will not discuss any details, we have included the definition of
 * putc to show that it operates in much the same way as getc, calling a
 * function _flushbuf when its buffer is full. We have also included macros for
 * accessing the error and end-of-file status and the file descriptor.
 *
 * The function fopen can now be written. Most of fopen is concerned with
 * getting the file opened and positioned at the right place, and setting the
 * flag bits to indicate the proper state. fopen does not allocate any buffer
 * space; this is done by _fillbuf when the file is first read.
 */

/***
 * This version of fopen does not handle all of the access mode possibilities of
 * the standard, though adding them would not take much code. In particular, our
 * fopen does not recognize the "b" that signals binary access, since that is
 * meaningless on UNIX systems, nor the "+" that permits both reading and
 * writing.
 *
 * The first call to getc for a particular file finds a count of zero, which
 * forces a call of _fillbuf. If _fillbuf finds that file is not open for
 * reading, it returns EOF immediately. Otherwise, it tries to allocate a buffer
 * (if reading is to be buffered).
 *
 * Once the buffer is established, _fillbuf calls read to fill it, sets the
 * count and pointers, and returns the character at the beginning of the buffer.
 * Subsequent calls to _fillbuf will find a buffer allocated.
 */

// The only remaining loose end is how everything gets started. The array _iob
// must be defined and initialized for stdin, stdout and stderr:

// The initialization of the flag part of the structure shows that stdin is to
// be read, stdout is to be written, and stderr is to be written unbuffered.
#endif /* _STDIO_H */
