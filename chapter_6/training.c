#include <stdio.h>

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
  struct Employee employees[] = {joe, jane};
  struct Employee *ep = employees;
  size_t employee_count = 2;

  while (employee_count--) {
    printf("Name: %s | Department: %s\n", ep->name, ep->department);
    char **tp = ep->trainings;
    while (*tp != NULL) {
      printf("Training: %s\n", *tp);
      tp++;
    }
    // while (*(ep->trainings) != NULL) {
    //   printf("Training: %s\n", *(ep->trainings));
    //   ep++;
    // }
    ep++;
  }

  // char *first_training = *(ep++->trainings);
  // printf("First training: %s\n", first_training);
  // printf("Second training: %s\n", *(ep->trainings));
}
