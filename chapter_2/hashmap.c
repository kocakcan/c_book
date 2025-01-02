#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 100

typedef struct {
  char *key;
  int value;
  struct Entry *next;
} Entry;

typedef struct {
  Entry **buckets;
} HashTable;

unsigned int hash(const char *key);
Entry *create_entry(const char *key, int value);
HashTable *create_table();
void insert(HashTable *table, const char *key, int value);
int search(HashTable *table, const char *key, int *value);
void print_table(const HashTable *table);

int main(void) {
  HashTable *table = create_table();

  // Insert key-value pairs
  insert(table, "Alice", 25);
  insert(table, "Bob", 30);
  insert(table, "Seyfi", 59);
  insert(table, "Leyli", 54);

  // Search for a key
  int age;
  if (search(table, "Can", &age)) {
    printf("Can's age is: %d\n", age);
  } else {
    printf("Can was not found");
  }

  print_table(table);

  free(table);
}

Entry *create_entry(const char *key, int value) {
  Entry *new_entry = malloc(sizeof(Entry));
  if (!new_entry) {
    fprintf(stderr, "Failed to allocate memory for entry.\n");
    exit(EXIT_FAILURE);
  }

  new_entry->key = strdup(key);

  if (!new_entry->key) {
    fprintf(stderr, "Failed to duplicate key.\n");
    free(new_entry);
    exit(EXIT_FAILURE);
  }

  new_entry->value = value;
  new_entry->next = NULL;

  return new_entry;
}

HashTable *create_table() {
  HashTable *table = malloc(sizeof(HashTable));

  if (!table) {
    fprintf(stderr, "Failed to allocate memory for hash table.\n");
    exit(EXIT_FAILURE);
  }

  table->buckets = malloc(sizeof(Entry *) * TABLE_SIZE);
  if (!table->buckets) {
    fprintf(stderr, "Failed to allocate memory for buckets.\n");
    free(table);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }

  return table;
}

unsigned int hash(const char *key) {
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int key_len = strlen(key);

  for (; i < key_len; i++) {
    value = value * 37 + key[i];
  }

  return value % TABLE_SIZE;
}

void insert(HashTable *table, const char *key, int value) {
  unsigned int bucket = hash(key);

  Entry *new_entry = create_entry(key, value);

  if (table->buckets[bucket] == NULL) {
    table->buckets[bucket] = new_entry;
  } else {
    new_entry->next = table->buckets[bucket];
    table->buckets[bucket] = new_entry;
  }
}

int search(HashTable *table, const char *key, int *value) {
  unsigned int bucket = hash(key);
  Entry *entry = table->buckets[bucket];

  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      // Key found
      *value = entry->value;
      return 1;
    }
    entry = entry->next;
  }

  // Key not found
  return 0;
}

void print_table(const HashTable *table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Entry *entry = table->buckets[i];
    if (entry == NULL) {
      continue;
    }
    printf("Bucket[%d]: ", i);
    while (entry != NULL) {
      printf("(%s: %d) -> ", entry->key, entry->value);
      entry = entry->next;
    }
    printf("NULL\n");
  }
}
