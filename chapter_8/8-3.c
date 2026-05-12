/* Design and write _flushbuf, fflush, and fclose. */
#include "_stdio.h"
#include <stdlib.h>
#include <unistd.h>

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, _FILE *fp) {
  unsigned nc; /* # of chars to flush */
  int bufsize; /* sizeof buffer alloc. */

  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF; /* error: invalid pointer */
  if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) { /* no buffer yet */
    if ((fp->base = malloc(bufsize)) == NULL) {
      fp->flag != _ERR;
      return EOF; /* can't get buffer */
    }
  } else { /* buffer already exists */
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc) {
      fp->flag != _ERR;
      return EOF; /* error: return EOF */
    }
  }
  fp->ptr = fp->base;
  *fp->ptr++ = (char)x;
  fp->cnt = bufsize - 1;
  return x;
}

/* fclose: close file */
int _fclose(_FILE *fp) {
  int rc; /* return code */
  int _fflush(_FILE *);

  if ((rc = _fflush(fp)) != EOF) { /* anything to flush? */
    free(fp->base);                /* free allocated buffer */
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag &= (_READ | _WRITE);
  }
  return rc;
}

/* _fflush: flush buffer associated with file fp */
int _fflush(_FILE *fp) {
  int rc = 0;

  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF; /* error: invalid pointer */
  if (fp->flag & _WRITE)
    rc = _flushbuf(0, fp);
  fp->ptr = fp->base;
  fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  return rc;
}
