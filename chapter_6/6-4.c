/***
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order or frequency of occurrence. Precede each word by its count.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define NDISTINCT 1000

struct tnode {         /* the tree node */
  char *word;          /* points to the text */
  int count;           /* number of occurrences */
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

static char buf[MAXWORD];
static char *bufp = buf;

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *);
int getch(void);
void ungetch(int);
int getword(char *, int);
void sortlist(void);
void treestore(struct tnode *);
void freetree(struct tnode *);

struct tnode *list[NDISTINCT]; /* pointers to tree nodes */
int ntn = 0;                   /* number of tree nodes */

/* print distinct words sorted in decreasing order or freq. */
int main(void) {
  struct tnode *root;
  char word[MAXWORD];
  int i;

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha((unsigned char)word[0]))
      root = addtree(root, word);
  treestore(root);
  sortlist();
  for (i = 0; i < ntn; i++)
    printf("%2d:%20s\n", list[i]->count, list[i]->word);
  freetree(root);
  return 0;
}

struct tnode *talloc(void) {
	struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
	if (p == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

struct tnode *addtree(struct tnode *p, char *w) {
	int cond;

	if (p == NULL) {	/* a new word has arrived */
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(p->word, w)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

int getch(void) { return (bufp - buf > 0) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (c == EOF)
    return;
  if (bufp - buf >= MAXWORD)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = c;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	int c;
	char *w = word;

	while (isspace(c = getch()) && c != '\n')
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

/* treestore: store in list[i] pointers to tree nodes */
void treestore(struct tnode *p) {
  if (p != NULL) {
    treestore(p->left);
    if (ntn < NDISTINCT)
      list[ntn++] = p;
    treestore(p->right);
  }
}

/* sortlist: sort list of pointers to tree nodes */
void sortlist(void) {
  int gap, i, j;
  struct tnode *temp;

  for (gap = ntn / 2; gap > 0; gap /= 2)
    for (i = gap; i < ntn; i++)
      for (j = i - gap; j >= 0; j -= gap) {
        if ((list[j]->count) >= (list[j + gap]->count))
          break;
        temp = list[j];
        list[j] = list[j + gap];
        list[j + gap] = temp;
      }
}

void freetree(struct tnode *p) {
	if (p == NULL)
		return;
	freetree(p->left);
	freetree(p->right);
	free(p->word);
	free(p);
}
