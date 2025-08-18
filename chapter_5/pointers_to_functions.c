/***
 *
 * 5. 11 Pointers to Functions
 *
 * In C, a function itself is not a variable, but it is possible to define
 * pointers to functions, which can be assigned, placed in arrays, passed to
 * functions, returned by functions, and so on. We will illustrate this by
 * modifying the sorting procedure written earlier in this chapter so that if
 * the optional argument -n is given, it will sort the input lines numerically
 * instead of lexicographically.
 *
 * A sort often consists of three parts - a comparison that determines the
 * ordering of any pair of objects, an exchange that reverses their order, and a
 * sorting algorithm that makes comparisons and exchanges until the objects are
 * in order. The sorting algorithm is independent of the comparison and exchange
 * operations, so by passing different comparison and exchange functions to it,
 * we can arrange to sort by different criteria. This is the approach taken in
 * our new sort.
 */
