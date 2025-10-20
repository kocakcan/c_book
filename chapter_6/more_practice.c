#include "boss.c"
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

int main(void) {
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
