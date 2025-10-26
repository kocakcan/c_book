/***
 * 6.3 Arrays of Structures
 *
 * Consider writing a program to count the occurrences of each C keyword. We need an array of character strings to hold the names, and an array of integers for the counts. One possibility is to use two parallel arrays, keyword and keycount, as in
 *
 * 	char *keyword[NKEYS];
 * 	int keyword[NKEYS];
 * But the very fact that the arrays are parallel suggests a different organization, an array of structures. Each keyword is a pair:
 *
 * 	char *word;
 * 	int count;
 * and there is an array of pairs. The structure declaration
 *
 * 	struct key {
 * 		char *word;
 * 		int count;
 * 	} keytab[NKEYS];
 * declares a structure type key, defines an array keytab of structures of this type, and sets aside storage for them. Each element of the array is a structure. This could also be written
 *
 * 	struct key {
 * 		char *word;
 * 		int count;
 * 	};
 *
 * 	struct key keytab[NKEYS];
 * Since the structure keytab contains a constant set of names, it is easiest to make it an external variable and initialize it once and for all when it is defined. The structure initialization is analogous to earlier ones - the definition is followed by a list of initializers enclosed in braces:
 *
 * 	struct key {
 * 		char *word;
 * 		int count;
 * 	} keytab[] = {
 * 		"auto", 0,
 * 		"break", 0,
 * 		"case", 0,
 * 		"char", 0,
 * 		"const", 0,
 * 		"continue", 0,
 * 		"default", 0,
 *		"unsigned", 0,
 *		"void", 0,
 *		"volatile", 0,
 *		"while", 0
 *	};
 * The initializers are listed in pairs corresponding to the structure members. It would be more precise to enclose the initializers for each "row" or structure in braces, as in
 *
 * 	{ "auto", 0 },
 * 	{ "break", 0 },
 * 	{ "case", 0 }
 * 	...
 * but inner braces are not necessary when the initializers are simple variables or character strings, and when all are present. As usual, the number of entries in the array keytab will be computed if the initializers are present and the [] is left empty.
 *
 * The keyword counting program begins with the definition of keytab. The main routine read the input by repeatedly calling a function getword that fetches one word at a time. Each word is looked up in keytab with a version of the binary search function. The list of keywords must be sorted in increasing order in the table.
 */
 */
