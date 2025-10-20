#include <limits.h>
#define PRINTB(b)                                                              \
  printf("Name: %s | Location: %s | HP: %d | Souls: %d | Weakness: %s\n"       \
         "Physical: %d | Fire: %d | Magic: %d | Lightning: %d\n",              \
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

static struct Boss asylum_demon = {"Asylum Demon",
                                   "Undead Asylum",
                                   800,
                                   83,
                                   66,
                                   62,
                                   54,
                                   LIGHTNING,
                                   2000,
                                   {"Big Pilgrim Key", "Humanity"}};
static struct Boss bell_gargoyles = {
    "Bell Gargoyles", "Undead Parish", 1479, 133, 98, 103, 104, FIRE, 10000,
    {"Gargoyle Helm"}};
static struct Boss capra_demon = {
    "Capra Demon",
    "Lower Undead Burg",
    1176,
    159,
    127,
    119,
    106,
    LIGHTNING,
    6000,
    {"Key to the Depths", "Humanity", "Homeward Bone", "Demon Great Machete"}};
static struct Boss super_ornstein = {
    "Super Ornstein",
    "Anor Londo",
    2981,
    339,
    221,
    256,
    1657,
    MAGIC,
    50000,
    {"Soul of Ornstein", "Leo Ring", "Humanity"}};
static struct Boss super_smough = {"Super Smough",
                                   "Anor Londo",
                                   4094,
                                   180,
                                   125,
                                   153,
                                   359,
                                   FIRE,
                                   50000,
                                   {"Soul of Smough", "Humanity"}};
static struct Boss quelagg = {"Chaos Witch Quelagg",
                              "Quelagg's Domain",
                              3139,
                              255,
                              INT_MAX,
                              229,
                              205,
                              LIGHTNING,
                              20000,
                              {"Soul of Quelagg", "Twin Humanities"}};
