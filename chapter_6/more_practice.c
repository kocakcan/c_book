#include "boss.c"
#include <limits.h>
#include <stdio.h>
#define PRINTB(b)                                                              \
  printf("Name: %s | Location: %s | HP: %d | Souls: %d | Weakness: %s\n"       \
         "Physical: %d | Fire: %d | Magic: %d | Lightning: %d\n",              \
         (b)->name, (b)->location, (b)->hp, (b)->souls,                        \
         weak_to_string((b)->weakness), (b)->pres, (b)->fres, (b)->mres,       \
         (b)->lres)

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

int main(void) {
  // PRINTB(&quelagg);
  struct Boss bosses[] = {asylum_demon, capra_demon,   quelagg,
                          priscilla,    gwyndolin,     super_ornstein,
                          super_smough, gaping_dragon, iron_golem,
                          pinwheel,     stray_demon,   taurus_demon};
  struct Boss *bp = bosses;
  size_t boss_count = sizeof(bosses) / sizeof(bosses[0]);

  while (boss_count--) {
    PRINTB(bp);
    bp++;
  }

  return 0;
}
