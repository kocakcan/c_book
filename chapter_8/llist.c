#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *newnode(int data) {
	struct node *p;

	p = malloc(sizeof(struct node));
	if (p == NULL) {
		fprintf(stderr, "newnode: out of memory\n");
		exit(1);
	}
	p->data = data;
	p->next = NULL;
	return p;
}

struct node *prepend(struct node *head, int data) {
	struct node *p = newnode(data);
	p->next = head;
	return p;
}

struct node *append(struct node *head, int data) {
	struct node *p, *cur;

	p = newnode(data);
	if (head == NULL)
		return p;
	for (cur = head; cur->next != NULL; cur = cur->next)
		;
	cur->next = p;
	return head;
}

struct node *delete(struct node *head, int data) {
	struct node *cur, *prev;

	prev = NULL;
	for (cur = head; cur != NULL; cur = cur->next) {
		if (cur->data == data) {
			if (prev == NULL)
				head = cur->next;
			else
				prev->next = cur->next;
		free(cur);
		return head;
		}
		prev = cur;
	}
	return head;
}

void print(struct node *head) {
	struct node *p;

	for (p = head; p != NULL; p = p->next)
		printf("%d%s", p->data, p->next ? " -> " : "\n");
	if (head == NULL)
		printf("(empty)\n");
}

void freeall(struct node *head) {
	struct node *p, *next;

	for (p = head; p != NULL; p = next) {
		next = p->next;
		free(p);
	}
}

int main(void) {
	struct node *head = NULL;

	head = append(head, 10);
	head = append(head, 20);
	head = append(head, 30);
	head = prepend(head, 5);

	print(head);
	head = delete(head, 20);
	print(head);
	freeall(head);
	return 0;
}

