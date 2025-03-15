#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
  int data;          // Data part
  struct Node *next; // Pointer to the next node
} Node;

// Function to create a new node
Node *create_node(int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }
  new_node->data = data; // Set the data for the new node
  new_node->next = NULL; // Initialize the next pointer to NULL
  return new_node;
}

// Function to add a node to the front of the linked list
void add_to_front(Node **head, int data) {
  Node *new_node = create_node(data);
  new_node->next = *head; // Point the new node to the current head
  *head = new_node;       // Update the head to the new node
}

// Function to add a node to the end of the linked list
void add_to_end(Node **head, int data) {
  Node *new_node = create_node(data);
  if (*head == NULL) {
    *head = new_node; // If the list is empty, the new node is the head
    return;
  }
  Node *current = *head;
  while (current->next != NULL) {
    current = current->next; // Traverse to the end of the list
  }
  current->next = new_node; // Link the new node at the end
}

// Function to remove a node from the linked list
void remove_node(Node **head, int data) {
  Node *current = *head;
  Node *previous = NULL;

  while (current != NULL && current->data != data) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    printf("Node with data %d not found.\n", data);
    return; // Node not found
  }

  if (previous == NULL) {
    // The node to be deleted is the head
    *head = current->next;
  } else {
    // Bypass the node to be deleted
    previous->next = current->next;
  }

  free(current); // Free the memory allocated to the deleted node
}

// Function to print the linked list
void print_list(Node *head) {
  Node *current = head;
  while (current != NULL) {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

// Free all nodes in the linked list
void free_list(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *next_node = current->next; // Store the next node
    free(current);                   // Free the current node
    current = next_node;             // Move to the next node
  }
}

int main() {
  Node *head = NULL; // Initialize the head of the list

  // Add nodes to the linked list
  add_to_front(&head, 3);
  add_to_front(&head, 2);
  add_to_front(&head, 1);

  add_to_end(&head, 4);
  add_to_end(&head, 5);

  printf("Linked List: ");
  print_list(head); // print the linked list

  // Remove a node
  remove_node(&head, 3);
  printf("After removing 3: ");
  print_list(head); // print the linked list again

  // Clean up
  free_list(head);

  return 0;
}
