#include <stdio.h>

#define FAMILY_SIZE 5

enum GENDER { MALE, FEMALE, OTHER };
enum MARITAL_STATUS { MARRIED, SINGLE, DIVORCED, WIDOWED };

struct Kocak {
  char *name;
  int age;
  enum GENDER gender;
  enum MARITAL_STATUS m_status;
};

char *gender_to_string(enum GENDER gender) {
  switch (gender) {
  case MALE:
    return "MALE";
    break;
  case FEMALE:
    return "FEMALE";
    break;
  case OTHER:
    return "OTHER";
    break;
  default:
    return "UNKNOWN GENDER";
    break;
  }
}

char *marital_status_to_string(enum MARITAL_STATUS m_status) {
  switch (m_status) {
  case MARRIED:
    return "MARRIED";
    break;
  case SINGLE:
    return "SINGLE";
    break;
  case DIVORCED:
    return "DIVORCED";
    break;
  case WIDOWED:
    return "WIDOWED";
    break;
  default:
    return "UNKNOWN MARITAL_STATUS";
    break;
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
  double result;

  for (int i = 0; i < FAMILY_SIZE; i++)
    result += kocak++->age;

  return result / FAMILY_SIZE;
}

int main(void) {
  struct Kocak kocaks[] = {{"Seyfi", 60, MALE, MARRIED},
                           {"Leyli", 55, FEMALE, MARRIED},
                           {"Dilan", 32, FEMALE, MARRIED},
                           {"Medet", 32, FEMALE, MARRIED},
                           {"Can", 27, MALE, WIDOWED}};

  size_t family_size = FAMILY_SIZE;
  struct Kocak *kp = kocaks;

  while (family_size--) {
    printf("Name: %s | Age: %d | Gender: %s | Marital Status: %s\n", kp->name,
           kp->age, gender_to_string(kp->gender),
           marital_status_to_string(kp->m_status));
    kp++;
  }

  printf("Oldest family member is %d years old.\n", max_age(kocaks));
  printf("Youngest family member is %d years old.\n", min_age(kocaks));
  printf("Average age in the Kocak family is %.2f\n", avg_age(kocaks));

  return 0;
}
