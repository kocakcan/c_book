#include "boss.h"
#include <stdio.h>

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
