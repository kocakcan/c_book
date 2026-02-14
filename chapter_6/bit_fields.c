/***
 * 6.9 Bit-fields
 *
 * When storage is at a premium, it may be necessary to pack several objects
 * into a single machine word; one common use is a set of single-bit flags in
 * applications like compiler symbol tables. Externally-imposed data formats,
 * such as interfaces to hardware devices, also often require the ability to get
 * at pieces of a word.
 *
 * Imagine a fragment of a compiler that manipulates a symbol table. Each
 * identifier in a program has certain information associated with it, for
 * example, whether or not it is a keyword, whether or not it is external and/or
 * static, and so on. The most compact way to encode such information is a set
 * of one-bit flags in a single char or int.
 *
 * The usual way this is done is to define a set of "masks" corresponding to the
 * relevant bit positions, as in
 *
 *  #define KEYWORD 01
 *  #define EXTERNAL 02
 *  #define STATIC 04
 * or
 *
 *  enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04 };
 * The numbers must be powers of two. Then accessing the bits becomes a matter
 * of "bit-fiddling" with the shifting, masking, and complementing operators.
 *
 * Certain idioms appear frequently:
 */
