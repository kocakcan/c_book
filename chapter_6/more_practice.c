#include <stdio.h>
#define PRINTB(b)                                                              \
  printf("Name: %s | Location: %s | HP: %d | Souls: %d | Weakness: %s\n"       \
         "Physical: %d | Fire: %d | Magic: %d | Lightning: %d",                \
         (b)->name, (b)->location, (b)->hp, (b)->souls,                        \
         weak_to_string((b)->weakness), (b)->pres, (b)->fres, (b)->mres,       \
         (b)->lres)

enum WEAKNESS { PHYSICAL, MAGIC, FIRE, LIGHTNING };

struct Boss {
  char *name;
  char *location;
  int hp;
  int pres; /* physical resistance */
  int fres; /* fire resistance */
  int mres; /* magic resistance */
  int lres; /* lightning resistance */
  enum WEAKNESS weakness;
  int souls;
  char *reward[5];
};

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
  struct Boss asylum_demon = {"Asylum Demon",
                              "Undead Asylum",
                              800,
                              83,
                              66,
                              62,
                              54,
                              LIGHTNING,
                              2000,
                              {"Big Pilgrim Key", "Humanity"}};
  struct Boss bell_gargoyles = {
      "Bell Gargoyles", "Undead Parish", 1479, 133, 98, 103, 104, FIRE, 10000,
      {"Gargoyle Helm"}};
  PRINTB(&asylum_demon);

  return 0;
}
