#include <stdio.h>
#include <stdlib.h>

#define FAMILY_SIZE 5

enum GENDER { MALE, FEMALE, OTHER };
enum MARITAL_STATUS { MARRIED, SINGLE, DIVORCED, WIDOWED };

int strcmp_(const char *, const char *);
int numcmp(int, int);
int namecmp(const void *, const void *);
int agecmp(const void *, const void *);

struct Kocak {
  char *name;
  int age;
  enum GENDER gender;
  enum MARITAL_STATUS m_status;
};

const char *gender_to_string(enum GENDER gender) {
  switch (gender) {
  case MALE:
    return "MALE";
  case FEMALE:
    return "FEMALE";
  case OTHER:
    return "OTHER";
  default:
    return "UNKNOWN GENDER";
  }
}

const char *marital_status_to_string(enum MARITAL_STATUS m_status) {
  switch (m_status) {
  case MARRIED:
    return "MARRIED";
  case SINGLE:
    return "SINGLE";
  case DIVORCED:
    return "DIVORCED";
  case WIDOWED:
    return "WIDOWED";
  default:
    return "UNKNOWN MARITAL_STATUS";
  }
}

int max_age(struct Kocak *kocak) {
  int max = kocak++->age;

  for (int i = 1; i < FAMILY_SIZE; i++) {
    if (kocak->age > max)
      max = kocak->age;
    kocak++;
  }

  return max;
}

int min_age(struct Kocak *kocak) {
  int min = kocak++->age;

  for (int i = 1; i < FAMILY_SIZE; i++) {
    if (kocak->age < min)
      min = kocak->age;
    kocak++;
  }

  return min;
}

double avg_age(struct Kocak *kocak) {
  double result = 0.0;

  for (int i = 0; i < FAMILY_SIZE; i++)
    result += kocak++->age;

  return result / FAMILY_SIZE;
}

struct Kocak *find_by_name(struct Kocak *kocak, const char *name) {
  for (size_t i = 0; i < FAMILY_SIZE; i++) {
    if (strcmp_(kocak->name, name) == 0)
      return kocak;
    kocak++;
  }

  return NULL;
}

void printk(const struct Kocak *kocak) {
  for (size_t i = 0; i < FAMILY_SIZE; i++) {
    printf("Name: %-5s | Age: %d | Gender: %-6s | Marital Status: %s\n",
           kocak->name, kocak->age, gender_to_string(kocak->gender),
           marital_status_to_string(kocak->m_status));
    kocak++;
  }
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t)
    s++, t++;
  return (unsigned char)*s - (unsigned char)*t;
}

int numcmp(int i, int j) {
  if (i < j)
    return -1;
  else if (i > j)
    return 1;
  else
    return 0;
}

int namecmp(const void *s, const void *t) {
  const struct Kocak *a = (const struct Kocak *)s;
  const struct Kocak *b = (const struct Kocak *)t;
  return strcmp_(a->name, b->name);
}

int agecmp(const void *s, const void *t) {
  const struct Kocak *a = (const struct Kocak *)s;
  const struct Kocak *b = (const struct Kocak *)t;
  return -numcmp(a->age, b->age);
}

int main(void) {
  struct Kocak kocaks[] = {{"Seyfi", 60, MALE, MARRIED},
                           {"Leyli", 55, FEMALE, MARRIED},
                           {"Dilan", 32, FEMALE, MARRIED},
                           {"Medet", 32, FEMALE, MARRIED},
                           {"Can", 27, MALE, WIDOWED}};

  struct Kocak *kp = kocaks;
  printk(kocaks);

  printf("Oldest family member is %d years old.\n", max_age(kocaks));
  printf("Youngest family member is %d years old.\n", min_age(kocaks));
  printf("Average age in the Kocak family is %.2f\n", avg_age(kocaks));
  struct Kocak *result = find_by_name(kocaks, "Abuzittin");
  printf("Result: %s\n", (result != NULL) ? result->name : "NOT FOUND");

  printf("Sorting according to name\n");
  qsort(kocaks, FAMILY_SIZE, sizeof(struct Kocak), namecmp);
  printk(kocaks);

  printf("Sorting according to age\n");
  qsort(kocaks, FAMILY_SIZE, sizeof(struct Kocak), agecmp);
  printk(kocaks);
  return 0;
}
