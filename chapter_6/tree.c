#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD	100

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
int getword (char *, int);
char *strdup_(char *);
int strcmp_(const char *, const char *);
void strcpy_(char *, const char *);
void treeprint(struct tnode *);

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

struct tnode *talloc(void) {
	return (struct tnode *)malloc(sizeof(struct tnode));
}

int strcmp_(const char *s, const char *t) {
	while (*s && *s == *t) {
		if (*s == '\0')
			return 0;
		s++, t++;
	}
	return (unsigned char)*s - (unsigned char)*t;
}

struct tnode *addtree(struct tnode *p, char *w) {
	int cond;

	if (p == NULL) {	/* a new word has arrived */
		p = talloc();	/* make a new tree */
		p->word = strdup_(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp_(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p, p->word);
	else
		p->right = addtree(p, p->word);
	return p;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF) {
		*w++ = c;
	}
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

int getch(void) {
	return (bufp - buf) ? *--bufp : getchar();
}

void ungetch(int c) {
	if (bufp - buf >= MAXWORD)
		printf("ungetch: too many characters\n");
	else
		*bufp++ = c;
}

void strcpy_(char *s, const char *t) {
       while (*s++ = *t++)
       	;
}       

char *strdup_(char *s) {
	char *p;

	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
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
