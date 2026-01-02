/***
 * 6.6 Table Lookup
 *
 * In this section we will write the innards of a table-lookup package, to
 * illustrate more aspects of structures. This code is typical of what might be
 * found in the symbol table management routines of a macro processor or a
 * compiler. For example, consider the #define statement. When a line like
 *
 *   #define IN 1
 * is encountered, the name IN and the replacement text 1 are stored in a table.
 * Later, when the name IN appears in a statement like
 *
 *   state = IN;
 * it must be replaced by 1.
 *
 * There are two routines that manipulate the names and replacement texts.
 * install(s, t) records the name s and the replacement text t in a table; s and
 * t are just character strings. lookup(s) searches for s in the table, and
 * returns a pointer to the place where it was found, or NULL if it wasn't
 * there.
 *
 * The algorithm is a hash-search - the incoming name is converted into a small
 * non-negative integer, which is then used to index into an array of pointers.
 * An array element points to the beginning of a linked list of blocks
 * describing names that have that hash value. It is NULL if no names have
 * hashed to that value.
 */
