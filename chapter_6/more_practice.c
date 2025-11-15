#include "boss.h"
#include <stdio.h>

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t)
    s++, t++;
  return (unsigned char)*s - (unsigned char)*t;
}

size_t strlen_(const char *s) {
  size_t i = 0;

  while (*s++)
    i++;

  return i;
}

size_t get_longest_name(struct Boss *boss) {
  size_t max = strlen_(boss++->name);

  for (size_t i = 1; i < BOSS_COUNT; i++) {
    if (strlen_(boss->name) > max)
      max = strlen_(boss->name);
    boss++;
  }

  return max;
}

size_t get_longest_location(struct Boss *boss) {
  size_t max = strlen_(boss++->location);

  for (size_t i = 1; i < BOSS_COUNT; i++) {
    if (strlen_(boss->location) > max)
      max = strlen_(boss->location);
    boss++;
  }

  return max;
}

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

struct Boss *find_by_name(struct Boss *boss, const char *name) {
  for (size_t i = 0; i < BOSS_COUNT; i++) {
    if (strcmp_(boss->name, name) == 0)
      return boss;
    boss++;
  }

  return NULL;
}

enum WEAKNESS most_common_weakness(struct Boss *boss, int *out_count) {
  int counts[4] = {0};

  for (size_t i = 0; i < BOSS_COUNT; i++) {
    enum WEAKNESS w = boss[i].weakness;
    if ((int)w >= 0 && (int)w < 4)
      counts[(int)w]++;
  }

  int max = 0;
  for (size_t i = 1; i < 4; i++) {
    if (counts[i] > counts[max])
      max = i;
  }

  if (out_count)
    *out_count = counts[max];

  return (enum WEAKNESS)max;
}

int main(void) {
  struct Boss bosses[] = {asylum_demon,
                          bell_gargoyles,
                          capra_demon,
                          quelagg,
                          priscilla,
                          gwyndolin,
                          super_ornstein,
                          super_smough,
                          gaping_dragon,
                          iron_golem,
                          pinwheel,
                          stray_demon,
                          taurus_demon,
                          sif,
                          moonlight_butterfly,
                          four_kings,
                          ceaseless,
                          firesage,
                          sanctuary_guardian,
                          seath,
                          nito,
                          centipede_demon,
                          bed_of_chaos,
                          artorias,
                          manus,
                          kalameet,
                          gwyn,
                          gundyr,
                          vordt,
                          greatwood,
                          sage,
                          deacons,
                          abyss_watchers,
                          wolnir,
                          odk,
                          pontiff,
                          aldrich,
                          yhorm,
                          dancer,
                          oceiros,
                          champ_gundyr,
                          wyvern,
                          nameless_king,
                          dragonslayer_armour};
  struct Boss *bp = bosses;

  struct Boss *result = find_by_name(bosses, "Sif, the Great Grey Wolf");
  printf("Result: %s\n", (result != NULL) ? result->name : "NOT FOUND");

  size_t longest_name = get_longest_name(bp);
  size_t longest_location = get_longest_location(bp);

  for (size_t i = 0; i < BOSS_COUNT; i++) {
    PRINTB(bp, longest_name, longest_location);
    bp++;
  }

  int count;
  enum WEAKNESS most = most_common_weakness(bosses, &count);
  printf("%d bosses are weak to %s\n", count, weak_to_string(most));

  return 0;
}
