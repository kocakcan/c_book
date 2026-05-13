/* The standard library function
 *
 * 	int fseek(FILE *fp, long offset, int origin)
 * is identical to lseek except that fp is a file pointer instead of a file descriptor and return value is an int status, not a position. Write fseek. Make sure that your fseek coordinates properly with the buffering done for the functions of the library.
 */
#include <unistd.h>
#include <stdio.h>

/* fseek: seek with a file pointer */
int _fseek(FILE *fp, long offset, int origin) {
	unsigned nc;					/* # of chars to flush */
	long rc = 0;					/* return code */

	if (fp->flag & _READ) {
		if (origin == 1)			/* from current position? */
			offset -= fp->cnt;		/* rememeber chars in buffer */
		rc = lseek(fp->fd, offset, origin);
		fp->cnt = 0;				/* no chars buffered */
	} else if (fp->flag & _WRITE) {
		if ((nc = fp->ptr - fp->base) > 0)
			if (write(fp->fd, fp->base, nc) != nc)
				rc = -1;
		if (rc != -1)
			rc = lseek(fp->fd, offset, origin);
	}
	return (rc == -1) ? -1 : 0;
}

/***
 * The variable rc contains the return code. It is set to -1 when an error occurs.
 * There are two situations in fseek: the file is open for reading or it is open for writing.
 * When the file is open for reading and the origin is 1, the offset is counted from the current position (the other cases are: origin 0, the offset is counted from the beginning of the files; origin 2, the offset is counted from the end of the file). To measure the offset from the current position, fseek takes the characters already in the buffer into account:
 *
 * 	if (origin == 1)
 * 		offset -= fp->cnt;
 * fseek then invokes lseek and discards the buffered characters:
 * 	
 * 	rc = lseek(fp->fd, offset, origin);
 * 	fp->cnt = 0;
 * When the file is open for writing, fseek first flushes buffered characters if any:
 *
 * 	if ((nc = fp->ptr - fp->base) > 0)
 * 		if (write(fp->fd, fp->base, nc) != nc)
 * 			rc = -1;
 *
 * If there are no errors, fseek calls lseek:
 * 	
 * 	if (rc != -1)
 * 		rc = lseek(fp->fd, offset, origin);
 * The function fseek returns 0 for proper seeks.
 */
