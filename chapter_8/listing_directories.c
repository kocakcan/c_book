/***
 * 8.6 Example - Listing Directories
 *
 * A different kind of file system interaction is sometimes called for -
 * determining information about a file, not what it contains. A
 * directory-listing program such as the UNIX command ls is an example - it
 * prints the names of files in a directory, and optionally, other information,
 * such as sizes, permissions, and so on. The MS-DOS dir command is analogous.
 *
 * Since a UNIX directory is just a file, ls need only read it to retrieve the
 * filenames. But it is necessary to use a system call to access other
 * information about a file, such as its size. On other systems, a system call
 * may be needed even to access filenames; this is the case on MS-DOS for
 * instance. What we want is provide access to the information in a relatively
 * system-independent way, even though the implementation may be highly
 * system-dependent.
 *
 * We will illustrate some of this by writing a program called fsize, fsize is a
 * special form of ls that prints the size of all files named in its commandline
 * argument list. If one of the files is a directory, fsize applies itself
 * recursively to that directory. If there are no arguments at all, it processes
 * the current directory.
 *
 * Let us begin with a short review of UNIX file system structure. A directory
 * is a file that contains a list of filenames and some indication of where they
 * are located. The "location" is an index into another table called the "inode
 * list". The inode for a file is where all information about the file except
 * its name is kept. A directory entry generally consists of only two items, the
 * filename and an inode number.
 *
 * Regrettably, the format and precise contents of a directory are not the same
 * on all versions of the system. So we will divide the task into two pieces to
 * try to isolate the non-portable parts. The outer level defines a structure
 * called a Dirent and three routines opendir, readdir, and closedir to provide
 * system-independent access to the name and inode number in a directory entry.
 * We will write fsize with this interface. Then we will show how to implement
 * these on systems that use the same directory structure as Version 7 and
 * System V UNIX; variants are left as exercises.
 *
 * The Dirent structure contains the inode number and the name. The maximum
 * length of a filename component is NAME_MAX, which is a system-dependent
 * value, opendir returns a pointer to a structure called DIR, analogous to
 * FILE, which is used by readdir and closedir. This information is collected
 * into a file called dirent.h.
 *
 * The system call stat takes a filename and returns all of the information in the ino-
 * de for that file, or -1 if there is an error. That is,
 *
 * fills the structure stbuf with the inode information for the file name. The struct-
 * ure describing the value returned by stat is in <sys/stat.h>, and typically looks l-
 * ike this:
 */
#include <sys/types.h>
#include <sys/stat.h>

struct _stat {				/* inode information returned by stat */
	dev_t		st_dev;		/* device of inode */
	ino_t		st_ino;		/* inode number */
	short		st_mode;	/* mode bits */
	short		st_nlink;	/* number of links to file */
	short		st_uid;		/* owners user id */
	short		st_gid;		/* owners group id */
	dev_t		st_rdev;	/* for special files */
	off_t		st_size;	/* file size in characters */
	time_t		st_atime;	/* time last accessed */
	time_t		st_mtime;	/* time last modified */
	time_t		st_ctime;	/* time originally created */
};
/***
 * Most of the values are explained by the comment fields. The types like dev_t and i-
 * no_t are defined in <sys/types.h>, which must be included too.
 *
 * The st_mode entry contains a set of flags describing the file. The flag definitions
 * are also included in <sys/types.h>; we need only the part that deals with file type:
 */
#define S_IFMT		0160000		/* type of file */
#define S_IFDIR		0040000		/* directory */
#define S_IFCHR		0020000		/* character special */
#define S_IFBLK		0060000		/* block special */
#define S_IFREG		0010000		/* regular */
/***
 * Now we are ready to write the program fsize. If the mode obtained from stat indicat-
 * es that a file is not a directory, then the size is at hand and can be printed dire-
 * ctly. If the name is a directory, however, then we have to process that directory o-
 * ne file at a time; it may in turn contain sub-directories, so the process is recurs-
 * ive.
 *
 * The main routine deals with command-line arguments; it hands each argument to the f-
 * unction fsize.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "dirent.h"

void fsize(char *);

/* print file name */
int main(int argc, char **argv) {
	if (argc == 1)	/* default current directory */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}
