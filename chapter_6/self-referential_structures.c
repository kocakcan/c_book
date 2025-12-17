/***
 * 6.5 Self-Referential Structures
 *
 * Suppose we want to handle the more general problem of counting the
 * occurrences of all the words in some input. Since the list of words isn't
 * known in advance, we can't conveniently sort it and use a binary search. Yet
 * we can't do a linear search for each word as it arrives, to see if it's
 * already been seen; the program would take too long. (More precisely, its
 * running time is likely to grow quadratically with the number of input words.)
 * How can we organize the data to copy efficiently with a list of arbitrary
 * words?
 *
 * One solution is to keep the set of words seen so far sorted at all times, by
 * placing each word into its proper position in the order as it arrives. This
 * shouldn't be done by shifting words in a linear array, though - that also
 * takes too long. Instead we use a data structure called a binary tree.
 *
 * The tree contains one "node" per distinct word; each node contains
 *
 * -> A pointer to the text of the word
 * -> A count of the number of occurrences
 * -> A pointer to the left child node
 * -> A pointer to the right child node
 *
 * No node may have more than two children; it might have only zero or one.
 *
 * The nodes are maintained so that at any node the left subtree contains only
 * words that are lexicographically less than the word at the node, and the
 * right subtree contains only words that are greater.
 *
 * To find out whether a new word is already in the tree, start at the root and
 * compare the new word to the word stored at that node. If they match, the
 * question is answered affirmatively. If the new record is less than the tree
 * word, continue searching at the left child, otherwise at the right child. If
 * there is no child in the required direction, the word is not in the tree, and
 * in fact the empty slot is the proper place to add the new word. This process
 * is recursive, since the search from any node uses a search from one of its
 * children. Accordingly, recursive routines for insertion and printing will be
 * most natural.
 *
 * Going back to the description of a node, it is mostly conveniently
 * represented as a structure with four components:
 *
 *  struct tnode {        -> the tree node
 *    char *word;         -> points to the text
 *    int count;          -> number of occurrences
 *    struct tnode *left; -> left child
 *    struct tnode *right -> right child
 *  };
 * This recursive declaration of a node might look chancy, but it's correct. It
 * is illegal for a structure to contain an instance of itself, but
 *
 *  struct tnode *left;
 * declares left to be a pointer to a tnode, not a tnode itself.
 *
 * Occassionally, one needs a variation of self-referential structures: two
 * structures that refer to each other. The way to handle this is:
 *
 *  struct t {
 *    ...
 *    struct s *p;  -> p points to an s
 *  };
 *
 *  struct s {
 *    ...
 *    struct t *q;  -> q points to a q
 *  };
 * The code for the whole program is surprisingly small, given a handful of
 * supporting routines like getword that we have already written. The main
 * routine reads words with getword and installs them in the tree with addtree.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdup_(char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main(void) {
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treeprint(root);
  return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) { /* a new word has arrived */
    p = talloc();  /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word) == 0))
    p->count++;      /* repeated word */
  else if (cond < 0) /* less than into left subtree */
    p->left = addtree(p->left, w);
  else /* greater than into right subtree */
    p->right = addtree(p->right, w);
  return p;
}

/***
 * The function addtree is recursive. A word is presented by main to the top
 * level (the root) of the tree. At each stage, that word is compared to the
 * word already stored at the node, and is percolated down to either left or
 * right subtree by a recursive call to addtree. Eventually, the word either
 * matches something already in the tree (in which case the count is
 * incremented), or a null pointer is encountered, indicating that a node must
 * be created and added to the tree. If a new node is created, addtree returns a
 * pointer to it, which is installed in the parent node.
 *
 * Storage for the new node is fetched by a routine talloc, which returns a
 * pointer to a free space suitable for holding a tree node, and the new word
 * is copied into a hidden space by strdup. The count is initialized, and the
 * two children are made null. This part of the code is executed only at the
 * leaves of the tree, when a new node is being added.
 *
 * treeprint prints the tree in sorted order; at each node, it prints the left
 * subtree (all the words less than this word), then the word itself, then the
 * right subtree (all the words greater).
 */

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}
