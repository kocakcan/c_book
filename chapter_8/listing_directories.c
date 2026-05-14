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
 */
