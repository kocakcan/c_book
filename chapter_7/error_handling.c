/***
 * Error Handling - Stderr and Exit
 *
 * The treatment of errors in cat is not ideal. The trouble is that if one of
 * the files can't be accessed for some reason, the diagnostic is printed at the
 * end of the concatenated output. That might me acceptable if the output is
 * going to a screen, but not if it's going into a file or into another program
 * via a pipeline.
 *
 * To handle this situation better, a second output stream, called stderr, is
 * assigned to a program in the same way that stdin and stdout are. Output
 * written on stderr normally appears on the screen even if the standard output
 * is redirected.
 */
