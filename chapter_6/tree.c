#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

static char buf[MAXWORD];
static char *bufp = buf;

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
int getch(void);
void ungetch(int);
int getword(char *, int);
char *strdup_(const char *);
int strcmp_(const char *, const char *);
void strcpy_(char *, const char *);
void treeprint(struct tnode *);
void freetree(struct tnode *);

int main(void) {
  struct tnode *root = talloc();
  // char word[MAXWORD];
  //
  // root = NULL;
  // while (getword(word, MAXWORD) != EOF)
  //   if (isalpha((unsigned char)word[0]))
  //     root = addtree(root, word);
  // treeprint(root);
  //
  // freetree(root);
  root->word = "Can";
  root->count = 1;
  root->left = NULL;
  root->right = NULL;
  root = addtree(root, "Medet");
  root = addtree(root, "Seyfi");
  root = addtree(root, "Boromir");
  printf("self: %s | left: %s | right: %s | right->right: %s\n", root->word,
         root->left != NULL ? root->left->word : "NULL",
         root->right != NULL ? root->right->word : "NULL",
         root->right->right != NULL ? root->right->right->word : "NULL");
  return 0;
}

struct tnode *talloc(void) {
  struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
  if (p == NULL) {
    fprintf(stderr, "talloc: out of memory\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t)
    s++, t++;
  return (unsigned char)*s - (unsigned char)*t;
}

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) { /* a new word has arrived */
    p = talloc();  /* make a new tree */
    p->word = strdup_(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp_(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);
  return p;
}

int getword(char *word, int lim) {
  int c;
  char *w = word;

  while ((c = getch()) != EOF && isspace((unsigned char)c))
    ;
  if (c == EOF)
    return EOF;
  *w++ = (char)c;
  if (!isalpha((unsigned char)c)) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; w++) {
    c = getch();
    if (c == EOF || !isalnum((unsigned char)c)) {
      if (c != EOF)
        ungetch(c);
      break;
    }
    *w = (char)c;
  }
  *w = '\0';
  return word[0];
}

int getch(void) { return (bufp - buf > 0) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (c == EOF)
    return;
  if (bufp - buf >= MAXWORD)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = (char)c;
}

void strcpy_(char *s, const char *t) {
  while (*s++ = *t++)
    ;
}

char *strdup_(const char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p == NULL) {
    fprintf(stderr, "strdup_: out of memory\n");
    exit(EXIT_FAILURE);
  }
  strcpy_(p, s);
  return p;
}

void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
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
