#include "boss.h"
#include <stdio.h>

const char *weak_to_string(enum WEAKNESS weakness) {
  switch (weakness) {
  case PHYSICAL:
    return "PHYSICAL";
  case MAGIC:
    return "MAGIC";
  case FIRE:
    return "FIRE";
  case LIGHTNING:
    return "LIGHTNING";
  default:
    return "UNKNOWN WEAKNESS";
  }
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t)
    s++, t++;
  return (unsigned char)*s - (unsigned char)*t;
}

struct Boss *find_by_name(struct Boss *boss, const char *name) {
  for (size_t i = 0; i < BOSS_COUNT; i++) {
    if (strcmp_(boss->name, name) == 0)
      return boss;
    boss++;
  }

  return NULL;
}

int main(void) {
  struct Boss bosses[] = {asylum_demon, capra_demon,         quelagg,
                          priscilla,    gwyndolin,           super_ornstein,
                          super_smough, gaping_dragon,       iron_golem,
                          pinwheel,     stray_demon,         taurus_demon,
                          sif,          moonlight_butterfly, four_kings};
  struct Boss *bp = bosses;

  struct Boss *result = find_by_name(bosses, "Sif, the Great Grey Wolf");
  printf("Result: %s\n", (result != NULL) ? result->name : "NOT FOUND");

  return 0;
}
