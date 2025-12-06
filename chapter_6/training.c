#include <stdio.h>

#define NEMPLOYEES (sizeof employees / sizeof(employees[0]))

struct Employee {
  char *name;
  char *department;
  char *trainings[10];
};

int main(void) {
  struct Employee joe = {
      "Joe Doe", "R&D", {"Compliance Training", "AI Training", NULL}};
  struct Employee jane = {
      "Jane Doe", "Quality", {"Compliance Training", "Quality Training", NULL}};
  struct Employee leonhard = {
      "Leonhard Ringfinger",
      "Manufacturing",
      {"How to Invade Efficiently", "Intro to Invasion", NULL}};
  struct Employee employees[] = {joe, jane, leonhard};

  for (struct Employee *ep = employees; ep - employees < NEMPLOYEES; ep++) {
    printf("Name: %s | Department: %s\n", ep->name, ep->department);
    for (char **tp = ep->trainings; *tp != NULL; tp++)
      printf("Training: %s\n", *tp);
  }
}
