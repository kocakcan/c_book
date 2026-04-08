/***
 * Chapter 8 - The UNIX System Interface
 *
 * The UNIX operating system provides its services through a set of system
 * calls, which are in effect functions within the operating system that may be
 * called by user programs. This chapter describes how to use some of the most
 * important system calls from C programs. If you use UNIX, this should be
 * directly helpful, for it is sometimes necessary to employ system calls for
 * maximum efficiency, or to access some facility that is not in the library.
 * Even if you use C on a different operating system, however, you should be
 * able to glean insight into C programming from studying these examples;
 * although details vary, similar code will be found on any system. Since the
 * ANSI C library is in my cases modeled on UNIX facilities, this code may help
 * your understanding of the library as well.
 *
 * 8.1 File Descriptors
 *
 * In the UNIX operating system, all input and output is done by reading or
 * writing files, because all peripheral devices, even keyboard and screen, are
 * files in the file system. This means that a single homogeneous interface
 * handles all communication between a program and peripheral devices.
 *
 * In the most general case, before you read and write a file, you must inform
 * the system of your intent to do so, a process called opening the file. If you
 * are going to write on a file it may also be necessary to create it or discard
 * its previous contents. The system checks your right to do so (Does the file
 * exist? Do you have permission to access it?) and if all is well, returns to
 * the program a small non-negative integer called a file descriptor. Whenever
 * input or output is to be done on a file, the file descriptor is used instead
 * of the name to identify the file. (A file descriptor is analogous to the file
 * pointer used by the standard library, or to the file handle of MS-DOS.) All
 * information about an open file is maintained by the system; the user program
 * refers to the file only by the file descriptor.
 *
 * Since input and output invoking keyboard and screen is so common, special
 * arrangements exist to make this convenient. When the command interpreter (the
 * "shell") runs a program, three files are open, with file descriptors 0, 1,
 * and 2, called the standard input, the standard output, and the standard
 * error. If a program reads 0 and writes 1 and 2, it can do input and output
 * without worrying about opening files.
 *
 * The user of a program can redirect I/O and from files with < and >:
 *
 *  prog < infile > outfile
 */
