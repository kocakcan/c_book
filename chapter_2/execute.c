#include <stdio.h>
#include <stdlib.h>

enum boolean { NO, YES };

typedef struct {
  const char *name;
  unsigned attack;
  unsigned health;
} Card;

void init_card(Card *minion, const char *name, unsigned attack,
               unsigned health);

int execute(Card *minion);

int main() {
  Card *leeroy = malloc(sizeof(Card));
  init_card(leeroy, "Leeroy Jenkins", 6, 2);

  if (execute(leeroy)) {
    printf("You successfully destroyed %s, who was damaged before.\n",
           leeroy->name);
  }

  free(leeroy);

  return 0;
}

int execute(Card *minion) {
  minion->health = 0;

  printf("%s has been executed.\n", minion->name);

  return YES;
}

void init_card(Card *minion, const char *name, unsigned attack,
               unsigned health) {
  minion->name = name;
  minion->attack = attack;
  minion->health = health;
}
